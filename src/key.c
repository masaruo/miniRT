/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:37:01 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/07 16:26:32 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "destructor.h"
#include "mlx.h"

#define ESC (65307)
#define KEY_UP (65362)
#define KEY_DOWN (65364)
#define KEY_RIGHT (65363)
#define KEY_LEFT (65361)
#define KEY_ROTATE (114)//r
#define KEY_REV_ROTATE (116)//t
#define KEY_Z_PLUS (122)//z
#define KEY_Z_MINUS (120)//x

#ifdef LEAK

static void	print_camera_data(t_world *world)
{
	t_vec3_pos	pos;
	t_vec3_pos	face;

	pos = world->camera.position;
	face = world->camera.orientation;
	dprintf(2, "camera coord[x:%.f][y:%.f][z:%.f]", pos.x, pos.y, pos.z);
	dprintf(2, "&facing[x:%.4f][y:%.4f][z:%.4f]\n", face.x, face.y, face.z);
}

int	hook_keys(int key, t_world *world)
{
	if (key == ESC)
		ft_destructor(world);
	else if (key == KEY_DOWN)
		world->camera.position.y -= 1.0;
	else if (key == KEY_UP)
		world->camera.position.y += 1.0;
	else if (key == KEY_RIGHT)
		world->camera.position.x += 1.0;
	else if (key == KEY_LEFT)
		world->camera.position.x -= 1.0;
	else if (key == KEY_ROTATE)
		world->camera.orientation.y += 1.0;
	else if (key == KEY_REV_ROTATE)
		world->camera.orientation.y -= 1.0;
	else if (key == KEY_Z_PLUS)
		world->camera.position.z += 1.0;
	else if (key == KEY_Z_MINUS)
		world->camera.position.z -= 1.0;
	else
		return (EXIT_FAILURE);
	print_camera_data(world);
	paint_each_xy_pixcel(world);
	mlx_put_image_to_window(\
	world->mlx_ptr, world->win_ptr, world->img.ptr, 0, 0);
	return (EXIT_SUCCESS);
}

#else

int	hook_keys(int key, t_world *world)
{
	if (key == ESC)
		ft_destructor(world);
	return (EXIT_SUCCESS);
}

#endif
