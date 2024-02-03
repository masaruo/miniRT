# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 16:04:53 by mogawa            #+#    #+#              #
#    Updated: 2024/02/03 14:28:19 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	miniRT
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -MMD -MP
SRCDIR	:=	./src
OBJDIR	:=	./obj
LIBFTDIR	:=	./libft
LIBFT	:=	$(LIBFTDIR)/libft.a
MLXDIR	:=	./mlx
MLX		:=	$(MLXDIR)/libmlx_Darwin.a
INCLUDE	:=	-I./include -I$(LIBFTDIR)/include -I$(MLXDIR)
SRCS		:=	\
			get_next_line.c get_next_line_utils.c \
			math_utils.c \
			parse.c \
			phong.c \
			shadow.c \
			t_color.c \
			t_image.c \
			t_intersect.c \
			t_list.c \
			t_matrix.c \
			t_ray.c \
			t_shape.c \
			t_world.c \
			vec_utils.c \
			minirt.c
OBJS	:=	$(SRCS:%.c=$(OBJDIR)/%.o)
DEPS	:=	$(OBJS:%.o=%.d)
LDFLAGS	:=	-L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit -lm

ifdef WITH_DEBUG
CFLAGS	:=	-Wall -Wextra -g3 -O0 -DLEAK
endif

ifdef WITH_ASAN
CFLAGS	:=	-Wall -Wextra -g3 -O0 -fsanitize=address
endif

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(MLXDIR)
	$(CC) $(CFLAGS) $(LIBFT) $(MLX) $(LDFLAGS) $^ -o $@

debug: 
	$(RM) -r $(OBJDIR)
	$(MAKE) WITH_DEBUG=1 all

asan: 
	$(RM) -r $(OBJDIR)
	$(MAKE) WITH_ASAN=1 all

clean:
	$(RM) -r $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(MLXDIR)

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

dev: all
	./miniRT test_rt

re:	fclean all

-include $(DEPS)

.PHONY: clean fclean re debug asan