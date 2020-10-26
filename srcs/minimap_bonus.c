/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 15:35:27 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/14 16:21:49 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mini_map(t_all *all)
{
	int				i;
	int				j;
	t_minimap		mm;

	init_mini_map(&mm, all->cfg);
	j = 0;
	while (all->cfg->grid[j])
	{
		i = 0;
		while (all->cfg->grid[j][i])
		{
			draw_tiles(&mm, all, i, j);
			i++;
		}
		j++;
	}
}

void	draw_tiles(t_minimap *mm, t_all *all, int i, int j)
{
	mm->tile_x = i * mm->tile_size + 10;
	mm->next_tile_x = mm->tile_x + mm->tile_size;
	while (mm->tile_x <= mm->next_tile_x)
	{
		mm->tile_y = j * mm->tile_size + 10;
		mm->next_tile_y = mm->tile_y + mm->tile_size;
		while (mm->tile_y <= mm->next_tile_y)
		{
			if (all->cfg->grid[j][i] == '0')
				draw_to_image(all->mlx, 0x001B2025, mm->tile_x, mm->tile_y);
			if (all->cfg->grid[j][i] == '1' || all->cfg->grid[j][i] == ' ')
				draw_to_image(all->mlx, 0x003A4753, mm->tile_x, mm->tile_y);
			if (all->cfg->grid[j][i] == '2')
				draw_to_image(all->mlx, 0x00d70d2e, mm->tile_x, mm->tile_y);
			if ((int)floor(all->rc->pos_x) == i &&
											(int)floor(all->rc->pos_y) == j)
				draw_to_image(all->mlx, 0x000fc7ec, mm->tile_x, mm->tile_y);
			mm->tile_y++;
		}
		mm->tile_x++;
	}
}

void	init_mini_map(t_minimap *mm, t_cfg *cfg)
{
	mm->tile_x = 0;
	mm->tile_y = 0;
	mm->next_tile_x = 0;
	mm->next_tile_y = 0;
	mm->tile_size = 0;
	mm->tile_size = cfg->width / cfg->line_max_len + cfg->height / cfg->line_nb;
	mm->tile_size = mm->tile_size / 2 / 5;
}
