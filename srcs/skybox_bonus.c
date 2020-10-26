/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_skybox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:49:51 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/14 16:48:19 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_skybox(t_all *all, int x, int drawstart, t_tex sky)
{
	double	step;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	int		color;

	all->rc->sky_x = fabs(atan2(all->rc->raydir_y, all->rc->raydir_x)
													* 180 / M_PI - 180) / 360;
	tex_x = sky.w;
	step = sky.w / (double)(all->cfg->height / 2);
	tex_pos = sky.w;
	tex_y = (int)(all->rc->sky_x * (double)(sky.h - 1));
	if (tex_y < 1)
		tex_y = 1;
	while (drawstart < all->rc->drawstart)
	{
		tex_x = (int)tex_pos;
		tex_pos = tex_pos - step;
		if (tex_y <= sky.h && tex_x <= sky.w)
			color = get_pixel_color(&sky, tex_x, tex_y);
		draw_to_image(all->mlx, color, x, drawstart);
		drawstart++;
	}
}
