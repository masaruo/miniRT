/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:37:29 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 15:20:03 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_sphere.h"
#include <math.h>
#include "math_utils.h"

// ２関数tの解を、判別式を用いて計算
static	double	calculate_t_distance(double d, double b, double a)
{
	double			t_distance;
	double			t_plus;
	double			t_minus;

	t_distance = -1;
	if (a == 0)
		return (t_distance);
	if (d >= 0)
	{
		t_plus = (-b + sqrt(d)) / (2 * a);
		t_minus = (-b - sqrt(d)) / (2 * a);
		if (t_plus > 0 && t_minus > 0)
		{
			t_distance = d_min(t_plus, t_minus);
		}
		else if (t_plus > 0 || t_minus > 0)
		{
			if (t_plus > 0)
				t_distance = t_plus;
			else
				t_distance = t_minus;
		}
	}
	return (t_distance);
}

// ２次関数a b cから判定式dを計算。aは正規化されたRayの方向ベクトルなので常に１。
static	double	cal_sphere_distance(t_sphere const *sphere, t_ray const *ray)
{
	t_vec3 const	sphere_to_ray = vec3_subtract(ray->start, sphere->center);
	double const	a = vec3_square(ray->direction);
	double const	b = 2 * vec3_dot(sphere_to_ray, ray->direction);
	double const	c = vec3_square(sphere_to_ray) - pow(sphere->r, 2);
	double const	d = (b * b) - (4 * a * c);

	return (calculate_t_distance(d, b, a));
}

int	get_distance_to_sphere(\
		t_sphere const *sphere, \
		t_ray const *ray, \
		t_intersect *out_intersect)
{
	double const	distance = cal_sphere_distance(sphere, ray);

	if (distance < 0)
	{
		return (NO_INTERSECTION);
	}
	out_intersect->distance = distance;
	out_intersect->position = t_ray_get_point(ray, distance);
	out_intersect->normal = \
		vec3_normalized_subtract(out_intersect->position, sphere->center);
	out_intersect->color = sphere->color;
	return (HAS_INTERSECTION);
}
