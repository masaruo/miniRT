/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_intersect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:28:11 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/16 15:37:41 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_intersect.h"
#include <math.h>
#include "math_utils.h"
#include <stdio.h>

static void	_calc_intersection(t_intersect *ans, double t)
{
	// ans->distance = t;
	// ans->position
	return ;
}

//球体との交差判定
static int	_intersect_against_sphere(t_shape const *shape, t_ray const *ray, t_intersect *out_intersect)
{
	t_vec3 const	sphere_to_ray = vec3_subtract(&ray->start, &shape->u_data.sphere.center);
	double const	a = vec3_dot(&ray->direction, &ray->direction);//? 1で決め打ちでもいいか？
	double const	b = 2 * vec3_dot(&sphere_to_ray, &ray->direction);
	double const	c = vec3_dot(&sphere_to_ray, &sphere_to_ray) - shape->u_data.sphere.r * shape->u_data.sphere.r;
	double const	d = (b * b) - (4 * a * c);
	double			t;

	t = -1;//todo make func called get_distance for t
	if (d == 0)
	{
		t = -b / (2 * a);
	}
	else if (d > 0)
	{
		double t1 = (-b + sqrt(d)) / (2 * a);
		double t2 = (-b - sqrt(d)) / (2 * a);
		if (t1 > 0 && t2 > 0)
		{
			t = double_min(t1, t2);
		}
		else if (t1 > 0 || t2 > 0)
		{
			if (t1 > 0)
				t = t1;
			else
				t = t2;
		}
	}
	else
	{
		return (NO_INTERSECTION);
	}
	// 最も近いintersect
	if (out_intersect->distance < t)
	{
		return (HAS_INTERSECTION);
	}
	out_intersect->distance = t;
	t_vec3	tmp = vec3_multiply(&ray->direction, t);
	out_intersect->position = vec3_add(&ray->start, &tmp);
	out_intersect->normal = vec3_subtract(&out_intersect->position, &shape->u_data.sphere.center);
	out_intersect->normal = vec3_normalize(&out_intersect->normal);
	return (HAS_INTERSECTION);
}

//平面との交差判定
static int	_intersect_against_plane(t_shape const *shape, t_ray const *ray, t_intersect *out_intersect)
{
	double	t;
	double	numerator;
	double	denominator;
	t_vec3 const plane_to_camera = vec3_subtract(&ray->start, &shape->u_data.plane.position);

	t = -1;
	numerator = vec3_dot(&plane_to_camera, &shape->u_data.plane.normal) * -1;
	denominator = vec3_dot(&ray->direction, &shape->u_data.plane.normal);
	if (denominator == 0)
		return (NO_INTERSECTION);
	t = numerator / denominator;
	if (t >= 0)
	{
		if (out_intersect->distance < t)
		{
			return (HAS_INTERSECTION);
		}
		out_intersect->distance = t;
		t_vec3 tmp = vec3_multiply(&ray->direction, t);
		out_intersect->position = vec3_add(&ray->start, &tmp);
		out_intersect->normal = shape->u_data.plane.normal;
	}
	else
	{
		return (NO_INTERSECTION);
	}
	return (HAS_INTERSECTION);
}

int	get_intersect(t_shape const *shape, t_ray const *ray, t_intersect *out_intersect)
{
	if (shape->type == e_sphere)
	{
		return (_intersect_against_sphere(shape, ray, out_intersect));
	}
	else if (shape->type == e_plane)
	{
		return (_intersect_against_plane(shape, ray, out_intersect));
	}
	else
	{
		return (NO_INTERSECTION);
	}
}

int	get_nearest_shape(t_scene const *scene, t_ray const *ray, double max_distance, int exit_once_found, t_shape **out_shape, t_intersect *out_intersect)
{
	
}