/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:56:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/11 10:05:09 by mogawa           ###   ########.fr       */
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

#define window_width 512
#define window_height 512

void	sphere(t_world const *world, t_image const *image)
{
	t_vec3			eyePos = vec3_init(0, 0, -5);
	t_vec3			spherePos = vec3_init(0, 0, 5);
	double			sphereR = 1;
	t_vec3			lightPos = vec3_init(-5, 5, -5);
	t_vec3			pw;//スクリーン上の点

	pw.z = 0;
	for (double y = 0; y < window_height; y++)
	{
		// pw.y = -2 * y / (window_height - 1) + 1;
		pw.y = -2 * y / (window_height - 1) + 1;
		for (double x = 0; x < window_width; x++)
		{
			pw.x = 2 * x / (window_width - 1) - 1;
			t_vec3 eyeDir = vec3_subtract(&pw, &eyePos);//視線ベクトル
			eyeDir = vec3_normalize(&eyeDir);//方向ベクトルなので正規化
			t_vec3 tmp = vec3_subtract(&eyePos, &spherePos);
			double a = vec3_lengthSq(&eyeDir);
			double b = 2 * vec3_dot(&tmp, &eyeDir);
			double c = vec3_dot(&tmp, &tmp) - sphereR * sphereR;
			double d = (b * b) - (4 * a * c);
			double t = -1;
			if (d >= 0)
			{
				double t1 = 0;
				double t2 = 0;
				t1 = (-b + sqrt(d)) / (2 * a);
				t2 = (-b - sqrt(d)) / (2 * a);
				if (t1 > 0 && t2 > 0)
					t = double_min(t1, t2);
				else if (t1 > 0 || t2 > 0)
				{
					if (t1 > 0)
						t = t1;
					else
						t = t2;
				}
				dprintf(2, "a:[%f], b:[%f], c:[%f], d:[%f], t:[%f], t1:[%f], t2:[%f]\n", a, b, c, d, t, t1, t2);
			}
			if (t > 0)
			{
				t_vec3 tmp2 = vec3_multiply(&eyeDir, t);
				t_vec3	intPos = vec3_add(&eyePos, &tmp2);
				t_vec3	lightDir = vec3_subtract(&lightPos, &intPos);
				lightDir = vec3_normalize(&lightDir);
				t_vec3	sphereN = vec3_subtract(&intPos, &spherePos);
				sphereN = vec3_normalize(&sphereN);
				//! ambient
				double Ka = 0.01;
				double Ia = 0.1;
				double Ra = Ka * Ia;
				//! diffuse
				double Rd = 0;
				double Kd = 0.69;
				double n_dot_l = vec3_dot(&sphereN, &lightDir);
				Rd = double_clamp(n_dot_l, 0, 1) * Kd;
				//! specular
				double Rs = 0;
				double alpha = 8;
				double Ks = 0.3;
				t_vec3 r = vec3_copy(&sphereN);
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

int	main(void)
{
	t_world	world;
	t_image image;

	//todo parse check
	world = tworld_init(window_width, window_height);
	image = timage_init(world.mlx_ptr, world.screen_witdh, world.screen_height);
	sphere(&world, &image);
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