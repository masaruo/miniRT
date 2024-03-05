/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_world.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:42:43 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 11:43:38 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "t_world.h"
#include "wrapper.h"
#include "libft.h"

t_world	tworld_init(void)
{
	t_world	world;

	world.screen_witdh = WIDTH;
	world.screen_height = HEIGHT;
	world.mlx_ptr = mlx_init();
	if (!world.mlx_ptr)
	{
		ft_perror_exit(EXIT_FAILURE, "mlx_init function failed.");
	}
	world.win_ptr = mlx_new_window(world.mlx_ptr, WIDTH, HEIGHT, TITLE);
	if (!world.win_ptr)
	{
		ft_perror_exit(EXIT_FAILURE, "mlx_new_window function failed.");
	}
	world.img = timage_init(world.mlx_ptr, WIDTH, HEIGHT);
	world.shapes = ft_lstnew(NULL);
	world.lights = ft_lstnew(NULL);
	return (world);
}
