/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/17 13:18:09 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "t_vec3.h"
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

#define window_width 512
#define window_height 512

void	get_intersect_with_shape(t_world const *world, t_image const *image)
{
	t_ray			eyePos;
	t_light			light;
	light.type = e_point;
	light.vector = vec3_init(-5, 5, -5);
	t_vec3			pw;//スクリーン上の点

	pw.z = 0;
	for (double y = 0; y < window_height; y++)
	{
		pw.y = -2 * y / (window_height - 1) + 1;
		for (double x = 0; x < window_width; x++)
		{
			pw.x = 2 * x / (window_width - 1) - 1;
			t_vec3	tmp = vec3_init(0, 0, -5);
			eyePos = t_ray_init(&tmp, &pw);

			t_intersect isect;
			isect.distance = __DBL_MAX__;
			isect.nearest_shape = NULL;
			t_list *crnt;
			crnt = world->shapes->next;
			while (crnt)
			{
				t_shape	*shape;
				shape = crnt->content;
				get_intersect(shape, &eyePos, &isect);
				crnt = crnt->next;
			}
			if (isect.distance < __DBL_MAX__)
			{
				t_vec3	lightDir = vec3_subtract(&light.vector, &isect.position);
				lightDir = vec3_normalize(&lightDir);
				//! ambient
				double Ka = 0.01;
				double Ia = 0.1;
				double Ra = Ka * Ia;
				//! diffuse
				double Rd = 0;
				double Kd = 0.69;
				double n_dot_l = vec3_dot(&isect.normal, &lightDir);
				Rd = double_clamp(n_dot_l, 0, 1) * Kd;
				//! specular
				double Rs = 0;
				double alpha = 8;
				double Ks = 0.3;
				t_vec3 r = vec3_copy(&isect.normal);
				r = vec3_multiply(&r, 2 * n_dot_l);
				r = vec3_subtract(&r, &lightDir);
				double v_dot_r = vec3_dot(&lightDir, &r);
				Rs = Ks * pow(v_dot_r, alpha);
				//! combine
				if (n_dot_l < 0)
				{
					Rd = 0;
				}
				if (v_dot_r < 0)
				{
					Rs = 0;
				}
				double phong = Ra + Rd + Rs;
				my_mlx_pixcel_put(image, x, y, tcolor_to_hex(tcolor_scalar_multiply(isect.nearest_shape->color, phong)));
			}
			else
			{
				my_mlx_pixcel_put(image, x, y, get_hex_color(100, 149, 237));//空色	
			}
		}
	}
}

t_list	*ADHOC_create_shape_list(t_list *shapes)//todo delete
{
	t_shape			*sphere1;
	sphere1 = ft_calloc(1, sizeof(t_shape));
	sphere1->type = e_sphere;
	sphere1->u_data.sphere.center = vec3_init(1, 10, 50);
	sphere1->u_data.sphere.r = 1;
	sphere1->color = tcolor_init(0, 0, 255);//blue
	t_shape			*sphere2;
	sphere2 = ft_calloc(1, sizeof(t_shape));
	sphere2->type = e_sphere;
	sphere2->u_data.sphere.center = vec3_init(0, 0, 5);
	sphere2->u_data.sphere.r = 1;
	sphere2->color = tcolor_init(255, 0, 0);//red
	t_shape	*plane;
	plane = ft_calloc(1, sizeof(t_shape));
	plane->type = e_plane;
	plane->u_data.plane.position = vec3_init(0, -1, 0);
	plane->u_data.plane.normal = vec3_init(0, 1, 0);
	plane->color = tcolor_init(128, 128, 128);//grey

	ft_lstadd_back(&shapes, ft_lstnew(NULL));
	ft_lstadd_back(&shapes, ft_lstnew(sphere1));
	ft_lstadd_back(&shapes, ft_lstnew(sphere2));
	ft_lstadd_back(&shapes, ft_lstnew(plane));
	return (shapes);
}

int	main(void)
{
	t_world	world;
	// t_image image;

	//todo parse
	//todo getnextline
	//todo ft_spolit
	//todo validation
	world = tworld_init(window_width, window_height);
	world.img = timage_init(world.mlx_ptr, world.screen_witdh, world.screen_height);
	world.shapes = NULL;//todo refactor
	world.shapes = ADHOC_create_shape_list(world.shapes);//todo refactor
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