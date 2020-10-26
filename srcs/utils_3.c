/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:25:03 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/26 14:19:12 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_empty_lines(t_cfg *cfg)
{
	int		y;
	int		x;
	int		end;

	y = cfg->line_nb - 1;
	end = cfg->line_nb;
	x = 0;
	while (y > 0)
	{
		skip_spaces(cfg->grid[y], &x);
		if (!cfg->grid[y][x])
		{
			if (cfg->grid[y])
				free(cfg->grid[y]);
			cfg->grid[y] = cfg->grid[end];
			cfg->line_nb--;
			x = 0;
		}
		else
			break ;
		y--;
	}
}

int		check_xpm(t_cfg *cfg)
{
	int		fd;

	if (!check_open(cfg->no, &fd))
		return (0);
	close(fd);
	if (!check_open(cfg->so, &fd))
		return (0);
	close(fd);
	if (!check_open(cfg->we, &fd))
		return (0);
	close(fd);
	if (!check_open(cfg->ea, &fd))
		return (0);
	close(fd);
	if (!check_open(cfg->sprite, &fd))
		return (0);
	close(fd);
	return (1);
}

int		check_extension(char *path, char *ext)
{
	int		i;
	int		j;

	i = ft_strlen(path) - 4;
	j = 0;
	while (path[i])
	{
		if (ext[j] != path[i])
			return (0);
		i++;
		j++;
	}
	return (1);
}

int		fc_already_exists(char *line, t_cfg *cfg)
{
	if ((cfg->flag_f == 1 && line[0] == 'F')
		|| (cfg->flag_c == 1 && line[0] == 'C'))
		return (1);
	return (0);
}

int		key_is_valid(char c)
{
	if (c && c != 'R' && c != 'F' && c != 'C' && !is_nswe(c))
		return (0);
	return (1);
}
