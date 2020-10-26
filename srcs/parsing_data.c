/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:23:44 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/26 14:59:07 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		assign_parsing(char *line, t_cfg *cfg)
{
	int		i;
	int		ret;

	i = 0;
	skip_spaces(line, &i);
	if (!cfg->start_grid && !(line[i] >= '0' && line[i] <= '2'))
	{
		if (!key_is_valid(line[i]))
			return (-7);
		if (line[i] == 'R' && (ret = res_parsing(line + i + 1, cfg)) == 0)
			return (-1);
		if (is_nswe(line[i]) && (ret = textures_parsing(line + i, cfg)) == 0)
			return (-2);
		if (line[i] == 'F' && (ret = fc_parsing(line + i, &cfg->f, cfg)) == 0)
			return (-3);
		if (line[i] == 'C' && (ret = fc_parsing(line + i, &cfg->c, cfg)) == 0)
			return (-4);
	}
	if ((line[i] >= '0' && line[i] <= '2') && (ret = grid_check(line, cfg)) < 0)
		return (ret);
	if (line[i] && ret == 0)
		return (-7);
	if (!line[i] && cfg->start_grid)
		cfg->line_nb++;
	return (1);
}

int		res_parsing(char *line, t_cfg *cfg)
{
	int		i;

	i = 0;
	if (cfg->width || cfg->height)
		return (0);
	skip_spaces(line, &i);
	if (!ft_isdigit(line[i]))
		return (0);
	if ((cfg->width = ft_atoi(line + i)) < 300)
		cfg->width = 300;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	if (!ft_isdigit(line[i]))
		return (0);
	if ((cfg->height = ft_atoi(line + i)) < 300)
		cfg->height = 300;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	skip_spaces(line, &i);
	if (line[i] == '\0')
		return (1);
	return (0);
}

int		get_path(char *line, char **path)
{
	int		i;
	int		len;

	i = 0;
	skip_spaces(line, &i);
	if (i == 0)
		return (0);
	len = 0;
	while (line[i])
	{
		i++;
		len++;
	}
	if (!(*path = (char *)malloc((len + 1) * sizeof(char))))
		return (0);
	(*path)[len] = '\0';
	while (len > 0)
	{
		len--;
		(*path)[len] = line[i - 1];
		i--;
	}
	if (!(check_extension(*path, ".xpm")))
		return (0);
	return (1);
}

int		textures_parsing(char *line, t_cfg *cfg)
{
	int		ret;

	if (line[0] == 'N' && line[1] == 'O' && !cfg->no)
		ret = get_path(line + 2, &cfg->no);
	else if (line[0] == 'S' && line[1] == 'O' && !cfg->so)
		ret = get_path(line + 2, &cfg->so);
	else if (line[0] == 'W' && line[1] == 'E' && !cfg->we)
		ret = get_path(line + 2, &cfg->we);
	else if (line[0] == 'E' && line[1] == 'A' && !cfg->ea)
		ret = get_path(line + 2, &cfg->ea);
	else if (line[0] == 'S' && !cfg->sprite)
		ret = get_path(line + 1, &cfg->sprite);
	else
		ret = 0;
	return (ret);
}

int		fc_parsing(char *line, int (*array)[3], t_cfg *cfg)
{
	int		i;
	int		flag;
	char	**split;

	split = ft_split(line + 1, ',');
	flag = 0;
	i = 0;
	while (split[i])
	{
		if (i < 3 && str_isdigit(split[i]) &&
			(((*array)[i] = ft_atoi(split[i])) <= 255))
			flag++;
		free(split[i]);
		i++;
	}
	free(split);
	if (flag != 3 || i != 3 || fc_already_exists(line, cfg))
		return (0);
	cfg->flag_f = (line[0] == 'F') ? 1 : cfg->flag_f;
	cfg->flag_c = (line[0] == 'C') ? 1 : cfg->flag_c;
	return (1);
}
