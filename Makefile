# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 16:04:53 by mogawa            #+#    #+#              #
#    Updated: 2024/01/05 13:53:31 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	miniRT
CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -MMD -MP
SRCDIR	:=	./src
OBJDIR	:=	./obj
LIBFTDIR	:=	./libft
LIBFT	:=	$(LIBFTDIR)/libft.a
MLXDIR	:=	./mlx
MLX		:=	$(MLXDIR)/libmlx_Darwin.a
INCLUDE	:=	-I./include -I$(LIBFTDIR)/include -I$(MLXDIR)
SRCS		:=	\
			\
			minirt.c
OBJS	:=	$(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)
DEPS	:=	$(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.d)
LDFLAGS	:=	-L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit -lm

ifdef WITH_DEBUG
CFLAGS	:=	-Wall -Wextra -g3 -O0 -DLEAK
endif

ifdef WITH_ASAN
CFLAGS	:=	-Wall -Wextra -g3 -O0 -fsanitize=address
endif

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all:	$(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(MLXDIR)
	$(CC) $(CFLAGS) $(LIBFT) $(MLX) $(LDFLAGS) $^ -o $@

debug: fclean
	$(MAKE) $(NAME) WITH_DEBUG

asan: fclean
	$(MAKE) $(NAME) WITH_ASAN

clean:
	$(RM) -r $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(MLXDIR)

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re:	fclean all

-include $(DEPS)

.PHONY: clean fclean re debug asan