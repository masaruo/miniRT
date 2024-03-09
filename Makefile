# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 16:04:53 by mogawa            #+#    #+#              #
#    Updated: 2024/03/09 10:55:09 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	miniRT
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror -MMD -MP
LDFLAGS	:=	-L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit -lm
DBGFLG	:=	-g3 -O0
SRCDIR	:=	./src
OBJDIR	:=	./obj
LIBFTDIR	:=	./libft
LIBFT	:=	$(LIBFTDIR)/libft.a
MLXDIR	:=	./mlx
MLX		:=	$(MLXDIR)/libmlx_Darwin.a
INCLUDE	:=	-I./include -I$(LIBFTDIR)/include -I$(MLXDIR)
SRCS		:=	\
			destructor.c \
			ft_atod.c \
			get_next_line.c get_next_line_utils.c \
			key.c \
			math_utils.c \
			minirt.c \
			parse.c \
			parse2.c \
			phong.c \
			shadow.c \
			t_camera.c \
			t_color.c \
			t_color2.c \
			t_cylinder.c \
			t_cylinder2.c \
			t_image.c \
			t_intersect.c \
			t_plane.c \
			t_ray.c \
			t_sphere.c \
			t_vec3_utils.c \
			t_vec3_utils2.c \
			t_vec3_utils3.c \
			t_world.c \
			validation.c \
			wrapper.c \
			wrapper2.c \
			main.c
OBJS	:=	$(SRCS:%.c=$(OBJDIR)/%.o)
DEPS	:=	$(OBJS:%.o=%.d)

ifdef WITH_LEAK
CFLAGS	:=	$(filter-out -Werror, $(CFLAGS))
CFLAGS	+=	$(DBGFLG) -DLEAK
endif

ifdef WITH_ASAN
CFLAGS	:=	$(filter-out -Werror, $(CFLAGS))
CFLAGS	+=	$(DBGFLG) -fsanitize=address
LDFLAGS	+=	-fsanitize=address
endif

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(MLXDIR)
	$(CC) $(LDFLAGS) $(LIBFT) $(MLX) $^ -o $@

leak: 
	$(RM) -r $(OBJDIR)
	$(MAKE) WITH_LEAK=1 all

review: leak

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

dev: asan
	$(shell ./miniRT maps/test.rt)

re:	fclean all

norm:
	$(shell echo 'norminette ./include ./src ./libft')

-include $(DEPS)

.PHONY: clean fclean re leak asan dev norm review
