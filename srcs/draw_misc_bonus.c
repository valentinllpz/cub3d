/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_misc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:15:40 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/15 17:34:19 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ratio(t_all *all, t_tex *img)
{
	t_ratio		screen;

	screen.ratio_x = (double)img->w / (double)all->cfg->width;
	screen.ratio_y = (double)img->h / (double)all->cfg->height;
	screen.x = 0;
	screen.y = 0;
	while (screen.y < all->cfg->height)
	{
		screen.ybis = (double)screen.y * (double)screen.ratio_y;
		while (screen.x < all->cfg->width)
		{
			screen.xbis = (double)screen.x * (double)screen.ratio_x;
			screen.color = get_pixel_color(img, screen.xbis, screen.ybis);
			if ((screen.color & 0x00FFFFFF) != 0)
				*(int *)(all->mlx->img_data + screen.y * all->mlx->line_size
								+ screen.x * all->mlx->bpp / 8) = screen.color;
			screen.x++;
		}
		screen.x = 0;
		screen.y++;
	}
}

void	title_screen(t_all *all)
{
	t_tex		img;

	img = load_texture(all, "./textures/custom/title.xpm");
	draw_ratio(all, &img);
	mlx_put_image_to_window((t_all *)all->mlx->ptr, all->mlx->win,
														all->mlx->img, 0, 0);
	mlx_destroy_image(all->mlx->ptr, img.ptr);
}

void	gradient(t_mlx *mlx)
{
	static int	sens = 1;
	static int	i = 1;

	if (i == 255 || i == 0)
		sens *= -1;
	mlx->bg_color = create_trgb(0 + i, 255 - i, 255);
	if (sens > 0)
		i++;
	if (sens < 0)
		i--;
}
