/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/06 16:30:57 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include "t_world.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

#define window_width 512
#define window_height 512

void	sphere(t_world const *world)
{
	t_vec3			camera_vec;
	t_vec3			sphere_vec;
	t_vec3			screen_vec;
	t_vec3			dir_vec;
	double const	sphere_r = 1;

	camera_vec = vec3_init(0, 0, -5);
	sphere_vec = vec3_init(0, 0, 5);
	for (double y = 0; y < window_height; y++)
	{
		for (double x = 0; x < window_width; x++)
		{
			screen_vec = vec3_init(2 * x / (window_width - 1) - 1, 2 * y / (window_height - 1) - 1, 0);//x, y をスクリーン座標に転換（-1.0 - 1）
			dir_vec = vec3_subtract(&screen_vec, &camera_vec);
			dir_vec = vec3_normalize(&dir_vec);//レイの方向ベクトル
			t_vec3	camera_to_sphere;
			camera_to_sphere = vec3_subtract(&sphere_vec, &camera_vec);
			// camera_to_sphere = vec3_subtract(&camera_vec, &sphere_vec);

			// the ray hits the sphere?
			double a = vec3_lengthSq(&dir_vec);
			double b = 2 * vec3_dot(&camera_to_sphere, &dir_vec);
			double c = vec3_dot(&camera_to_sphere, &camera_to_sphere) - sphere_r * sphere_r;
			double d = b * b - 4 * a * c;
			if (d >= 0)
			{
				my_mlx_pixcel_put(world->mlx_ptr, world->screen_witdh, world->screen_height, 0x00FF0000);
			}
			else
			{
				my_mlx_pixcel_put(world->mlx_ptr, world->screen_witdh, world->screen_height, 0x000000FF);
			}
		}
	}
	mlx_put_image_to_window(world->mlx_ptr, world->win_ptr, world->img.img_ptr, world->screen_witdh, world->screen_height);
	return ;
}

int	main(void)
{
	t_world	world;

	//todo parse check
	world = tworld_init();
	sphere(&world);
	return (EXIT_SUCCESS);
}
