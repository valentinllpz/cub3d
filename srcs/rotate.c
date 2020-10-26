/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:07:57 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/14 16:37:22 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_rc *rc)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = rc->dir_x;
	rc->dir_x = rc->dir_x * cos(-rc->rot) - rc->dir_y * sin(-rc->rot);
	rc->dir_y = olddir_x * sin(-rc->rot) + rc->dir_y * cos(-rc->rot);
	oldplane_x = rc->plane_x;
	rc->plane_x = rc->plane_x * cos(-rc->rot) - rc->plane_y * sin(-rc->rot);
	rc->plane_y = oldplane_x * sin(-rc->rot) + rc->plane_y * cos(-rc->rot);
}

void	rotate_right(t_rc *rc)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = rc->dir_x;
	rc->dir_x = rc->dir_x * cos(rc->rot) - rc->dir_y * sin(rc->rot);
	rc->dir_y = olddir_x * sin(rc->rot) + rc->dir_y * cos(rc->rot);
	oldplane_x = rc->plane_x;
	rc->plane_x = rc->plane_x * cos(rc->rot) - rc->plane_y * sin(rc->rot);
	rc->plane_y = oldplane_x * sin(rc->rot) + rc->plane_y * cos(rc->rot);
}
