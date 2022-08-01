/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:24:11 by vlugand-          #+#    #+#             */
/*   Updated: 2020/10/26 14:19:42 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# if defined(__linux__)
#  define MAC_OS		0
#  define LINUX			1
#  define W				119
#  define S				115
#  define A				97
#  define D				100
#  define ESC			65307
#  define LEFT			65361
#  define RIGHT			65363
#  define UP			65362
#  define SPACE			32
#  include "../mlx_linux/mlx.h"
# else
#  define MAC_OS		1
#  define LINUX			0
#  define W				13
#  define S				1
#  define A				0
#  define D				2
#  define ESC			53
#  define LEFT			123
#  define RIGHT			124
#  define UP				126
#  define SPACE			49
#  include "../mlx_OpenGL/mlx.h"
# endif

# define KEYPRESS		2
# define KEYRELEASE		3
# define DESTROYNOTIFY	17

typedef struct		s_cfg
{
	int				width;
	int				height;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	int				f[3];
	int				flag_f;
	int				c[3];
	int				flag_c;
	char			**grid;
	char			position;
	int				pos_x;
	int				pos_y;
	int				dir_x;
	int				dir_y;
	int				line_nb;
	int				line_max_len;
	int				count_lines;
	int				start_grid;
	int				success;
	int				sprites_nb;
	int				save;
}					t_cfg;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img;
	char			*img_data;
	int				endian;
	int				bpp;
	int				line_size;
	int				pixel;
	int				bg_color;
}					t_mlx;

typedef struct		s_bmp
{
	unsigned int	file_size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned int	pixel_data_offset;
	unsigned int	header_size;
	unsigned int	img_width;
	unsigned int	img_height;
	unsigned short	planes;
	unsigned short	bpp;
	unsigned int	compression;
	unsigned int	img_size;
	unsigned int	x_pixels_per_meter;
	unsigned int	y_pixels_per_meter;
	unsigned int	total_colors;
	unsigned int	important_colors;
}					t_bmp;

typedef struct		s_key
{
	int				fwd;
	int				bwd;
	int				r;
	int				l;
	int				cam_l;
	int				cam_r;
	int				run;
	int				space;
}					t_key;

typedef struct		s_tex
{
	void			*ptr;
	char			*data;
	int				bpp;
	int				line_size;
	int				endian;
	int				w;
	int				h;
}					t_tex;

typedef struct		s_rc
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			deltadist_x;
	double			deltadist_y;
	int				step_x;
	int				step_y;
	double			sidedist_x;
	double			sidedist_y;
	int				hit;
	int				side;
	double			perpwalldist;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				f_color;
	int				c_color;
	double			speed;
	double			rot;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				color;
	t_tex			xpm[8];
	double			sky_x;
}					t_rc;

typedef struct		s_sprite
{
	double			x;
	double			y;
}					t_sprite;

typedef struct		s_sc
{
	int				nb;
	double			*z_buffer;
	t_sprite		*spr;
	int				*spr_order;
	double			*spr_dist;
	double			spr_x;
	double			spr_y;
	double			inv;
	double			trsform_x;
	double			trsform_y;
	int				spr_screen_x;
	int				spr_h;
	int				spr_w;
	int				drawstart_x;
	int				drawstart_y;
	int				drawend_x;
	int				drawend_y;
	int				stripe;
	int				tex_x;
	int				tex_y;
	int				d;
	int				color;
}					t_sc;

typedef struct		s_fc
{
	int				x;
	int				y;
	float			f0raydir_x;
	float			f0raydir_y;
	float			f1raydir_x;
	float			f1raydir_y;
	int				p;
	float			pos_z;
	float			row_dist;
	float			floor_step_x;
	float			floor_step_y;
	float			floor_x;
	float			floor_y;
	int				cell_x;
	int				cell_y;
	int				color;
}					t_fc;

typedef struct		s_map
{
	int				i;
	int				j;
	int				tile_x;
	int				tile_y;
	int				next_tile_x;
	int				next_tile_y;
	int				tile_size;
}					t_minimap;

typedef struct		s_ratio
{
	double			ratio_x;
	double			ratio_y;
	int				x;
	int				y;
	int				xbis;
	int				ybis;
	int				color;
}					t_ratio;

typedef struct		s_all
{
	t_mlx			*mlx;
	t_cfg			*cfg;
	t_rc			*rc;
	t_key			*key;
	t_sc			*sc;
}					t_all;

void				skip_spaces(char *s, int *i);
int					is_nswe(char c);
int					is_space(char c);
int					str_isdigit(char *s);
void				free_all(t_cfg *cfg);
int					arg_errors(int argc, char **argv, t_all *all);
int					get_position(t_cfg *cfg, char c, int i);
int					check_open(char *path, int *fd);
char				*strdup_n_fill(char **line, t_cfg *cfg);
int					find_max_len(char *str);
void				clean_empty_lines(t_cfg *cfg);
int					check_xpm(t_cfg *cfg);
int					fc_already_exists(char *line, t_cfg *cfg);
int					key_is_valid(char c);
int					check_extension(char *path, char *ext);
int					init_parsing(char *cfg_file, t_cfg *cfg);
int					parse_data(char **line, t_cfg *cfg, int fd);
void				cfg_init(t_cfg *cfg);
int					store_grid(t_cfg *cfg, int fd);
int					check_missing_data(t_cfg *cfg);
int					assign_parsing(char *line, t_cfg *cfg);
int					fc_parsing(char *line, int (*array)[3], t_cfg *cfg);
int					textures_parsing(char *line, t_cfg *cfg);
int					get_path(char *line, char **path);
int					res_parsing(char *line, t_cfg *cfg);
int					grid_check(char *line, t_cfg *cfg);
int					grid_parsing(t_cfg *cfg, char *cfg_file);
int					check_grid_columns(t_cfg *cfg);
int					grid_is_closed(char **grid, int line_nb, int i, int j);
int					check_grid_lines(char *line, t_cfg *cfg);
int					struct_all_init(t_all *all);
void				t_mlx_init(t_mlx *mlx, t_cfg *cfg);
void				t_key_init(t_key *key);
void				t_rc_init(t_rc *rc, t_cfg *cfg);
int					sc_init(t_all *all);
void				get_sprites_nb(t_cfg cfg, t_sc *sc);
void				get_sprites_xy(t_cfg cfg, t_sc *sc);
void				ft_swap(int *a, int *b);
void				ft_dblswap(double *a, double *b);
int					render_next_frame(t_all *all);
void				draw_verline(t_all *all, t_rc rc, t_tex tex, int x);
void				draw_to_image(t_mlx *mlx, int color, int x, int y);
int					create_trgb(int r, int g, int b);
int					get_pixel_color(t_tex *tex, int x, int y);
void				gradient(t_mlx *mlx);
int					keys_action(t_all *all);
int					ft_key_press(int keycode, t_all *all);
int					ft_key_release(int keycode, t_all *all);
int					clic_red_button(t_all *all);
void				move_left(t_rc *rc, t_cfg *cfg);
void				move_right(t_rc *rc, t_cfg *cfg);
void				move_fwd(t_rc *rc, t_cfg *cfg);
void				move_bwd(t_rc *rc, t_cfg *cfg);
void				run_fwd(t_all *all);
void				rotate_right(t_rc *rc);
void				rotate_left(t_rc *rc);
t_tex				load_texture(t_all *all, char *path);
void				init_textures(t_all *all);
void				print_tex_to_wall(t_rc *rc, t_cfg *cfg, t_tex tex);
void				get_wall_data(t_rc *rc, t_cfg *cfg);
void				perform_dda(t_rc *rc, t_cfg *cfg);
void				get_step_and_sidedist(t_rc *rc);
void				prepare_new_ray(t_rc *rc, t_cfg *cfg, int x);
void				raycasting(t_all *all);
void				sort_sprites(int *order, double *distance, int number);
void				calculate_sprite_distance(t_sc *sc, t_rc *rc);
void				get_sprite_onscreen_data(t_sc *sc, t_rc *rc, t_cfg *cfg,
																	int i);
void				display_sprite(t_sc *sc, t_cfg *cfg, t_tex *tex,
																t_mlx *mlx);
void				spritecasting(t_all *all);
void				get_floor_data(t_fc *fc, t_rc *rc, t_cfg *cfg);
void				floorcasting(t_rc *rc, t_cfg *cfg, t_tex tex, t_mlx *mlx);
void				mini_map(t_all *all);
void				draw_tiles(t_minimap *mm, t_all *all, int i, int j);
void				init_mini_map(t_minimap *mm, t_cfg *cfg);
void				set_to_null(t_all *all);
void				clean_mem(t_all *all);
void				clean_mem_2(t_all *all);
void				clean_mem_3(t_all *all);
void				clean_exit(t_all *all, int status);
void				write_file_failure(t_all *all);
t_bmp				header_init(t_cfg *cfg, t_mlx *mlx);
void				render_first_img(t_all *all);
void				save_screen_bmp(t_all *all);
void				draw_skybox(t_all *all, int x, int drawstart, t_tex sky);
void				title_screen(t_all *all);
void				draw_ratio(t_all *all, t_tex *img);
int					exit_parsing_fail(t_all *all);
int					exit_args_error(t_all *all);

#endif
