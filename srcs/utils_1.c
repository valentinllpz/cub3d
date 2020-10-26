/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 18:11:58 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/14 16:43:21 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		arg_errors(int argc, char **argv, t_all *all)
{
	if (argc > 3 || argc < 2)
	{
		write(1, "Error\nInvalid arguments number.\n\nAborting...\n", 46);
		return (0);
	}
	if (!(check_extension(argv[1], ".cub")))
	{
		write(1, "Error\nInvalid description file.\n\nAborting...\n", 46);
		return (0);
	}
	all->cfg->save = 0;
	if (argc == 3)
	{
		if (ft_memcmp(argv[2], "--save", ft_strlen(argv[2])) != 0)
		{
			write(1, "Error\n2nd argument should be \"--save\".\n", 39);
			write(1, "\nAborting...\n", 14);
			return (0);
		}
		all->cfg->save = 1;
	}
	return (1);
}

int		get_position(t_cfg *cfg, char c, int i)
{
	if (!is_nswe(c))
		return (0);
	cfg->position = c;
	cfg->pos_x = i;
	cfg->pos_y = cfg->line_nb;
	if (c == 'E')
		cfg->dir_x = 1;
	else if (c == 'W')
		cfg->dir_x = -1;
	else if (c == 'S')
		cfg->dir_y = 1;
	else if (c == 'N')
		cfg->dir_y = -1;
	return (1);
}

int		check_open(char *path, int *fd)
{
	if ((*fd = open(path, O_RDONLY)) < 0)
	{
		write(1, "Error\nCouldn't open the file \"", 30);
		ft_putstr_fd(path, 1);
		write(1, "\". Please check if the path is correct.\n\n", 41);
		write(1, "Aborting...\n", 12);
		return (0);
	}
	return (1);
}

char	*strdup_n_fill(char **line, t_cfg *cfg)
{
	int		i;
	char	*s;

	if (!(*line))
		return (NULL);
	if (!(s = (char *)malloc(cfg->line_max_len + 1)))
		return (NULL);
	i = 0;
	while ((*line)[i] && i < cfg->line_max_len)
	{
		s[i] = (*line)[i];
		i++;
	}
	free(*line);
	while (i < cfg->line_max_len)
	{
		s[i] = ' ';
		i++;
	}
	s[cfg->line_max_len] = '\0';
	return (s);
}

int		find_max_len(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i > 0)
		i--;
	while (is_space(str[i]))
		i--;
	return (i + 1);
}
