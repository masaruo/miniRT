/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/01 13:36:18 by mogawa           ###   ########.fr       */
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

#define window_width 512
#define window_height 512

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
	for (double y = 0; y < window_height; y++)
	{
		pw.y = -2 * y / (window_height - 1) + 1;
		// screen_coord.y = get_y_in_camera(y, window_height, fov);
		for (double x = 0; x < window_width; x++)
		{
			pw.x = 2 * x / (window_width - 1) - 1;
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
				col = tcolor_calc_phong(world->lights, &intersection, &eye_ray, world->shapes);
				my_mlx_pixcel_put(image, x, y, tcolor_to_hex(col));
			}
			else
			{
				my_mlx_pixcel_put(image, x, y, get_hex_color(100, 149, 237));//空色	
			}
		}
	}
}

// t_list	*ADHOC_create_shape_list(void)//todo delete
// {
// 	t_list	*shapes;

// 	shapes = ft_calloc(1, sizeof(t_list *));
// 	t_shape			*sphere1;
// 	sphere1 = ft_calloc(1, sizeof(t_shape));
// 	sphere1->type = sphere_type;
// 	sphere1->u_data.sphere.center = vec3_init(3, 0, 25);
// 	sphere1->u_data.sphere.r = 1;
// 	sphere1->material.color = tcolor_convert_rgbcolor(255, 0, 0);
// 	sphere1->material.ambient = tcolor_set(0.01, 0.01, 0.01);
// 	sphere1->material.diffuse = tcolor_set(0.69, 0, 0);
// 	sphere1->material.specular = tcolor_set(0.30, 0.30, 0.30);
// 	sphere1->material.shininess = 8;

// 	t_shape			*sphere2;
// 	sphere2 = ft_calloc(1, sizeof(t_shape));
// 	sphere2->type = sphere_type;
// 	sphere2->u_data.sphere.center = vec3_init(2, 0, 20);
// 	sphere2->u_data.sphere.r = 1;
// 	sphere2->material.color = tcolor_convert_rgbcolor(255, 0, 0);
// 	sphere2->material.ambient = tcolor_set(0.01, 0.01, 0.01);
// 	sphere2->material.diffuse = tcolor_set(0.00, 0.69, 0.00);
// 	sphere2->material.specular = tcolor_set(0.30, 0.30, 0.30);
// 	sphere2->material.shininess = 8;

// 	t_shape			*sphere3;
// 	sphere3 = ft_calloc(1, sizeof(t_shape));
// 	sphere3->type = sphere_type;
// 	sphere3->u_data.sphere.center = vec3_init(1, 0, 15);
// 	sphere3->u_data.sphere.r = 1;
// 	sphere3->material.color = tcolor_convert_rgbcolor(255, 0, 0);
// 	sphere3->material.ambient = tcolor_set(0.01, 0.01, 0.01);
// 	sphere3->material.diffuse = tcolor_set(0.00, 0.00, 0.69);
// 	sphere3->material.specular = tcolor_set(0.30, 0.30, 0.30);
// 	sphere3->material.shininess = 8;

// 	t_shape			*sphere4;
// 	sphere4 = ft_calloc(1, sizeof(t_shape));
// 	sphere4->type = sphere_type;
// 	sphere4->u_data.sphere.center = vec3_init(0, 0, 10);
// 	sphere4->u_data.sphere.r = 1;
// 	sphere4->material.color = tcolor_convert_rgbcolor(255, 0, 0);
// 	sphere4->material.ambient = tcolor_set(0.01, 0.01, 0.01);
// 	sphere4->material.diffuse = tcolor_set(0.00, 0.69, 0.69);
// 	sphere4->material.specular = tcolor_set(0.30, 0.30, 0.30);
// 	sphere4->material.shininess = 8;
	
// 	t_shape			*sphere5;
// 	sphere5 = ft_calloc(1, sizeof(t_shape));
// 	sphere5->type = sphere_type;
// 	sphere5->u_data.sphere.center = vec3_init(3, 3, -3);
// 	sphere5->u_data.sphere.r = 2;
// 	sphere5->material.color = tcolor_convert_rgbcolor(0, 176, 176);
// 	sphere5->material.ambient = tcolor_set(0.01, 0.01, 0.01);
// 	sphere5->material.diffuse = tcolor_set(0.69, 0.00, 0.69);
// 	sphere5->material.specular = tcolor_set(0.30, 0.30, 0.30);
// 	sphere5->material.shininess = 8;
	
// 	t_shape	*plane;
// 	plane = ft_calloc(1, sizeof(t_shape));
// 	plane->type = plane_type;
// 	plane->u_data.plane.position = vec3_init(0, -1, 0);
// 	plane->u_data.plane.normal = vec3_init(0, 1, 0);
// 	plane->material.color = tcolor_convert_rgbcolor(255, 0, 0);
// 	plane->material.ambient = tcolor_set(0.01, 0.01, 0.01);
// 	plane->material.diffuse = tcolor_set(0.69, 0.69, 0.69);
// 	plane->material.specular = tcolor_set(0.30, 0.30, 0.30);
// 	plane->material.shininess = 8;

// 	shapes = ft_lstnew(NULL);
// 	ft_lstadd_back(&shapes, ft_lstnew(sphere1));
// 	ft_lstadd_back(&shapes, ft_lstnew(sphere2));
// 	ft_lstadd_back(&shapes, ft_lstnew(sphere3));
// 	ft_lstadd_back(&shapes, ft_lstnew(sphere4));
// 	// ft_lstadd_back(&shapes, ft_lstnew(sphere5));
// 	ft_lstadd_back(&shapes, ft_lstnew(plane));
// 	return (shapes);
// }
// t_list	*ADHOC_create_lights_list(void)
// {
// 	t_list	*lights;

// 	lights = ft_calloc(1, sizeof(t_list *));
// 	t_light	*light1;
// 	light1 = ft_calloc(1, sizeof(t_light));
// 	light1->type = e_directional;
// 	light1->vector = vec3_init(-5, 5, -5);
// 	light1->brightness = tcolor_set(0.5, 0.5, 0.5);
// 	//todo color light1->color = 

// 	t_light	*light2;
// 	light2 = ft_calloc(1, sizeof(t_light));
// 	light2->type = e_directional;
// 	light2->vector = vec3_init(5, 0, -5);
// 	light2->brightness = tcolor_set(0.5, 0.5, 0.5);

// 	t_light	*light3;
// 	light3 = ft_calloc(1, sizeof(t_light));
// 	light3->type = e_directional;
// 	light3->vector = vec3_init(5, 20, -5);
// 	light3->brightness = tcolor_set(0.5, 0.5, 0.5);

// 	lights = ft_lstnew(NULL);
// 	ft_lstadd_back(&lights, ft_lstnew(light1));
// 	ft_lstadd_back(&lights, ft_lstnew(light2));
// 	ft_lstadd_back(&lights, ft_lstnew(light3));
// 	return (lights);
// }

int	main(int argc, char **argv)
{
	t_world	world;
	t_list	*shapes;
	t_list	*lights;
	// t_image image;

	//todo parse
	//todo getnextline
	//todo ft_spolit
	//todo validation
	world = tworld_init(window_width, window_height);
	world.img = timage_init(world.mlx_ptr, world.screen_witdh, world.screen_height);
	// shapes = ADHOC_create_shape_list();//todo refactor
	shapes = ft_lstnew(NULL);
	lights = ft_lstnew(NULL);
	parse_controller(argv[1], shapes, lights);
	// print_tshape(shapes);
	// lights = ADHOC_create_lights_list();//todo refactor
	world.shapes = shapes;
	world.lights = lights;
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