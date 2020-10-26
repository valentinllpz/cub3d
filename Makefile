# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 17:58:20 by vlugand-          #+#    #+#              #
#    Updated: 2020/10/26 14:38:04 by vlugand-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	cub3D

OS			= 	${shell uname}

SRCS_BONUS 	=	srcs/draw_misc_bonus.c\
				srcs/floorcasting_bonus.c\
				srcs/minimap_bonus.c\
				srcs/skybox_bonus.c

SRCS = 			srcs/clean_memory.c\
				srcs/events.c\
				srcs/exit.c\
				srcs/main.c\
				srcs/move.c\
				srcs/parsing_data.c\
				srcs/parsing_grid.c\
				srcs/parsing_init.c\
				srcs/raycasting.c\
				srcs/rotate.c\
				srcs/save_bmp.c\
				srcs/sprites.c\
				srcs/structs_init.c\
				srcs/textures.c\
				srcs/utils_1.c\
				srcs/utils_2.c\
				srcs/utils_3.c\
				srcs/utils_mlx.c\
				srcs/utils_sprites.c

ifeq ($(MAKECMDGOALS), bonus)
	CFLAGS	= 	-Wall -Werror -Wextra -D BONUS=1
else ifeq ($(MAKECMDGOALS), rebonus)
	CFLAGS	= 	-Wall -Werror -Wextra -D BONUS=1
else
	CFLAGS	=   -Wall -Werror -Wextra -D BONUS=0
endif

ifeq ($(OS), Linux)
	MLX_DIR	=	mlx_linux
	MLX_LNK	=	-L ${MLX_DIR} -lmlx -lXext -lX11 -lbsd -lm
	SRCS	+=	srcs/utils_linux.c
else
	MLX_DIR	= mlx_OpenGL
	MLX_LNK	= -L ${MLX_DIR} -lmlx -framework OpenGL -framework AppKit
	SRCS	+=	srcs/utils_mac.c
endif

CC			= 	gcc
OBJS		= 	${SRCS:.c=.o}
OBJS_BONUS 	= 	${SRCS_BONUS:.c=.o}
LIBS		=	-L libft -lft ${MLX_LNK}
RM			= 	rm -f

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

mlx:
			@echo "\033[0;35m\033[1mPreparing MLX...\033[0m"
			@make 2>/dev/null -C ${MLX_DIR}
			@echo "\033[0;36m\033[1mMLX is ready to use.\033[0m"

lbft:
			@echo "$(tput bold)\033[0;35m\033[1mPreparing Libft...\033[0m$(tput sgr0)"
			@make bonus -C libft
			@echo "\033[0;36m\033[1mLibft is ready to use.\033[0m"
			
${NAME}:	${OBJS_PATH} ${OBJS} lbft mlx
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME}
			@echo "\033[0;32m\033[1mCub3D is now ready! Use the command \"./cub3D\" with the .cub file of your choice.\033[0m"
			@echo "Please note that you compiled a version \033[1mwithout bonus\033[0m, for a better experience use \033[1m\"make rebonus\"\033[0m"

clean:		
			@make clean -C libft
			@make clean -C ${MLX_DIR}
			${RM} ${OBJS} ${OBJS_BONUS}
			@echo "\033[0;35m\033[1mCleaned all .o files.\033[0m"

fclean:		clean
			@make fclean -C libft
			@make clean -C ${MLX_DIR}
			${RM} ${NAME}
			@echo "\033[0;35m\033[1mCleaned all .o files and executable.\033[0m"

re:			fclean all

bonus:		${OBJS_PATH} ${OBJS} ${OBJS_BONUS} lbft mlx
			${CC} ${CFLAGS} ${OBJS} ${OBJS_BONUS} ${LIBS} -o ${NAME}
			@echo "\033[0;32m\033[1mCub3D is now ready! Use the command \"./cub3D\" with the .cub file of your choice.\033[0m"

rebonus:	fclean bonus

.PHONY:		all clean fclean re bonus rebonus