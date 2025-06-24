# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 16:04:53 by mogawa            #+#    #+#              #
#    Updated: 2025/06/24 14:16:51 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	miniRT
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror -MMD -MP
LDFLAGS	:=	-L/usr/local/lib -lmlx -lX11 -lXext -lbsd -lm
DBGFLG	:=	-g3 -O0
SRCDIR	:=	./src
OBJDIR	:=	./obj
LIBFTDIR	:=	./libft
LIBFT	:=	$(LIBFTDIR)/libft.a
INCLUDE	:=	-I./include -I$(LIBFTDIR)/include -I/usr/local/include -I./mlx
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
			phong2.c \
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
CFLAGS	+=	$(DBGFLG) -DLEAK
endif

ifdef WITH_ASAN
CFLAGS	:=	$(filter-out -Werror, $(CFLAGS))
CFLAGS	+=	$(DBGFLG) -fsanitize=address
LDFLAGS	+=	-fsanitize=address
endif

ifdef WITH_BONUS
CFLAGS	+=	-DBONUS
endif

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $^ $(LDFLAGS) $(LIBFT) -o $@

leak:
	$(RM) -r $(OBJDIR)
	$(MAKE) WITH_LEAK=1 all

review: leak

bonus:
	$(RM) -r $(OBJDIR)
	$(MAKE) WITH_BONUS=1 WITH_LEAK=1 all

gdb:
	$(RM) -r $(OBJDIR)
	$(MAKE) WITH_ASAN=1 all

clean:
	$(RM) -r $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

dev: leak
	$(shell ./miniRT test.rt)

re:	fclean all

-include $(DEPS)

.PHONY: clean fclean re leak asan dev norm review
