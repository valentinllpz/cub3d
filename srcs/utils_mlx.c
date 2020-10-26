/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:31:40 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/20 09:20:19 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		render_next_frame(t_all *all)
{
	static int flag = 0;

	keys_action(all);
	if (BONUS && flag == 0)
	{
		title_screen(all);
		if (all->key->space == 1)
			flag++;
		return (1);
	}
	if (BONUS)
	{
		gradient(all->mlx);
		floorcasting(all->rc, all->cfg, all->rc->xpm[5], all->mlx);
	}
	raycasting(all);
	spritecasting(all);
	if (BONUS)
	{
		mini_map(all);
		draw_ratio(all, &all->rc->xpm[7]);
	}
	mlx_put_image_to_window((t_all *)all->mlx->ptr, all->mlx->win,
														all->mlx->img, 0, 0);
	return (1);
}

void	draw_verline(t_all *all, t_rc rc, t_tex tex, int x)
{
	int		tmp;

	tmp = 0;
	if (!BONUS)
		while (tmp < rc.drawstart)
		{
			draw_to_image(all->mlx, rc.c_color, x, tmp);
			tmp++;
		}
	if (BONUS)
		draw_skybox(all, x, 0, all->rc->xpm[6]);
	while (rc.drawstart < rc.drawend)
	{
		rc.tex_y = (int)rc.tex_pos;
		rc.tex_pos += rc.step;
		rc.color = get_pixel_color(&tex, rc.tex_x, rc.tex_y);
		draw_to_image(all->mlx, rc.color, x, rc.drawstart);
		rc.drawstart++;
	}
	if (!BONUS)
		while (rc.drawend > 0 && rc.drawend < all->cfg->height)
		{
			draw_to_image(all->mlx, rc.f_color, x, rc.drawend);
			rc.drawend++;
		}
}

void	draw_to_image(t_mlx *mlx, int color, int x, int y)
{
	if ((color & 0x00FFFFFF) != 0)
		*(int *)(mlx->img_data + y * mlx->line_size + x * mlx->bpp / 8) = color;
	else if (BONUS)
		*(int *)(mlx->img_data + y * mlx->line_size + x
												* mlx->bpp / 8) = mlx->bg_color;
	else
		*(int *)(mlx->img_data + y * mlx->line_size + x * mlx->bpp / 8) = 0;
}

int		get_pixel_color(t_tex *tex, int x, int y)
{
	return (*(int*)(tex->data + y * tex->line_size + x * tex->bpp / 8));
}

int		create_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
