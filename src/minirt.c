/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/22 16:11:05 by mogawa           ###   ########.fr       */
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

#define window_width 512
#define window_height 512

void	get_intersect_with_shape(t_world const *world, t_image const *image)
{
	t_ray			eyePos;
	t_vec3			pw;//スクリーン上の点
	t_shape			nearest_shape;

	pw.z = 0;
	for (double y = 0; y < window_height; y++)
	{
		pw.y = -2 * y / (window_height - 1) + 1;
		for (double x = 0; x < window_width; x++)
		{
			pw.x = 2 * x / (window_width - 1) - 1;
			t_vec3	tmp = vec3_init(0, 0, -5);
			eyePos = t_ray_create_ray(&tmp, &pw);

			t_intersect isect;
			isect.distance = __DBL_MAX__;
			
			// crnt = world->shapes->next;
			// t_shape	*nearest_shape;
			// while (crnt)
			// {
				// t_shape	*shape;
				// shape = crnt->content;
				// int res;
				// t_intersect	crnt_intersect;
				// res = test_intersection(shape, &eyePos, &crnt_intersect);
				// if (res == HAS_INTERSECTION)
				// {
				// 	if (crnt_intersect.distance < isect.distance)
				// 	{
				// 		isect = crnt_intersect;
				// 		nearest_shape = shape;
				// 	}
				// }
				// crnt = crnt->next;
			// }
			// if (isect.distance < __DBL_MAX__)
			if (test_all_intersection(world->shapes, &eyePos, &isect, &nearest_shape) == true)
			{
				t_color col;
				col = tcolor_calc_phong(&nearest_shape, world->lights, &isect, &eyePos);
				my_mlx_pixcel_put(image, x, y, tcolor_to_hex(col));
			}
			else
			{
				my_mlx_pixcel_put(image, x, y, get_hex_color(100, 149, 237));//空色	
			}
		}
	}
}

