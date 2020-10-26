/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 17:39:25 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/14 16:42:18 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_spaces(char *s, int *i)
{
	while (s[*i] && ((s[*i] > 8 && s[*i] < 14) || s[*i] == ' '))
		(*i)++;
}

int		is_nswe(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	else
		return (0);
}

int		is_space(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (1);
	else
		return (0);
}

int		str_isdigit(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	skip_spaces(str, &i);
	while (i < len)
	{
		if (is_space(str[i]))
		{
			skip_spaces(str, &i);
			if (str[i])
				return (0);
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_all(t_cfg *cfg)
{
	int		i;

	i = 0;
	while (cfg->grid[i])
	{
		if (cfg->grid[i])
		{
			free(cfg->grid[i]);
			cfg->grid[i] = NULL;
		}
		i++;
	}
	if (cfg->grid[i])
	{
		free(cfg->grid);
		cfg->grid = NULL;
	}
}
