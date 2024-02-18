/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:31:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 08:46:02 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shape.h"
#include <math.h>
#include "math_utils.h"
#include "shadow.h"

// //!シリンダー

// static double	_cylinder_get_a(t_normalized_vec3 d, t_normalized_vec3 v)
// {
// 	double const	dv = vec3_dotx(d, v);
// 	double const	dv_pow2 = dv * dv;
// 	double const	a = vec3_dotx(d, d) - dv_pow2;

// 	return (a);
// }

// static double	_cylinder_get_b(t_normalized_vec3 d, t_normalized_vec3 v, t_position_vec3 c)
// {
// 	double dv = vec3_dotx(d, v);
// 	double vv = vec3_dotx(v, v);
// 	double dc = vec3_dotx(d, c);
// 	double cv = vec3_dotx(c, v);

// 	double b = 2 * (cv * dv - dc);
// 	// double b = -2 * (dc - (cv * dv));
// 	return (b);
// }

// static double	_cylinder_get_c(t_normalized_vec3 v, t_position_vec3 c, double r)
// {
// 	double	c_quadratic;

// 	double cc = vec3_dotx(c, c);
// 	double cv = vec3_dotx(c, v);
// 	double cv_pow2 = cv * cv;
// 	double vv = vec3_dotx(v, v);

// 	c_quadratic = cc - cv_pow2 - r * r;
// 	return (c_quadratic);
// }

// double	get_length_of_projection(t_ray *ray, t_cylinder *cylinder, t_vec3 point)
// {
// 	t_vec3	cylinder_center_to_point = vec3_subtractx(point, cylinder->position);
// 	double	len_projection = vec3_dotx(cylinder_center_to_point, cylinder->normal);
// 	return (len_projection);
// }

// t_vec3	get_normal(double t, t_ray *ray, t_cylinder *cylinder, t_vec3 point, bool is_inside)
// {
// 	t_vec3	normal;
// 	t_vec3	cylinder_center_to_point = vec3_subtractx(point, cylinder->position);
// 	double	len_projection = vec3_dotx(cylinder_center_to_point, cylinder->normal);
// 	t_vec3	projection = vec3_addx(cylinder->position, vec3_multiplyx(cylinder->normal, len_projection));

// 	if (is_inside)
// 	{
// 		normal = vec3_normalized_subtractx(projection, point);
// 		// normal = vec3_normalized_subtractx(point, projection);
// 	}
// 	else
// 	{
// 		normal = vec3_normalized_subtractx(point, projection);
// 		// normal = vec3_normalized_subtractx(projection, point);
// 	}
// 	normal = vec3_normalized_subtractx(point, projection);
// 	return (normal);
// }

// double	calculate_cylinder_distance(double A, double B, double C, t_vec3 *point, t_vec3 *normal, t_ray *ray, t_cylinder *cylinder)
// {
// 	double	t;
// 	double	d = B * B - 4 * A * C;
// 	double	t_plus;
// 	double	t_minus;
// 	t_vec3	cylinder_to_point;

// 	t = -1;
// 	if (d < 0)
// 		return (t);
// 	t_plus = (-B + sqrt(d)) / (2 * A);
// 	t_minus = (-B - sqrt(d)) / (2 * A);
// 	if (t_plus > 0 && t_minus > 0)
// 	{
// 		if (t_plus < t_minus)
// 		{
// 			t = t_plus;
// 		}
// 		else
// 		{
// 			t = t_minus;
// 		}
// 		*point = vec3_addx(ray->start, vec3_multiplyx(ray->direction, t));
// 		*normal = get_normal(t, ray, cylinder, *point, false);
// 		return (t);
// 	}
// 	else if (t_plus > 0 || t_minus > 0)
// 	{
// 		if (t_plus > 0)
// 		{
// 			t = t_plus;
// 		}
// 		else
// 		{
// 			t = t_minus;
// 		}
// 		*point = vec3_addx(ray->start, vec3_multiplyx(ray->direction, t));
// 		*normal = get_normal(t, ray, cylinder, *point, true);
// 	}
// 	return (t);
// }

// double	_cylinder_get_params(double A, double B, double D, double *m, t_vec3 *normal, t_vec3 s, t_vec3 v, t_vec3 c, t_vec3 d, double height)
// {
// 	double	t_distance;
// 	double	t_plus;
// 	double	t_minus;
// 	t_vec3	P;

// 	t_distance = -1;
// 	t_plus = -B + sqrt(D) / 2 * A;
// 	t_minus = -B - sqrt(D) / 2 * A;
// 	if (t_plus > 0 && t_minus > 0)
// 	{
// 		if (t_plus < t_minus)
// 		{
// 			t_distance = t_plus;
// 		}
// 		else
// 		{
// 			t_distance = t_minus;
// 		}
// 		// *m = t_distance * vec3_dotx(d, v) + 2 * vec3_dotx(s, v) - vec3_dotx(c, c);
// 		P = vec3_addx(s, vec3_multiplyx(d, t_distance));
// 		t_vec3	p_to_c = vec3_subtractx(c, P);
// 		double _m = vec3_dotx(p_to_c, v);
// 		*m = _m;
// 		t_vec3	projection = vec3_multiplyx(v, _m);
// 		t_vec3	N = vec3_normalized_subtractx(P, projection);
// 		*normal = N;
// 	}
// 	else if (t_plus > 0 || t_plus > 0)
// 	{
// 		if (t_plus > 0)
// 		{
// 			t_distance = t_plus;
// 		}
// 		else
// 		{
// 			t_distance = t_minus;
// 		}
// 		// *m = t_distance * vec3_dotx(d, v) + 2 * vec3_dotx(s, v) - vec3_dotx(c, c);
// 		P = vec3_addx(s, vec3_multiplyx(d, t_distance));
// 		t_vec3	p_to_c = vec3_subtractx(c, P);
// 		double _m = vec3_dotx(p_to_c, v);
// 		*m = _m;
// 		t_vec3	projection = vec3_multiplyx(v, _m);
// 		t_vec3	N = vec3_normalized_subtractx(P, projection);
// 		N = vec3_multiplyx(N, -1);
// 		*normal = N;
// 	}
// 	return (t_distance);
// }

