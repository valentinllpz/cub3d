/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:27:12 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/14 16:22:07 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_file_failure(t_all *all)
{
	write(1, "Error\nCannot save the screenshot.\n", 35);
	clean_exit(all, EXIT_FAILURE);
}

t_bmp	header_init(t_cfg *cfg, t_mlx *mlx)
{
	t_bmp	bmp;

	bmp.file_size = (cfg->width * cfg->height * (mlx->bpp / 8)) + 54;
	bmp.reserved1 = 0;
	bmp.reserved2 = 0;
	bmp.pixel_data_offset = 54;
	bmp.header_size = 40;
	bmp.img_width = cfg->width;
	bmp.img_height = cfg->height;
	bmp.planes = 1;
	bmp.bpp = mlx->bpp;
	bmp.compression = 0;
	bmp.img_size = cfg->width * cfg->height + (mlx->bpp / 8);
	bmp.x_pixels_per_meter = 0;
	bmp.y_pixels_per_meter = 0;
	bmp.total_colors = 0;
	bmp.important_colors = 0;
	return (bmp);
}

void	render_first_img(t_all *all)
{
	if (BONUS)
	{
		gradient(all->mlx);
		raycasting(all);
		floorcasting(all->rc, all->cfg, all->rc->xpm[5], all->mlx);
	}
	raycasting(all);
	spritecasting(all);
	if (BONUS)
		mini_map(all);
}

void	save_screen_bmp(t_all *all)
{
	t_bmp			bmp;
	int				fd;
	int				i;
	unsigned int	*line;

	all->mlx->img_data = mlx_get_data_addr(all->mlx->img, &all->mlx->bpp,
									&all->mlx->line_size, &all->mlx->endian);
	if ((fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
		write_file_failure(all);
	bmp = header_init(all->cfg, all->mlx);
	if (write(fd, "BM", 2) != 2 || write(fd, &bmp, sizeof(bmp)) != sizeof(bmp))
		write_file_failure(all);
	i = 0;
	while (i < all->cfg->height)
	{
		line = (unsigned int *)&all->mlx->img_data[(all->cfg->height - i - 1) *
			all->mlx->line_size];
		if (!write(fd, line, all->mlx->line_size))
			write_file_failure(all);
		i++;
	}
	if (close(fd) == -1)
		clean_exit(all, EXIT_FAILURE);
	clean_exit(all, EXIT_SUCCESS);
}
