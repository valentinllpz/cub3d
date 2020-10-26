/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 13:46:07 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/20 09:22:10 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(int *order, double *distance, int number)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (i < number)
	{
		while (j < number)
		{
			if (distance[j] > distance[i])
			{
				ft_swap(&order[i], &order[j]);
				ft_dblswap(&distance[i], &distance[j]);
			}
			j++;
		}
		i++;
		j = i;
	}
}

void	calculate_sprite_distance(t_sc *sc, t_rc *rc)
{
	int		i;

	i = 0;
	while (i < sc->nb)
	{
		sc->spr_order[i] = i;
		sc->spr_dist[i] = ((rc->pos_x - sc->spr[i].x)
					* (rc->pos_x - sc->spr[i].x) + (rc->pos_y - sc->spr[i].y)
					* (rc->pos_y - sc->spr[i].y));
		i++;
	}
}

void	get_sprite_onscreen_data(t_sc *sc, t_rc *rc, t_cfg *cfg, int i)
{
	sc->spr_x = sc->spr[sc->spr_order[i]].x - rc->pos_x;
	sc->spr_y = sc->spr[sc->spr_order[i]].y - rc->pos_y;
	sc->inv = 1.0 / (rc->plane_x * rc->dir_y - rc->dir_x * rc->plane_y);
	sc->trsform_x = sc->inv * (rc->dir_y * sc->spr_x - rc->dir_x * sc->spr_y);
	sc->trsform_y = sc->inv
						* (-rc->plane_y * sc->spr_x + rc->plane_x * sc->spr_y);
	sc->spr_screen_x = (int)(cfg->width / 2
						* (1 + sc->trsform_x / sc->trsform_y));
	sc->spr_h = (int)fabs(cfg->height / sc->trsform_y);
	sc->drawstart_y = -sc->spr_h / 2 + cfg->height / 2;
	if (sc->drawstart_y < 0)
		sc->drawstart_y = 0;
	sc->drawend_y = sc->spr_h / 2 + cfg->height / 2;
	if (sc->drawend_y >= cfg->height)
		sc->drawend_y = cfg->height - 1;
	sc->spr_w = (int)fabs(cfg->height / sc->trsform_y);
	sc->drawstart_x = -sc->spr_w / 2 + sc->spr_screen_x;
	if (sc->drawstart_x < 0)
		sc->drawstart_x = 0;
	sc->drawend_x = sc->spr_w / 2 + sc->spr_screen_x;
	if (sc->drawend_x >= cfg->width)
		sc->drawend_x = cfg->width - 1;
	sc->stripe = sc->drawstart_x;
}

void	display_sprite(t_sc *sc, t_cfg *cfg, t_tex *tex, t_mlx *mlx)
{
	int		y;

	while (sc->stripe < sc->drawend_x)
	{
		sc->tex_x = abs((int)(256 * (sc->stripe - (-sc->spr_w / 2
							+ sc->spr_screen_x)) * tex->w / sc->spr_w) / 256);
		if (sc->trsform_y > 0 && sc->stripe > 0 && sc->stripe < cfg->width
								&& sc->trsform_y < sc->z_buffer[sc->stripe])
		{
			y = sc->drawstart_y;
			while (y < sc->drawend_y)
			{
				sc->d = (y) * 256 - cfg->height * 128 + sc->spr_h * 128;
				sc->tex_y = abs(((sc->d * tex->h) / sc->spr_h) / 256);
				if (sc->tex_y < tex->h && sc->tex_x < tex->w)
					sc->color = get_pixel_color(tex, sc->tex_x, sc->tex_y);
				if ((sc->color & 0x00FFFFFF) != 0)
					draw_to_image(mlx, sc->color, sc->stripe, y);
				y++;
			}
		}
		sc->stripe++;
	}
}

void	spritecasting(t_all *all)
{
	int		i;

	i = 0;
	calculate_sprite_distance(all->sc, all->rc);
	sort_sprites(all->sc->spr_order, all->sc->spr_dist, all->sc->nb);
	i = 0;
	while (i < all->sc->nb)
	{
		get_sprite_onscreen_data(all->sc, all->rc, all->cfg, i);
		display_sprite(all->sc, all->cfg, &all->rc->xpm[4], all->mlx);
		i++;
	}
}
