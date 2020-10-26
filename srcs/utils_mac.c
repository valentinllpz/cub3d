/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_res_mac.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:27:49 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/19 15:07:00 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	t_mlx_init(t_mlx *mlx, t_cfg *cfg)
{
	int		width_max;
	int		height_max;

	width_max = 1200;
	height_max = 800;
	mlx->ptr = mlx_init();
	if (cfg->width > width_max)
		cfg->width = width_max;
	if (cfg->height > height_max)
		cfg->height = height_max;
	mlx->win = mlx_new_window(mlx->ptr, cfg->width, cfg->height, "cub3D");
	mlx->img = mlx_new_image(mlx->ptr, cfg->width, cfg->height);
	mlx->img_data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size,
																&mlx->endian);
}

void	clean_exit(t_all *all, int status)
{
	clean_mem(all);
	clean_mem_2(all);
	mlx_destroy_window(all->mlx->ptr, all->mlx->win);
	if (all->mlx->ptr)
		free(all->mlx->ptr);
	clean_mem_3(all);
	exit(status);
}
