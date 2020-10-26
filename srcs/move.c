/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:46:16 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/14 16:20:46 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_left(t_rc *rc, t_cfg *cfg)
{
	double	olddir_x;
	double	olddir_y;
	int		tmp_x;
	int		tmp_y;

	olddir_x = rc->dir_x;
	olddir_y = rc->dir_y;
	rc->dir_x = rc->dir_y;
	rc->dir_y = -olddir_x;
	tmp_x = floor(rc->pos_x + rc->dir_x * rc->speed);
	tmp_y = floor(rc->pos_y + rc->dir_y * rc->speed);
	if (BONUS && cfg->grid[(int)floor(rc->pos_y)][tmp_x] == '0')
		rc->pos_x += rc->dir_x * rc->speed;
	else if (!BONUS && tmp_x > 0 && tmp_x < cfg->line_max_len - 1)
		rc->pos_x += rc->dir_x * rc->speed;
	if (BONUS && cfg->grid[tmp_y][(int)floor(rc->pos_x)] == '0')
		rc->pos_y += rc->dir_y * rc->speed;
	else if (!BONUS && tmp_y > 0 && tmp_y < cfg->line_nb - 1)
		rc->pos_y += rc->dir_y * rc->speed;
	rc->dir_x = olddir_x;
	rc->dir_y = olddir_y;
}

void	move_right(t_rc *rc, t_cfg *cfg)
{
	double	olddir_x;
	double	olddir_y;
	int		tmp_x;
	int		tmp_y;

	olddir_x = rc->dir_x;
	olddir_y = rc->dir_y;
	rc->dir_x = -rc->dir_y;
	rc->dir_y = olddir_x;
	tmp_x = floor(rc->pos_x + rc->dir_x * rc->speed);
	tmp_y = floor(rc->pos_y + rc->dir_y * rc->speed);
	if (BONUS && cfg->grid[(int)floor(rc->pos_y)][tmp_x] == '0')
		rc->pos_x += rc->dir_x * rc->speed;
	else if (!BONUS && tmp_x > 0 && tmp_x < cfg->line_max_len - 1)
		rc->pos_x += rc->dir_x * rc->speed;
	if (BONUS && cfg->grid[tmp_y][(int)floor(rc->pos_x)] == '0')
		rc->pos_y += rc->dir_y * rc->speed;
	else if (!BONUS && tmp_y > 0 && tmp_y < cfg->line_nb - 1)
		rc->pos_y += rc->dir_y * rc->speed;
	rc->dir_x = olddir_x;
	rc->dir_y = olddir_y;
}

void	move_fwd(t_rc *rc, t_cfg *cfg)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = floor(rc->pos_x + rc->dir_x * rc->speed);
	tmp_y = floor(rc->pos_y + rc->dir_y * rc->speed);
	if (BONUS && cfg->grid[(int)floor(rc->pos_y)][tmp_x] == '0')
		rc->pos_x += rc->dir_x * rc->speed;
	else if (!BONUS && tmp_x > 0 && tmp_x < cfg->line_max_len - 1)
		rc->pos_x += rc->dir_x * rc->speed;
	if (BONUS && cfg->grid[tmp_y][(int)floor(rc->pos_x)] == '0')
		rc->pos_y += rc->dir_y * rc->speed;
	else if (!BONUS && tmp_y > 0 && tmp_y < cfg->line_nb - 1)
		rc->pos_y += rc->dir_y * rc->speed;
}

void	move_bwd(t_rc *rc, t_cfg *cfg)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = floor(rc->pos_x - rc->dir_x * rc->speed);
	tmp_y = floor(rc->pos_y - rc->dir_y * rc->speed);
	if (BONUS && cfg->grid[(int)floor(rc->pos_y)][tmp_x] == '0')
		rc->pos_x -= rc->dir_x * rc->speed;
	else if (!BONUS && tmp_x > 0 && tmp_x < cfg->line_max_len - 1)
		rc->pos_x -= rc->dir_x * rc->speed;
	if (BONUS && cfg->grid[tmp_y][(int)floor(rc->pos_x)] == '0')
		rc->pos_y -= rc->dir_y * rc->speed;
	else if (!BONUS && tmp_y > 0 && tmp_y < cfg->line_nb - 1)
		rc->pos_y -= rc->dir_y * rc->speed;
}

void	run_fwd(t_all *all)
{
	all->rc->speed *= 2.2;
	move_fwd(all->rc, all->cfg);
	all->rc->speed /= 2.2;
}