t_list	*ADHOC_create_shape_list(void)//todo delete
{
	t_list	*shapes;

	shapes = ft_calloc(1, sizeof(t_list *));
	t_shape			*sphere1;
	sphere1 = ft_calloc(1, sizeof(t_shape));
	sphere1->type = sphere_type;
	sphere1->u_data.sphere.center = vec3_init(3, 0, 25);
	sphere1->u_data.sphere.r = 1;
	sphere1->material.color = tcolor_convert_rgbcolor(255, 0, 0);
	sphere1->material.ambient = tcolor_set(0.01, 0.01, 0.01);
	sphere1->material.diffuse = tcolor_set(0.69, 0, 0);
	sphere1->material.specular = tcolor_set(0.30, 0.30, 0.30);
	sphere1->material.shininess = 8;

	t_shape			*sphere2;
	sphere2 = ft_calloc(1, sizeof(t_shape));
	sphere2->type = sphere_type;
	sphere2->u_data.sphere.center = vec3_init(2, 0, 20);
	sphere2->u_data.sphere.r = 1;
	sphere2->material.color = tcolor_convert_rgbcolor(255, 0, 0);
	sphere2->material.ambient = tcolor_set(0.01, 0.01, 0.01);
	sphere2->material.diffuse = tcolor_set(0.00, 0.69, 0.00);
	sphere2->material.specular = tcolor_set(0.30, 0.30, 0.30);
	sphere2->material.shininess = 8;

	t_shape			*sphere3;
	sphere3 = ft_calloc(1, sizeof(t_shape));
	sphere3->type = sphere_type;
	sphere3->u_data.sphere.center = vec3_init(1, 0, 15);
	sphere3->u_data.sphere.r = 1;
	sphere3->material.color = tcolor_convert_rgbcolor(255, 0, 0);
	sphere3->material.ambient = tcolor_set(0.01, 0.01, 0.01);
	sphere3->material.diffuse = tcolor_set(0.00, 0.00, 0.69);
	sphere3->material.specular = tcolor_set(0.30, 0.30, 0.30);
	sphere3->material.shininess = 8;

	t_shape			*sphere4;
	sphere4 = ft_calloc(1, sizeof(t_shape));
	sphere4->type = sphere_type;
	sphere4->u_data.sphere.center = vec3_init(0, 0, 10);
	sphere4->u_data.sphere.r = 1;
	sphere4->material.color = tcolor_convert_rgbcolor(255, 0, 0);
	sphere4->material.ambient = tcolor_set(0.01, 0.01, 0.01);
	sphere4->material.diffuse = tcolor_set(0.00, 0.69, 0.69);
	sphere4->material.specular = tcolor_set(0.30, 0.30, 0.30);
	sphere4->material.shininess = 8;
	
	t_shape			*sphere5;
	sphere5 = ft_calloc(1, sizeof(t_shape));
	sphere5->type = sphere_type;
	sphere5->u_data.sphere.center = vec3_init(-1, 0, 5);
	sphere5->u_data.sphere.r = 1;
	sphere5->material.color = tcolor_convert_rgbcolor(255, 0, 0);
	sphere5->material.ambient = tcolor_set(0.01, 0.01, 0.01);
	sphere5->material.diffuse = tcolor_set(0.69, 0.00, 0.69);
	sphere5->material.specular = tcolor_set(0.30, 0.30, 0.30);
	sphere5->material.shininess = 8;
	
	t_shape	*plane;
	plane = ft_calloc(1, sizeof(t_shape));
	plane->type = plane_type;
	plane->u_data.plane.position = vec3_init(0, -1, 0);
	plane->u_data.plane.normal = vec3_init(0, 1, 0);
	plane->material.color = tcolor_convert_rgbcolor(255, 0, 0);
	plane->material.ambient = tcolor_set(0.01, 0.01, 0.01);
	plane->material.diffuse = tcolor_set(0.69, 0.69, 0.69);
	plane->material.specular = tcolor_set(0.30, 0.30, 0.30);
	plane->material.shininess = 8;

	shapes = ft_lstnew(NULL);
	ft_lstadd_back(&shapes, ft_lstnew(sphere1));
	ft_lstadd_back(&shapes, ft_lstnew(sphere2));
	ft_lstadd_back(&shapes, ft_lstnew(sphere3));
	ft_lstadd_back(&shapes, ft_lstnew(sphere4));
	ft_lstadd_back(&shapes, ft_lstnew(sphere5));
	ft_lstadd_back(&shapes, ft_lstnew(plane));
	return (shapes);
}
t_list	*ADHOC_create_lights_list(void)
{
	t_list	*lights;

	lights = ft_calloc(1, sizeof(t_list *));
	t_light	*light1;
	light1 = ft_calloc(1, sizeof(t_light));
	light1->type = e_directional;
	light1->vector = vec3_init(-5, 5, -5);
	light1->brightness = tcolor_set(0.5, 0.5, 0.5);
	//todo color light1->color = 

	t_light	*light2;
	light2 = ft_calloc(1, sizeof(t_light));
	light2->type = e_directional;
	light2->vector = vec3_init(5, 0, -5);
	light2->brightness = tcolor_set(0.5, 0.5, 0.5);

	t_light	*light3;
	light3 = ft_calloc(1, sizeof(t_light));
	light3->type = e_directional;
	light3->vector = vec3_init(5, 20, -5);
	light3->brightness = tcolor_set(0.5, 0.5, 0.5);

	lights = ft_lstnew(NULL);
	ft_lstadd_back(&lights, ft_lstnew(light1));
	ft_lstadd_back(&lights, ft_lstnew(light2));
	ft_lstadd_back(&lights, ft_lstnew(light3));
	return (lights);
}

int	main(void)
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
	shapes = ADHOC_create_shape_list();//todo refactor
	// print_tshape(shapes);
	lights = ADHOC_create_lights_list();//todo refactor
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