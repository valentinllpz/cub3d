/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:16:49 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/14 17:25:33 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_data(t_rc *rc, t_cfg *cfg)
{
	if (rc->side <= 1)
		rc->perpwalldist = (rc->map_x - rc->pos_x + (1 - rc->step_x) / 2)
																/ rc->raydir_x;
	else
		rc->perpwalldist = (rc->map_y - rc->pos_y + (1 - rc->step_y) / 2)
																/ rc->raydir_y;
	rc->lineheight = (int)(cfg->height / rc->perpwalldist);
	rc->drawstart = (int)(-rc->lineheight / 2 + cfg->height / 2);
	if (rc->drawstart < 0)
		rc->drawstart = 0;
	rc->drawend = (int)(rc->lineheight / 2 + cfg->height / 2);
	if (rc->drawend >= cfg->height)
		rc->drawend = cfg->height - 1;
}

void	perform_dda(t_rc *rc, t_cfg *cfg)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->sidedist_x < rc->sidedist_y)
		{
			rc->sidedist_x += rc->deltadist_x;
			rc->map_x += rc->step_x;
			if (rc->raydir_x < 0)
				rc->side = 0;
			else
				rc->side = 1;
		}
		else
		{
			rc->sidedist_y += rc->deltadist_y;
			rc->map_y += rc->step_y;
			if (rc->raydir_y < 0)
				rc->side = 2;
			else
				rc->side = 3;
		}
		if (cfg->grid[rc->map_y][rc->map_x] == '1' ||
				cfg->grid[rc->map_y][rc->map_x] == ' ')
			rc->hit = 1;
	}
}

void	get_step_and_sidedist(t_rc *rc)
{
	if (rc->raydir_x < 0)
	{
		rc->step_x = -1;
		rc->sidedist_x = (rc->pos_x - rc->map_x) * rc->deltadist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->sidedist_x = (rc->map_x + 1.0 - rc->pos_x) * rc->deltadist_x;
	}
	if (rc->raydir_y < 0)
	{
		rc->step_y = -1;
		rc->sidedist_y = (rc->pos_y - rc->map_y) * rc->deltadist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->sidedist_y = (rc->map_y + 1.0 - rc->pos_y) * rc->deltadist_y;
	}
}

void	prepare_new_ray(t_rc *rc, t_cfg *cfg, int x)
{
	rc->camera_x = 2 * x / (double)cfg->width - 1;
	rc->raydir_x = rc->dir_x + rc->plane_x * rc->camera_x;
	rc->raydir_y = rc->dir_y + rc->plane_y * rc->camera_x;
	rc->map_x = (int)rc->pos_x;
	rc->map_y = (int)rc->pos_y;
	if (rc->raydir_y == 0)
		rc->deltadist_x = 0;
	else
	{
		if (rc->raydir_x == 0)
			rc->deltadist_x = 1;
		else
			rc->deltadist_x = fabs(1 / rc->raydir_x);
	}
	if (rc->raydir_x == 0)
		rc->deltadist_y = 0;
	else
	{
		if (rc->raydir_y == 0)
			rc->deltadist_y = 1;
		else
			rc->deltadist_y = fabs(1 / rc->raydir_y);
	}
}

void	raycasting(t_all *all)
{
	int		x;

	x = 0;
	while (x < all->cfg->width)
	{
		prepare_new_ray(all->rc, all->cfg, x);
		get_step_and_sidedist(all->rc);
		perform_dda(all->rc, all->cfg);
		get_wall_data(all->rc, all->cfg);
		print_tex_to_wall(all->rc, all->cfg, all->rc->xpm[all->rc->side]);
		draw_verline(all, *all->rc, all->rc->xpm[all->rc->side], x);
		all->sc->z_buffer[x] = all->rc->perpwalldist;
		x++;
	}
}
