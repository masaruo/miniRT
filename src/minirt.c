/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 16:55:15 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include "t_world.h"
#include "mlx.h"
#include "t_color.h"
#include "math_utils.h"
#include "t_ray.h"
#include "t_shape.h"
#include "t_light.h"
#include "t_intersect.h"
#include "libft.h"
#include "phong.h"
#include "parse.h"
#include "ft_atod.h"
#include "destructor.h"
#include "t_camera.h"
#define X (0)
#define Y (1)

static double	\
	_get_screen_coord(double raw, int x_or_y, double width, double height)
{
	if (x_or_y == X)
	{
		return (raw - (width - 1) / 2);
	}
	else
	{
		return ((height - 1) / 2 - raw);
	}
}

static void	paint_each_xy_pixcel(t_world *world)
{
	t_ray		eye_ray;
	t_color		paint_color;
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
			_get_screen_coord(x, X, world->screen_witdh, world->screen_height), \
			_get_screen_coord(y, Y, world->screen_witdh, world->screen_height), \
				world->screen_witdh);
			paint_color = get_color_at_xy_coord(world, &eye_ray);
			my_mlx_pixcel_put(&world->img, x, y, tcolor_to_hex(paint_color));
			x++;
		}
		y++;
	}
}

int	minirt_main(char const *file_name)
{
	t_world	world;
	int		status;

	world = tworld_init();
	parse_main(file_name, &world);
	paint_each_xy_pixcel(&world);
	mlx_put_image_to_window(world.mlx_ptr, world.win_ptr, world.img.ptr, 0, 0);
	mlx_key_hook(world.win_ptr, deal_key, &world);
	mlx_hook(world.win_ptr, 17, 1L << 3, click_close_button, &world);
	mlx_loop(world.mlx_ptr);
	status = ft_destructor(&world);
	return (status);
}
