/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 11:23:57 by vlugand-          #+#    #+#             */
/*   Updated: 2020/09/28 16:49:13 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_sprites_nb(t_cfg cfg, t_sc *sc)
{
	int		i;
	int		j;

	i = 0;
	sc->nb = 0;
	while (cfg.grid[i])
	{
		j = 0;
		while (cfg.grid[i][j])
		{
			if (cfg.grid[i][j] == '2')
				sc->nb++;
			j++;
		}
		i++;
	}
}

void	get_sprites_xy(t_cfg cfg, t_sc *sc)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (cfg.grid[i])
	{
		j = 0;
		while (cfg.grid[i][j])
		{
			if (cfg.grid[i][j] == '2')
			{
				sc->spr[k].x = j + 0.5;
				sc->spr[k].y = i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
}

void	ft_swap(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_dblswap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
