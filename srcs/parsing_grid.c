/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 15:42:40 by vlugand-          #+#    #+#             */
/*   Updated: 2020/09/28 16:49:13 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		grid_check(char *line, t_cfg *cfg)
{
	if (!check_missing_data(cfg))
		return (-5);
	if (!check_grid_lines(line, cfg))
		return (-6);
	cfg->line_nb++;
	if (cfg->line_max_len < find_max_len(line))
		cfg->line_max_len = find_max_len(line);
	if (cfg->start_grid == 0)
		cfg->start_grid = cfg->count_lines;
	return (1);
}

int		check_grid_lines(char *line, t_cfg *cfg)
{
	int		i;

	i = 0;
	while (line[i] && (is_space(line[i]) || (line[i] >= '0' && line[i] <= '2')))
	{
		skip_spaces(line, &i);
		if (line[i] && line[i] != '1')
			return (0);
		while ((line[i] >= '0' && line[i] <= '2') || is_nswe(line[i]))
		{
			if (!(line[i] >= '0' && line[i] <= '2'))
			{
				if (cfg->position != '0' || !get_position(cfg, line[i], i))
					return (0);
			}
			i++;
		}
		if (line[i - 1] != '1')
			return (0);
		skip_spaces(line, &i);
	}
	if (line[i])
		return (0);
	return (1);
}

int		grid_parsing(t_cfg *cfg, char *cfg_file)
{
	int		fd;
	char	*line;
	int		i;

	if (!check_open(cfg_file, &fd))
		return (0);
	i = 1;
	while (i < cfg->start_grid && get_next_line(fd, &line, 1, 0) > 0)
	{
		i++;
		free(line);
		line = NULL;
	}
	store_grid(cfg, fd);
	close(fd);
	if (!check_grid_columns(cfg) || cfg->position == '0')
	{
		write(1, "Error\nInvalid grid.\n\nAborting...\n", 33);
		free_all(cfg);
		return (0);
	}
	return (1);
}

int		check_grid_columns(t_cfg *cfg)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cfg->grid[i])
	{
		j = 0;
		while (j < (int)ft_strlen(cfg->grid[i]))
		{
			if (!grid_is_closed(cfg->grid, cfg->line_nb, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		grid_is_closed(char **grid, int line_nb, int i, int j)
{
	if (i == 0 && !is_space(grid[i][j]) && grid[i][j] != '1')
		return (0);
	if (i == line_nb - 1 && !is_space(grid[i][j]) && grid[i][j] != '1')
		return (0);
	if (i > 0 && is_space(grid[i][j]) && j < (int)ft_strlen(grid[i - 1])
					&& !is_space(grid[i - 1][j]) && grid[i - 1][j] != '1')
		return (0);
	if (i < line_nb - 1 && is_space(grid[i][j])
		&& j < (int)ft_strlen(grid[i + 1]) && !is_space(grid[i + 1][j])
												&& grid[i + 1][j] != '1')
		return (0);
	if (i > 0 && j >= (int)ft_strlen(grid[i - 1]) && grid[i][j] != '1'
												&& !is_space(grid[i][j]))
		return (0);
	if (i < line_nb - 1 && j >= (int)ft_strlen(grid[i + 1]) && grid[i][j] != '1'
													&& !is_space(grid[i][j]))
		return (0);
	return (1);
}
