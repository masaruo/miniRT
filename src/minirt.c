/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/12 12:49:24 by mogawa           ###   ########.fr       */
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

#define window_width 512
#define window_height 512

void	sphere(t_world const *world, t_image const *image)
{
	t_ray			eyePos;
	eyePos.start = vec3_init(0, 0, -5);
	t_shape			sphere2;
	sphere2.type = e_sphere;
	sphere2.u_data.sphere.center = vec3_init(1, 5, 50);
	sphere2.u_data.sphere.r = 1;
	t_light			light;
	light.type = e_point;
	light.vector = vec3_init(0, 50, 0);
	t_vec3			pw;//スクリーン上の点

	pw.z = 0;
	for (double y = 0; y < window_height; y++)
	{
		pw.y = -2 * y / (window_height - 1) + 1;
		for (double x = 0; x < window_width; x++)
		{
			pw.x = 2 * x / (window_width - 1) - 1;
			t_vec3 eyeDir = vec3_subtract(&pw, &eyePos);//視線ベクトル
			eyeDir = vec3_normalize(&eyeDir);//方向ベクトルなので正規化
			eyePos.direction = eyeDir;
			t_intersect isect;

			if (get_intersect(&sphere2, &eyePos, &isect))
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
				int grey = (int)(255 * phong);
				// t_color color = tcolor_init(grey, grey, grey);
				my_mlx_pixcel_put(image, x, y, get_hex_color(grey, grey, grey));
			}
			else
			{
				my_mlx_pixcel_put(image, x, y, get_hex_color(100, 149, 237));
			}
		}
	}
	return ;
}

void	plane(t_world const *world, t_image const *image)
{
	t_ray	camera;
	camera.start = vec3_init(0, 0, -5);
	t_shape	plane;
	plane.type = e_plane;
	plane.u_data.plane.position = vec3_init(0, -1, 0);
	plane.u_data.plane.normal = vec3_init(0, 1, 0);
	t_light	light;
	light.type = e_point;
	light.vector = vec3_init(-5, 5, -5);
	light.brightness = 0.6;
	t_vec3	pw;
	pw.z = 0;
	for (double y = 0; y < window_height; y++)
	{
		pw.y = -2 * y / (window_height - 1) + 1; 
		for (double x = 0; x < window_width; x++)
		{
			pw.x = 2 * x / (window_width - 1) - 1;
			camera.direction = vec3_subtract(&pw, &camera.start);
			camera.direction = vec3_normalize(&camera.direction);
			t_intersect isect;
			if (get_intersect(&plane, &camera, &isect))
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
				int grey = (int)(255 * phong);
				// t_color color = tcolor_init(grey, grey, grey);
				my_mlx_pixcel_put(image, x, y, get_hex_color(grey, grey, grey));
				
			}
			else
				my_mlx_pixcel_put(image, x, y, get_hex_color(255, 255, 255));
		}
	}
	
}

int	main(void)
{
	t_world	world;
	t_image image;

	//todo parse check
	world = tworld_init(window_width, window_height);
	image = timage_init(world.mlx_ptr, world.screen_witdh, world.screen_height);
	// sphere(&world, &image);
	plane(&world, &image);
	mlx_put_image_to_window(world.mlx_ptr, world.win_ptr, image.img_ptr, 0, 0);
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