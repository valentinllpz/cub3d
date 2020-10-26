/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:12:49 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/19 11:58:55 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		struct_all_init(t_all *all)
{
	ft_bzero(all, sizeof(*all));
	if (!(all->mlx = malloc(sizeof(t_mlx))))
		return (0);
	if (!(all->cfg = malloc(sizeof(t_cfg))))
		return (0);
	if (!(all->rc = malloc(sizeof(t_rc))))
		return (0);
	if (!(all->key = malloc(sizeof(t_key))))
		return (0);
	if (!(all->sc = malloc(sizeof(t_sc))))
		return (0);
	set_to_null(all);
	return (1);
}

void	cfg_init(t_cfg *cfg)
{
	cfg->width = 0;
	cfg->height = 0;
	cfg->no = NULL;
	cfg->so = NULL;
	cfg->ea = NULL;
	cfg->we = NULL;
	cfg->sprite = NULL;
	cfg->f[0] = 0;
	cfg->f[1] = 0;
	cfg->f[2] = 0;
	cfg->flag_f = 0;
	cfg->c[0] = 0;
	cfg->c[1] = 0;
	cfg->c[2] = 0;
	cfg->flag_c = 0;
	cfg->grid = NULL;
	cfg->position = '0';
	cfg->dir_x = 0;
	cfg->dir_y = 0;
	cfg->line_nb = 0;
	cfg->line_max_len = 0;
	cfg->count_lines = 0;
	cfg->start_grid = 0;
	cfg->success = 0;
}

void	t_key_init(t_key *key)
{
	key->fwd = 0;
	key->bwd = 0;
	key->r = 0;
	key->l = 0;
	key->cam_l = 0;
	key->cam_r = 0;
	key->space = 0;
	key->run = 0;
}

void	t_rc_init(t_rc *rc, t_cfg *cfg)
{
	ft_bzero(rc, sizeof(*rc));
	rc->pos_x = cfg->pos_x;
	rc->pos_y = cfg->pos_y;
	rc->dir_x = cfg->dir_x;
	rc->dir_y = cfg->dir_y;
	rc->plane_x = 0;
	rc->plane_y = 0;
	if (cfg->position == 'E')
		rc->plane_y = 0.66;
	else if (cfg->position == 'W')
		rc->plane_y = -0.66;
	else if (cfg->position == 'N')
		rc->plane_x = 0.66;
	else if (cfg->position == 'S')
		rc->plane_x = -0.66;
	cfg->grid[cfg->pos_y][cfg->pos_x] = '0';
	rc->f_color = create_trgb(cfg->f[0], cfg->f[1], cfg->f[2]);
	rc->c_color = create_trgb(cfg->c[0], cfg->c[1], cfg->c[2]);
	rc->speed = 0.07;
	rc->rot = 0.06;
	if (BONUS)
	{
		rc->speed = 0.12;
		rc->rot = 0.10;
	}
}

int		sc_init(t_all *all)
{
	ft_bzero(all->sc, sizeof(all->sc));
	get_sprites_nb(*all->cfg, all->sc);
	if (!(all->sc->z_buffer = (double *)malloc((all->cfg->width)
														* sizeof(double))))
		clean_exit(all, EXIT_FAILURE);
	if (!(all->sc->spr = (t_sprite *)malloc((all->sc->nb) * sizeof(t_sprite))))
		clean_exit(all, EXIT_FAILURE);
	get_sprites_xy(*all->cfg, all->sc);
	if (!(all->sc->spr_order = (int *)malloc((all->sc->nb) * sizeof(int))))
		clean_exit(all, EXIT_FAILURE);
	if (!(all->sc->spr_dist = (double *)malloc((all->sc->nb) * sizeof(double))))
		clean_exit(all, EXIT_FAILURE);
	return (1);
}
