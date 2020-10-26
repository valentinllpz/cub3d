/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:11:54 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/26 14:21:54 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		clic_red_button(t_all *all)
{
	clean_mem(all);
	clean_mem_2(all);
	mlx_destroy_window(all->mlx->ptr, all->mlx->win);
	if (all->mlx->ptr)
		free(all->mlx->ptr);
	clean_mem_3(all);
	exit(EXIT_SUCCESS);
	return (1);
}

int		exit_args_error(t_all *all)
{
	clean_mem_3(all);
	return (1);
}

int		exit_parsing_fail(t_all *all)
{
	clean_mem(all);
	clean_mem_3(all);
	return (1);
}
