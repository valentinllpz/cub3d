/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:35:32 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/19 14:55:56 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_all	all;

	if (!struct_all_init(&all))
		return (1);
	if (!arg_errors(argc, argv, &all))
		return (exit_args_error(&all));
	if (!init_parsing(argv[1], all.cfg))
		return (exit_parsing_fail(&all));
	t_mlx_init(all.mlx, all.cfg);
	t_key_init(all.key);
	t_rc_init(all.rc, all.cfg);
	init_textures(&all);
	sc_init(&all);
	render_first_img(&all);
	if (all.cfg->save)
		save_screen_bmp(&all);
	mlx_hook(all.mlx->win, KEYPRESS, 1L << 0, ft_key_press, &all);
	mlx_hook(all.mlx->win, KEYRELEASE, 1L << 1, ft_key_release, &all);
	mlx_hook(all.mlx->win, DESTROYNOTIFY, 1L << 17, clic_red_button, &all);
	mlx_loop_hook(all.mlx->ptr, render_next_frame, &all);
	mlx_loop(all.mlx->ptr);
	return (0);
}
