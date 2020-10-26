/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 15:06:08 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/15 17:30:15 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_tex_to_wall(t_rc *rc, t_cfg *cfg, t_tex tex)
{
	if (rc->side <= 1)
		rc->wall_x = rc->pos_y + rc->perpwalldist * rc->raydir_y;
	else
		rc->wall_x = rc->pos_x + rc->perpwalldist * rc->raydir_x;
	rc->wall_x -= floor(rc->wall_x);
	rc->tex_x = (int)(rc->wall_x * (double)tex.w);
	if (rc->side <= 0 && rc->raydir_x > 0)
		rc->tex_x = tex.w - rc->tex_x - 1;
	if (rc->side > 1 && rc->raydir_y < 0)
		rc->tex_x = tex.w - rc->tex_x - 1;
	rc->step = 1.0 * tex.w / rc->lineheight;
	rc->tex_pos = (rc->drawstart - cfg->height / 2 + rc->lineheight / 2)
																	* rc->step;
}

t_tex	load_texture(t_all *all, char *path)
{
	t_tex	tex;

	tex.ptr = NULL;
	if (!(tex.ptr = mlx_xpm_file_to_image(all->mlx->ptr, path, &tex.w, &tex.h)))
	{
		write(1, "Error\nCorrupted or missing XPM file.\n(", 38);
		ft_putstr_fd(path, 1);
		write(1, ")\n\nAborting...\n", 15);
		clean_exit(all, EXIT_FAILURE);
	}
	tex.data = mlx_get_data_addr(tex.ptr, &tex.bpp, &tex.line_size,
																&tex.endian);
	return (tex);
}

void	init_textures(t_all *all)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		all->rc->xpm[i].ptr = NULL;
		i++;
	}
	all->rc->xpm[0] = load_texture(all, all->cfg->ea);
	all->rc->xpm[1] = load_texture(all, all->cfg->we);
	all->rc->xpm[2] = load_texture(all, all->cfg->no);
	all->rc->xpm[3] = load_texture(all, all->cfg->so);
	all->rc->xpm[4] = load_texture(all, all->cfg->sprite);
	if (BONUS)
	{
		all->rc->xpm[5] = load_texture(all, "./textures/custom/floor.xpm");
		all->rc->xpm[6] = load_texture(all, "./textures/custom/sky.xpm");
		all->rc->xpm[7] = load_texture(all, "./textures/custom/gun.xpm");
	}
}
