/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:31:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/23 11:31:51 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shape.h"
#include "math.h"
#include "math_utils.h"
#include "shadow.h"

// ２関数tの解を、判別式を用いて計算
static	double	calculate_t_distance(double d, double b, double a)
{
	double			t_distance;
	double			t_plus;
	double			t_minus;

	t_distance = -1;
	if (d >= 0)
	{
		t_plus = (-b + sqrt(d)) / (2 * a);
		t_minus = (-b - sqrt(d)) / (2 * a);
		if (t_plus > 0 && t_minus > 0)
		{
			t_distance = double_min(t_plus, t_minus);
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
static	double	calculate_sphere_distance(t_sphere const *sphere, t_ray const *ray)
{
	t_vec3 const	sphere_to_ray = vec3_subtract(&ray->start, &sphere->center);
	double const	a = vec3_square(&ray->direction);
	double const	b = 2 * vec3_dot(&sphere_to_ray, &ray->direction);
	double const	c = vec3_square(&sphere_to_ray) -  pow(sphere->r, 2);
	double const	d = (b * b) - (4 * a * c);

	return (calculate_t_distance(d, b, a));
}

static int	get_distance_to_sphere(t_sphere const *sphere, t_ray const *ray, t_intersect *out_intersect)
{
	double const	distance = calculate_sphere_distance(sphere, ray);
	t_vec3			center_to_intersect;

	if (distance < 0)
	{
		return (NO_INTERSECTION);
	}
	out_intersect->distance = distance;
	out_intersect->position = t_ray_get_point(ray, distance);
	center_to_intersect = vec3_subtract(&out_intersect->position, &sphere->center);
	out_intersect->normal = vec3_normalize(&center_to_intersect);
	return (HAS_INTERSECTION);
}

static int	get_distance_to_plane(t_plane const *plane, t_ray const *ray, t_intersect *out_intersect)
{
	t_vec3 const	plane_to_camera = vec3_subtract(&ray->start, &plane->position);
	double const	numerator = vec3_dot(&plane_to_camera, &plane->normal) * -1;
	double const	denominator = vec3_dot(&ray->direction, &plane->normal);
	double			distance;

	if (denominator == 0)
		return (NO_INTERSECTION);
	distance = numerator / denominator;
	if (distance < 0)
		return (NO_INTERSECTION);
	out_intersect->distance = distance;
	out_intersect->position = t_ray_get_point(ray, distance);
	out_intersect->normal = plane->normal;
	return (HAS_INTERSECTION);
}

int	test_intersection(t_shape const *shape, t_ray const *ray, t_intersect *out_intersect)
{
	if (shape->type == sphere_type)
	{
		return (get_distance_to_sphere(&shape->u_data.sphere, ray, out_intersect));
	}
	else if (shape->type == plane_type)
	{
		return (get_distance_to_plane(&shape->u_data.plane, ray, out_intersect));
	}
	else
	{
		return (NO_INTERSECTION);
	}
}

int	test_all_intersection(t_list const * const shapes, t_ray const *ray, t_intersect *out_intersect)
{
	t_list		*crnt;
	t_shape		*shape;
	t_intersect	crnt_intersect;
	bool		has_intersection;

	has_intersection = false;
	crnt = shapes->next;
	while (crnt)
	{
		shape = crnt->content;
		if(test_intersection(shape, ray, &crnt_intersect))
		{
			if (crnt_intersect.distance < out_intersect->distance)
			{
				out_intersect->distance = crnt_intersect.distance;
				out_intersect->normal = crnt_intersect.normal;
				out_intersect->position = crnt_intersect.position;
				out_intersect->has_intersection = true;
				out_intersect->material = shape->material;
				has_intersection = true;
			}
		}
		crnt = crnt->next;
	}
	return (has_intersection);
}

int	test_shadow_intersection(t_list const * const shapes, t_light const *light, t_intersect const *intersect)
{
	t_vec3	vector_light;
	t_ray	shadow_ray;
	t_list	*crnt;
	t_shape	*shape;
	t_intersect shadow_intersect;

	vector_light = vec3_subtract(&light->vector, &intersect->position);
	double	light_distance = vec3_length(&vector_light);
	double	light_distance_minus_epsilon = light_distance - EPSILON;

	shadow_ray.direction = vec3_normalize(&vector_light);
	t_vec3	tmp;
	tmp = vec3_multiply(&shadow_ray.direction, EPSILON);
	shadow_ray.start = vec3_add(&intersect->position, &tmp);

	crnt = shapes->next;
	while (crnt)
	{
		shape = crnt->content;
		if (test_intersection(shape, &shadow_ray, &shadow_intersect) == HAS_INTERSECTION)
		{
			if (shadow_intersect.distance < light_distance_minus_epsilon)
				return (HAS_INTERSECTION);
		}
		crnt = crnt->next;
	}
	return (NO_INTERSECTION);
}
