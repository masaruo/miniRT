/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tworld_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:42:43 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/08 19:31:40 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "t_world.h"

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
