/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_world.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:42:43 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/16 21:13:35 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "t_world.h"

static t_list	parse_input(char *line)
{
	char const	**input = ft_split(line, ' ');
	char const	*identifier = input[0];

	if (ft_strcmp(identifier, "sp") == 0 || ft_strcmp(identifier, "pl") == 0)
		return ;
	else
		return ;
}

t_world	tworld_init(int in_witdh, int in_height)
{
	t_world	world;

	world.screen_witdh = in_witdh;
	world.screen_height = in_height;
	world.mlx_ptr = mlx_init();
	//todo error
	world.win_ptr = mlx_new_window(world.mlx_ptr, world.screen_witdh, world.screen_height, TITLE);
	//todo error
	// world.img = timage_init(world.mlx_ptr, WITDH, HEIGHT);
	return (world);
}
