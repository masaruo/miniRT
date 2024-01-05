/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tworld_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:42:43 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/05 18:13:58 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "t_world.h"

t_world	tworld_init(void)
{
	t_world	world;

	world.screen_witdh = WITDH;
	world.screen_height = HEIGHT;
	world.mlx = mlx_init();
	//todo error
	world.win = mlx_new_window(world.mlx, world.screen_witdh, world.screen_height, TITLE);
	//todo error
	return (world);
}
