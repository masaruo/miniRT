/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 14:20:40 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include "t_world.h"
#include "mlx.h"
#include "t_color.h"
#include "math_utils.h"
#include <stdlib.h>
#include <math.h>
#include "t_ray.h"
#include "t_shape.h"
#include "t_light.h"
#include "t_intersect.h"
#include "libft.h"
#include <limits.h>
#include "phong.h"
#include "parse.h"
#include "ft_atod.h"
#include "destructor.h"
#include "t_camera.h"

void	get_intersect_with_shape(t_world *world, t_image const *image)
{
	t_ray	eye_ray;
	double	screen_x;
	double	screen_y;
	t_intersect	intersection;
	t_color		phong_color;

	for (double y = 0; y < world->screen_height; y++)
	{
		for (double x = 0; x < world->screen_witdh; x++)
		{
			screen_x = x - (world->screen_witdh - 1) / 2;
			screen_y = (world->screen_height - 1) / 2 - y;
			eye_ray = get_camera_ray(world->camera, screen_x, screen_y, world->screen_witdh);
			intersection.distance = __DBL_MAX__;
			if (test_all_intersection(world->shapes, &eye_ray, &intersection) == true)
			{
				phong_color = tcolor_calc_phong(world, &intersection, &eye_ray);
				my_mlx_pixcel_put(image, x, y, tcolor_to_hex(phong_color));
			}
			else
			{
				my_mlx_pixcel_put(image, x, y, get_hex_color(100, 149, 237));
			}
		}
	}
}

int	minirt_main(char const *file_name)
{
	t_world	world;
	int		status;

	world = tworld_init();
	parse_main(file_name, &world);
	get_intersect_with_shape(&world, &world.img);
	mlx_put_image_to_window(world.mlx_ptr, world.win_ptr, world.img.ptr, 0, 0);
	mlx_key_hook(world.win_ptr, deal_key, &world);
	mlx_hook(world.win_ptr, 17, 1L << 3, click_close_button, &world);
	mlx_loop(world.mlx_ptr);
	status = destructor(&world);
	return (status);
}
