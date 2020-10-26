/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:09:27 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/26 14:21:45 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		keys_action(t_all *all)
{
	if (all->key->l == 1)
		move_left(all->rc, all->cfg);
	else if (all->key->r == 1)
		move_right(all->rc, all->cfg);
	else if (all->key->fwd == 1)
	{
		if (BONUS && all->key->run == 1 && all->key->bwd == 0)
			run_fwd(all);
		else
			move_fwd(all->rc, all->cfg);
	}
	else if (all->key->bwd == 1)
		move_bwd(all->rc, all->cfg);
	if (all->key->cam_l == 1)
		rotate_left(all->rc);
	else if (all->key->cam_r == 1)
		rotate_right(all->rc);
	if (all->rc->pos_x == (int)all->rc->pos_x)
		all->rc->pos_x += 0.2;
	if (all->rc->pos_y == (int)all->rc->pos_y)
		all->rc->pos_y += 0.2;
	return (1);
}

int		ft_key_press(int keycode, t_all *all)
{
	if (keycode == ESC)
		clean_exit(all, EXIT_SUCCESS);
	if (keycode == W)
		all->key->fwd = 1;
	if (keycode == A)
		all->key->l = 1;
	if (keycode == S)
		all->key->bwd = 1;
	if (keycode == D)
		all->key->r = 1;
	if (keycode == LEFT)
		all->key->cam_l = 1;
	if (keycode == RIGHT)
		all->key->cam_r = 1;
	if (keycode == UP)
		all->key->run = 1;
	if (keycode == SPACE)
		all->key->space = 1;
	return (1);
}

int		ft_key_release(int keycode, t_all *all)
{
	if (keycode == W)
		all->key->fwd = 0;
	if (keycode == A)
		all->key->l = 0;
	if (keycode == S)
		all->key->bwd = 0;
	if (keycode == D)
		all->key->r = 0;
	if (keycode == LEFT)
		all->key->cam_l = 0;
	if (keycode == RIGHT)
		all->key->cam_r = 0;
	if (keycode == UP)
		all->key->run = 0;
	if (keycode == SPACE)
		all->key->space = 0;
	return (1);
}
