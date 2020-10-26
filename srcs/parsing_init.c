/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:53:42 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/26 14:22:04 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_parsing(char *cub_file, t_cfg *cfg)
{
	int		fd;
	int		ret;
	char	*line;

	cfg_init(cfg);
	if (!check_open(cub_file, &fd))
		return (0);
	while ((ret = get_next_line(fd, &line, 1, 0)) >= 0)
	{
		cfg->count_lines++;
		if (!parse_data(&line, cfg, fd))
			return (0);
		if (line)
			free(line);
		line = NULL;
		if (ret == 0)
			break ;
	}
	close(fd);
	if (!check_xpm(cfg))
		return (0);
	if (!grid_parsing(cfg, cub_file))
		return (0);
	clean_empty_lines(cfg);
	return (1);
}

int		parse_data(char **line, t_cfg *cfg, int fd)
{
	int		ret;

	ret = assign_parsing(*line, cfg);
	if (ret >= 0)
		return (1);
	else if (ret == -1)
		write(1, "Error\nInvalid res.\n", 19);
	else if (ret == -2)
		write(1, "Error\nInvalid textures. Check XPM files and paths.\n", 51);
	else if (ret == -3)
		write(1, "Error\nInvalid floor data.\n", 26);
	else if (ret == -4)
		write(1, "Error\nInvalid ceiling data.\n", 28);
	else if (ret == -6)
		write(1, "Error\nInvalid grid.\n", 20);
	else if (ret == -7)
		write(1, "Error\nCorrupted config file.\n", 30);
	if (*line)
		free(*line);
	*line = NULL;
	get_next_line(fd, line, 1, 1);
	close(fd);
	write(1, "\nAborting...\n", 13);
	return (0);
}

int		check_missing_data(t_cfg *cfg)
{
	if (!cfg->width || !cfg->height)
		write(1, "Error\nMissing resolution details.\n", 35);
	else if (!cfg->no || !cfg->so || !cfg->ea || !cfg->we || !cfg->sprite)
		write(1, "Error\nMissing or invalid textures.\n", 36);
	else if (!cfg->no || !cfg->so || !cfg->ea || !cfg->we || !cfg->sprite)
		write(1, "Error\nMissing or invalid textures.\n", 36);
	else if (cfg->flag_c == 0 || cfg->flag_f == 0)
		write(1, "Error\nMissing or invalid floor / ceiling info.\n", 48);
	else
		return (1);
	return (0);
}

int		store_grid(t_cfg *cfg, int fd)
{
	char	*line;
	int		i;
	int		ret;

	if (!(cfg->grid = (char**)malloc((1 + cfg->line_nb) * sizeof(char *))))
		return (0);
	i = 0;
	while (i < cfg->line_nb && (ret = get_next_line(fd, &line, 1, 0)) >= 0)
	{
		cfg->grid[i] = strdup_n_fill(&line, cfg);
		i++;
		if (ret == 0)
			break ;
	}
	cfg->grid[i] = 0;
	close(fd);
	return (1);
}
