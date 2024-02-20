/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/20 14:42:54 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include "t_world.h"
#include "mlx.h"
#include "t_color.h"
#include "math_utils.h"
#include <stdlib.h>
// #include <stdio.h>
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
	t_vec3 pw;
	t_ray	eye_ray;

	
	pw.z = 0;
	for (double y = 0; y < world->screen_height; y++)
	{
		pw.y = -2 * y / (world->screen_height - 1) + 1;
		for (double x = 0; x < world->screen_witdh; x++)
		{
			pw.x = 2 * x / (world->screen_witdh - 1) - 1;

			

			
			double masaru_x = x - (world->screen_witdh - 1) / 2;
			double masaru_y = (world->screen_height - 1) / 2 - y;

		// 	//! junnetwork
			double sw = x - (world->screen_witdh - 1) / 2;
			double sy = (world->screen_height - 1) / 2 - y;
			double d = (world->screen_witdh / 2) / tan(convert_degree_to_radian(world->camera.field_of_view / 2));
			
			t_vec3 d_center = vec3_multiply(world->camera.orientation, d);

		// カメラが真上と真下を向いている時はエッジケース
			
			t_vec3 x_basis;
			x_basis.x = d_center.z / sqrt(pow(d_center.z, 2) + pow(d_center.x, 2));
			x_basis.y = 0;
			x_basis.z = -d_center.x / sqrt(pow(d_center.z, 2) + pow(d_center.x, 2));
			world->camera.x_basis = x_basis;

			t_vec3 y_basis;
			t_vec3 tmp = vec3_multiply(d_center, -1);
			y_basis = vec3_cross(x_basis, tmp);
			y_basis = vec3_normalize(y_basis);
			world->camera.y_basis = y_basis;
			
				if (world->camera.orientation.x == 0 && world->camera.orientation.y != 0 && world->camera.orientation.z == 0)
				{
					if (world->camera.orientation.y > 0)
					{
						x_basis = vec3_init(-1, 0, 0);
						y_basis = vec3_init(0, 0, -1);
					}
					else
					{
						x_basis = vec3_init(1, 0, 0);
						y_basis = vec3_init(0, 0, 1);
					}
				}

			t_vec3 xx = vec3_multiply(world->camera.x_basis, sw);
			t_vec3 yy = vec3_multiply(world->camera.y_basis, sy);

			t_vec3 ray_direction;
			ray_direction = vec3_add(xx, yy);
			ray_direction = vec3_add(d_center, ray_direction);
			ray_direction = vec3_normalize(ray_direction);

			t_ray	eye_ray;
			eye_ray.start = world->camera.position;
			eye_ray.direction = ray_direction;

		// 	//! end Junnetwork

			//! mo camera trial
			t_ray	masaru_ray;
			masaru_ray.start = world->camera.position;
			masaru_ray.direction = get_world_ray_direction(masaru_x, masaru_y, world->camera.position, world->camera.orientation, world->screen_witdh, world->camera.field_of_view);
			eye_ray = masaru_ray;
			//

			t_intersect intersection;
			intersection.distance = __DBL_MAX__;
			if (test_all_intersection(world->shapes, &eye_ray, &intersection) == true)
			{
				t_color col;
				col = tcolor_calc_phong(world, &intersection, &eye_ray);
				my_mlx_pixcel_put(image, x, y, tcolor_to_hex(col));
			}
			else
			{
				// my_mlx_pixcel_put(image, x, y, get_hex_color(100, 149, 237));//空色	
				my_mlx_pixcel_put(image, x, y, get_hex_color(100, 149, 237));
			}
		}
	}
}

//! mlx key till here


#include <stdio.h>
int	main(int argc, char **argv)
{
	t_world	world;
	// t_list	*shapes;
	// t_list	*lights;

	// char *input = "123456789.123456789";

	// double ans = ft_atod(input);
	// printf("ans=[%f], pc=[%f]\n", ans, atof(input));
	// return (0);
	//todo parse
	//todo getnextline
	//todo ft_spolit
	//todo validation
	world = tworld_init();
	world.img = timage_init(world.mlx_ptr, world.screen_witdh, world.screen_height);
	world.shapes = ft_lstnew(NULL);
	world.lights = ft_lstnew(NULL);
	parse_main(argv[1], &world);
	get_intersect_with_shape(&world, &world.img);
	mlx_put_image_to_window(world.mlx_ptr, world.win_ptr, world.img.img_ptr, 0, 0);

	//
	mlx_key_hook(world.win_ptr, deal_key, &world);
	mlx_hook(world.win_ptr, 17, 1L << 3, click_close_button, &world);
	//
	mlx_loop(world.mlx_ptr);
	destructor(&world);
	return (EXIT_SUCCESS);
}

// #ifdef LEAK
// #include <stdlib.h>
// __attribute__((destructor))
// void	destructor(void)
// {
// 	int	status;
// 	status = system("leaks -q miniRT");
// }
// #endif
