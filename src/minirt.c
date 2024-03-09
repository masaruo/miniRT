/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/09 10:49:34 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_world.h"
#include "mlx.h"
#include "t_color.h"
#include "t_ray.h"
#include "parse.h"
#include "destructor.h"
#define X (0)
#define Y (1)

static double	\
	convert_to_screen_coord_(double raw, int x_or_y, double screen_size)
{
	if (x_or_y == X)
	{
		return (raw - (screen_size - 1) / 2);
	}
	else
	{
		return ((screen_size - 1) / 2 - raw);
	}
}

void	paint_each_xy_pixcel(t_world *world)
{
	t_ray		eye_ray;
	t_color		color_to_paint;
	double		x;
	double		y;

	y = 0;
	while (y < world->screen_height)
	{
		x = 0;
		while (x < world->screen_witdh)
		{
			eye_ray = \
			get_camera_ray(world->camera, \
			convert_to_screen_coord_(x, X, world->screen_witdh), \
			convert_to_screen_coord_(y, Y, world->screen_height), \
			world->screen_witdh);
			color_to_paint = get_color_at_xy_coord(world, &eye_ray);
			my_mlx_pixcel_put(&world->img, x, y, tcolor_to_hex(color_to_paint));
			x++;
		}
		y++;
	}
}

void	minirt_main(char const *file_name)
{
	t_world	world;

	world = tworld_init();
	parse_main(file_name, &world);
	paint_each_xy_pixcel(&world);
	mlx_put_image_to_window(world.mlx_ptr, world.win_ptr, world.img.ptr, 0, 0);
	mlx_key_hook(world.win_ptr, hook_keys, &world);
	mlx_hook(world.win_ptr, 17, 1L << 3, click_close_button, &world);
	mlx_loop(world.mlx_ptr);
	ft_destructor(&world);
}
