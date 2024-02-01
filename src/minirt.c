/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/01 16:08:19 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include "t_world.h"
#include "mlx.h"
#include "t_color.h"
#include "math_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "t_ray.h"
#include "t_shape.h"
#include "t_light.h"
#include "t_intersect.h"
#include "libft.h"
#include <limits.h>
#include "phong.h"
#include "t_list.h"
#include "t_matrix.h"
#include "parse.h"

// #define window_width 512
// #define window_height 512

// t_vec3	cameraTransform(t_vec3 *point, t_vec3 *cameraPos, t_vec3 *cameraTarget, t_vec3 *worldUp)
// {
// 	// t_vec3	cameraDirection = vec3_normalized_subtract(cameraTarget, cameraPos);
// 	t_vec3	cameraRight = vec3_cross(worldUp, cameraTarget);
// 	cameraRight = vec3_normalize(&cameraRight);
// 	t_vec3	cameraUp = vec3_cross(cameraTarget, &cameraRight);

// 	t_vec3 pointInCameraCoord;
// 	t_vec3 cameraToPoint = vec3_subtract(point, cameraPos);
// 	pointInCameraCoord.x = vec3_dot(&cameraToPoint, &cameraRight);
// 	pointInCameraCoord.y = vec3_dot(&cameraToPoint, &cameraUp);
// 	pointInCameraCoord.z = vec3_dot(&cameraToPoint, &cameraTarget);
// 	return (pointInCameraCoord);
// }

double	get_x_in_camera(double x_in_loop, double width, double height, double fov)
{
	double const	aspect_ratio = (width / height);
	double const	ndc_x = (x_in_loop + 0.5) / width;//todo define 0.5
	double const	screen_x = (2 * ndc_x) - 1;
	double const	camera_x = screen_x * aspect_ratio;
	double const	fov_adj_camera_x = camera_x * tan(convert_degree_to_radian(fov / 2));

	return (fov_adj_camera_x);
};

double	get_y_in_camera(double y_in_loop, double height, double fov)
{
	double const	ndc_y = (y_in_loop + 0.5) / height;//todo define 0.5
	double const	screen_y = 1 - (2 * ndc_y);
	double const	fov_adj_camera_y = screen_y * tan(convert_degree_to_radian(fov / 2));

	return (fov_adj_camera_y);
}

void	get_intersect_with_shape(t_world const *world, t_image const *image)
{
	double			fov = 60;//!

	t_vec3 pw;
	pw.z = 0;
	// screen_coord.z = -1;
	for (double y = 0; y < world->screen_height; y++)
	{
		pw.y = -2 * y / (world->screen_height - 1) + 1;
		// screen_coord.y = get_y_in_camera(y, window_height, fov);
		for (double x = 0; x < world->screen_witdh; x++)
		{
			pw.x = 2 * x / (world->screen_witdh - 1) - 1;
			// screen_coord.x = get_x_in_camera(x, window_width, window_height, fov);
			// t_vec3	tmp = vec3_init(0, 0, -5);
			// eye_ray = t_ray_create_ray(&tmp, &screen_coord);
			// t_vec3 pwTransformed = cameraTransform(&screen_coord, &cameraPos, &cameraTarget, &worldUp);
			// eye_ray = t_ray_create_ray(&cameraPos, &pwTransformed);
			
			//! junnetwork
			double sw = x - (world->screen_witdh - 1) / 2;
			double sy = (world->screen_height - 1) / 2 - y;
			double d = (world->screen_witdh / 2) / tan(convert_degree_to_radian(fov / 2));

			t_vec3 camera_orientation = vec3_init(0, 0, 1);//! change
			
			t_vec3 d_center = vec3_multiply(&camera_orientation, d);
			t_vec3 x_basis;
			x_basis.x = d_center.z / sqrt(pow(d_center.z, 2) + pow(d_center.x, 2));
			x_basis.y = 0;
			x_basis.z = -d_center.x / sqrt(pow(d_center.z, 2) + pow(d_center.x, 2));
			t_vec3 y_basis;
			t_vec3 tmp = vec3_multiply(&d_center, -1);
			y_basis = vec3_cross(&x_basis, &tmp);
			y_basis = vec3_normalize(&y_basis);

			t_vec3 xx = vec3_multiply(&x_basis, sw);
			t_vec3 yy = vec3_multiply(&y_basis, sy);

			t_vec3 ray_direction;
			ray_direction = vec3_add(&xx, &yy);
			ray_direction = vec3_add(&d_center, &ray_direction);
			ray_direction = vec3_normalize(&ray_direction);

			t_ray	eye_ray;
			eye_ray.start = vec3_init(0, 0, -20);//!
			eye_ray.direction = ray_direction;
			//! end Junnetwork

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
				my_mlx_pixcel_put(image, x, y, get_hex_color(0, 0, 0));
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_world	world;
	t_list	*shapes;
	t_list	*lights;

	//todo parse
	//todo getnextline
	//todo ft_spolit
	//todo validation
	world = tworld_init();
	world.img = timage_init(world.mlx_ptr, world.screen_witdh, world.screen_height);
	world.shapes = ft_lstnew(NULL);
	world.lights = ft_lstnew(NULL);
	parse_controller(argv[1], &world);
	get_intersect_with_shape(&world, &world.img);
	mlx_put_image_to_window(world.mlx_ptr, world.win_ptr, world.img.img_ptr, 0, 0);
	mlx_loop(world.mlx_ptr);
	return (EXIT_SUCCESS);
}

#ifdef LEAK
#include <stdlib.h>
__attribute__((destructor))
void	destructor(void)
{
	int	status;
	status = system("leaks -q miniRT");
}
#endif