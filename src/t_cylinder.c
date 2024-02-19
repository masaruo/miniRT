/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:56:27 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 08:27:41 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cylinder.h"
#include <stdbool.h>

static double	_cylinder_get_a(t_normalized_vec3 d, t_normalized_vec3 v)
{
	double const	dv = vec3_dotx(d, v);
	double const	dv_pow2 = dv * dv;
	double const	a = vec3_dotx(d, d) - dv_pow2;

	return (a);
}

static double	_cylinder_get_b(t_normalized_vec3 d, t_normalized_vec3 v, t_position_vec3 c)
{
	double dv = vec3_dotx(d, v);
	double vv = vec3_dotx(v, v);
	double dc = vec3_dotx(d, c);
	double cv = vec3_dotx(c, v);

	double b = 2 * (cv * dv - dc);
	// double b = -2 * (dc - (cv * dv));
	return (b);
}

static double	_cylinder_get_c(t_normalized_vec3 v, t_position_vec3 c, double r)
{
	double	c_quadratic;

	double cc = vec3_dotx(c, c);
	double cv = vec3_dotx(c, v);
	double cv_pow2 = cv * cv;
	double vv = vec3_dotx(v, v);

	c_quadratic = cc - cv_pow2 - r * r;
	return (c_quadratic);
}

double	get_length_of_projection(t_ray *ray, t_cylinder *cylinder, t_vec3 point)
{
	t_vec3	cylinder_center_to_point = vec3_subtractx(point, cylinder->position);
	double	len_projection = vec3_dotx(cylinder_center_to_point, cylinder->normal);
	return (len_projection);
}

t_vec3	get_normal(double t, t_ray *ray, t_cylinder *cylinder, t_vec3 point, bool is_inside)
{
	t_vec3	normal;
	t_vec3	cylinder_center_to_point = vec3_subtractx(point, cylinder->position);
	double	len_projection = vec3_dotx(cylinder_center_to_point, cylinder->normal);
	t_vec3	projection = vec3_addx(cylinder->position, vec3_multiplyx(cylinder->normal, len_projection));

	if (is_inside)
	{
		normal = vec3_normalized_subtractx(projection, point);
		// normal = vec3_normalized_subtractx(point, projection);
	}
	else
	{
		normal = vec3_normalized_subtractx(point, projection);
		// normal = vec3_normalized_subtractx(projection, point);
	}
	normal = vec3_normalized_subtractx(point, projection);
	return (normal);
}

double	calculate_cylinder_distance(double A, double B, double C, t_vec3 *point, t_vec3 *normal, t_ray *ray, t_cylinder *cylinder)
{
	double	t;
	double	d = B * B - 4 * A * C;
	double	t_plus;
	double	t_minus;
	t_vec3	cylinder_to_point;

	t = -1;
	if (d < 0)
		return (t);
	t_plus = (-B + sqrt(d)) / (2 * A);
	t_minus = (-B - sqrt(d)) / (2 * A);
	if (t_plus > 0 && t_minus > 0)
	{
		if (t_plus < t_minus)
		{
			t = t_plus;
		}
		else
		{
			t = t_minus;
		}
		*point = vec3_addx(ray->start, vec3_multiplyx(ray->direction, t));
		*normal = get_normal(t, ray, cylinder, *point, false);
		return (t);
	}
	else if (t_plus > 0 || t_minus > 0)
	{
		if (t_plus > 0)
		{
			t = t_plus;
		}
		else
		{
			t = t_minus;
		}
		*point = vec3_addx(ray->start, vec3_multiplyx(ray->direction, t));
		*normal = get_normal(t, ray, cylinder, *point, true);
	}
	return (t);
}

double	_cylinder_get_params(double A, double B, double D, double *m, t_vec3 *normal, t_vec3 s, t_vec3 v, t_vec3 c, t_vec3 d, double height)
{
	double	t_distance;
	double	t_plus;
	double	t_minus;
	t_vec3	P;

	t_distance = -1;
	t_plus = -B + sqrt(D) / 2 * A;
	t_minus = -B - sqrt(D) / 2 * A;
	if (t_plus > 0 && t_minus > 0)
	{
		if (t_plus < t_minus)
		{
			t_distance = t_plus;
		}
		else
		{
			t_distance = t_minus;
		}
		// *m = t_distance * vec3_dotx(d, v) + 2 * vec3_dotx(s, v) - vec3_dotx(c, c);
		P = vec3_addx(s, vec3_multiplyx(d, t_distance));
		t_vec3	p_to_c = vec3_subtractx(c, P);
		double _m = vec3_dotx(p_to_c, v);
		*m = _m;
		t_vec3	projection = vec3_multiplyx(v, _m);
		t_vec3	N = vec3_normalized_subtractx(P, projection);
		*normal = N;
	}
	else if (t_plus > 0 || t_plus > 0)
	{
		if (t_plus > 0)
		{
			t_distance = t_plus;
		}
		else
		{
			t_distance = t_minus;
		}
		// *m = t_distance * vec3_dotx(d, v) + 2 * vec3_dotx(s, v) - vec3_dotx(c, c);
		P = vec3_addx(s, vec3_multiplyx(d, t_distance));
		t_vec3	p_to_c = vec3_subtractx(c, P);
		double _m = vec3_dotx(p_to_c, v);
		*m = _m;
		t_vec3	projection = vec3_multiplyx(v, _m);
		t_vec3	N = vec3_normalized_subtractx(P, projection);
		N = vec3_multiplyx(N, -1);
		*normal = N;
	}
	return (t_distance);
}

int	get_distance_to_cylinder(t_cylinder const *cylinder, t_ray const *ray, t_intersect *out_intersect)
{
	double	t1, t2;
	double	r = cylinder->r;
	t_vec3	s = ray->start;
	t_vec3	d = ray->direction;
	t_vec3	cylinder_to_ray;
	// t_vec3	cylinder_to_ray = vec3_subtractx(ray->start, cylinder->position);
	cylinder_to_ray = vec3_subtractx(cylinder->position, ray->start);
	// cylinder_to_ray= cylinder->position;
	t_vec3	c = cylinder->position;
	t_vec3	v = cylinder->normal;
	t_normalized_vec3	intersect_normal1;

	double	A = _cylinder_get_a(d, v);
	double	B = _cylinder_get_b(d, v, cylinder_to_ray);
	double	C = _cylinder_get_c(v, cylinder_to_ray, r);
	double	D = B * B - 4 * A * C;
	
	if (A == 0 || D < 0)
	{
		return (NO_INTERSECTION);
	}
	// double	m = -1;
	t_vec3	point;
	t_vec3	normal;
	double t = calculate_cylinder_distance(A, B, C, &point, &normal, ray, cylinder);
	if (t < 0)
	{
		return (NO_INTERSECTION);
	}
	double	m = get_length_of_projection(ray, cylinder, point);
	if (m > cylinder->height || m < 0)
	{
		return (NO_INTERSECTION);
	}

	out_intersect->distance = t;
	out_intersect->position = t_ray_get_point(ray, t);
	out_intersect->normal = normal;
	out_intersect->color = cylinder->color;
	return (HAS_INTERSECTION);
}
