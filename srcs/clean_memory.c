/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:47:54 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/20 09:25:11 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_to_null(t_all *all)
{
	all->cfg->no = NULL;
	all->cfg->so = NULL;
	all->cfg->we = NULL;
	all->cfg->ea = NULL;
	all->cfg->sprite = NULL;
	all->cfg->grid = NULL;
	all->sc->z_buffer = NULL;
	all->sc->spr = NULL;
	all->sc->spr_order = NULL;
	all->sc->spr_dist = NULL;
}

void	clean_mem(t_all *all)
{
	int		i;

	i = 0;
	if (all->cfg->grid)
		while (all->cfg->grid[i])
		{
			if (all->cfg->grid[i])
				free(all->cfg->grid[i]);
			i++;
		}
	if (all->cfg->grid)
		free(all->cfg->grid);
	if (all->cfg->no)
		free(all->cfg->no);
	if (all->cfg->so)
		free(all->cfg->so);
	if (all->cfg->we)
		free(all->cfg->we);
	if (all->cfg->ea)
		free(all->cfg->ea);
	if (all->cfg->sprite)
		free(all->cfg->sprite);
}

void	clean_mem_3(t_all *all)
{
	if (all->mlx)
		free(all->mlx);
	if (all->cfg)
		free(all->cfg);
	if (all->rc)
		free(all->rc);
	if (all->key)
		free(all->key);
	if (all->sc->spr)
		free(all->sc->spr);
	if (all->sc->z_buffer)
		free(all->sc->z_buffer);
	if (all->sc->spr_order)
		free(all->sc->spr_order);
	if (all->sc->spr_dist)
		free(all->sc->spr_dist);
	if (all->sc)
		free(all->sc);
}

void	clean_mem_2(t_all *all)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		if (all->rc->xpm[i].ptr)
			mlx_destroy_image(all->mlx->ptr, all->rc->xpm[i].ptr);
		i++;
	}
	if (all->mlx->img)
		mlx_destroy_image(all->mlx->ptr, all->mlx->img);
}
