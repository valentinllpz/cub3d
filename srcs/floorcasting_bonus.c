/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_floorcasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 12:44:10 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/14 17:15:30 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_floor_data(t_fc *fc, t_rc *rc, t_cfg *cfg)
{
	fc->f0raydir_x = rc->dir_x - rc->plane_x;
	fc->f0raydir_y = rc->dir_y - rc->plane_y;
	fc->f1raydir_x = rc->dir_x + rc->plane_x;
	fc->f1raydir_y = rc->dir_y + rc->plane_y;
	fc->p = fc->y - cfg->height / 2;
	fc->pos_z = 0.5 * cfg->height;
	fc->row_dist = fc->pos_z / fc->p;
	fc->floor_step_x = fc->row_dist * (fc->f1raydir_x - fc->f0raydir_x)
																/ cfg->width;
	fc->floor_step_y = fc->row_dist * (fc->f1raydir_y - fc->f0raydir_y)
																/ cfg->width;
	fc->floor_x = rc->pos_x + fc->row_dist * fc->f0raydir_x;
	fc->floor_y = rc->pos_y + fc->row_dist * fc->f0raydir_y;
	fc->x = 0;
}

void	floorcasting(t_rc *rc, t_cfg *cfg, t_tex tex, t_mlx *mlx)
{
	t_fc	fc;

	fc.y = 0;
	while (fc.y < cfg->height)
	{
		get_floor_data(&fc, rc, cfg);
		while (fc.x < cfg->width)
		{
			fc.cell_x = (int)(fc.floor_x);
			fc.cell_y = (int)(fc.floor_y);
			if (tex.h * (fc.floor_x - fc.cell_x) > 0 && tex.h *
											(fc.floor_x - fc.cell_x) < tex.w)
				rc->tex_x = abs((int)(tex.h * (fc.floor_x - fc.cell_x)));
			if (tex.h * (fc.floor_y - fc.cell_y) > 0 && tex.h *
											(fc.floor_y - fc.cell_y) < tex.h)
				rc->tex_y = abs((int)(tex.h * (fc.floor_y - fc.cell_y)));
			fc.floor_x += fc.floor_step_x;
			fc.floor_y += fc.floor_step_y;
			if (rc->tex_x < tex.w && rc->tex_y < tex.h)
				fc.color = get_pixel_color(&tex, rc->tex_x, rc->tex_y);
			draw_to_image(mlx, fc.color, fc.x, fc.y);
			fc.x++;
		}
		fc.y++;
	}
}