// int	get_distance_to_cylinder(t_cylinder const *cylinder, t_ray const *ray, t_intersect *out_intersect)
// {
// 	double	t1, t2;
// 	double	r = cylinder->r;
// 	t_vec3	s = ray->start;
// 	t_vec3	d = ray->direction;
// 	t_vec3	cylinder_to_ray;
// 	// t_vec3	cylinder_to_ray = vec3_subtractx(ray->start, cylinder->position);
// 	cylinder_to_ray = vec3_subtractx(cylinder->position, ray->start);
// 	// cylinder_to_ray= cylinder->position;
// 	t_vec3	c = cylinder->position;
// 	t_vec3	v = cylinder->normal;
// 	t_normalized_vec3	intersect_normal1;

// 	double	A = _cylinder_get_a(d, v);
// 	double	B = _cylinder_get_b(d, v, cylinder_to_ray);
// 	double	C = _cylinder_get_c(v, cylinder_to_ray, r);
// 	double	D = B * B - 4 * A * C;
	
// 	if (A == 0 || D < 0)
// 	{
// 		return (NO_INTERSECTION);
// 	}
// 	// double	m = -1;
// 	t_vec3	point;
// 	t_vec3	normal;
// 	double t = calculate_cylinder_distance(A, B, C, &point, &normal, ray, cylinder);
// 	if (t < 0)
// 	{
// 		return (NO_INTERSECTION);
// 	}
// 	double	m = get_length_of_projection(ray, cylinder, point);
// 	if (m > cylinder->height || m < 0)
// 	{
// 		return (NO_INTERSECTION);
// 	}

// 	out_intersect->distance = t;
// 	out_intersect->position = t_ray_get_point(ray, t);
// 	out_intersect->normal = normal;
// 	out_intersect->color = cylinder->color;
// 	return (HAS_INTERSECTION);
// }
// //!シリンダーここまで

// // ２関数tの解を、判別式を用いて計算
// static	double	calculate_t_distance(double d, double b, double a)
// {
// 	double			t_distance;
// 	double			t_plus;
// 	double			t_minus;

// 	t_distance = -1;
// 	if (d >= 0)
// 	{
// 		t_plus = (-b + sqrt(d)) / (2 * a);
// 		t_minus = (-b - sqrt(d)) / (2 * a);
// 		if (t_plus > 0 && t_minus > 0)
// 		{
// 			t_distance = double_min(t_plus, t_minus);
// 		}
// 		else if (t_plus > 0 || t_minus > 0)
// 		{
// 			if (t_plus > 0)
// 				t_distance = t_plus;
// 			else
// 				t_distance = t_minus;
// 		}
// 	}
// 	return (t_distance);
// }

// // ２次関数a b cから判定式dを計算。aは正規化されたRayの方向ベクトルなので常に１。
// static	double	calculate_sphere_distance(t_sphere const *sphere, t_ray const *ray)
// {
// 	t_vec3 const	sphere_to_ray = vec3_subtract(&ray->start, &sphere->center);
// 	double const	a = vec3_square(&ray->direction);
// 	double const	b = 2 * vec3_dot(&sphere_to_ray, &ray->direction);
// 	double const	c = vec3_square(&sphere_to_ray) -  pow(sphere->r, 2);
// 	double const	d = (b * b) - (4 * a * c);

// 	return (calculate_t_distance(d, b, a));
// }

// static int	get_distance_to_sphere(t_sphere const *sphere, t_ray const *ray, t_intersect *out_intersect)
// {
// 	double const	distance = calculate_sphere_distance(sphere, ray);
// 	t_vec3			center_to_intersect;

// 	if (distance < 0)
// 	{
// 		return (NO_INTERSECTION);
// 	}
// 	out_intersect->distance = distance;
// 	out_intersect->position = t_ray_get_point(ray, distance);
// 	center_to_intersect = vec3_subtract(&out_intersect->position, &sphere->center);
// 	out_intersect->normal = vec3_normalize(&center_to_intersect);
// 	out_intersect->color = sphere->color;
// 	return (HAS_INTERSECTION);
// }

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
	out_intersect->color = plane->color;
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
	else if (shape->type == cylinder_type)
	{
		return (get_distance_to_cylinder(&shape->u_data.cylinder, ray, out_intersect));
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
				if (shape->type == sphere_type)
					out_intersect->color = shape->u_data.sphere.color;
				else if (shape->type == plane_type)
					out_intersect->color = shape->u_data.plane.color;
				else
					out_intersect->color = shape->u_data.cylinder.color;
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
