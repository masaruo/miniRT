/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:56:27 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 17:09:12 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cylinder.h"
#include <stdbool.h>


static double	_get_length_of_projection(t_ray const *ray, t_cylinder const *cylinder, double distance)
{
	t_vec3_pos const	point = vec3_add(ray->start, vec3_multiply(ray->direction, distance));
	t_vec3 const		cylinder_pos_to_point = vec3_subtract(point, cylinder->position);
	double const		len_of_projection = vec3_dot(cylinder_pos_to_point, cylinder->normal);
	// t_vec3 const		projection = vec3_add(cylinder->position, vec3_multiply(cylinder->normal, len_of_projection));

	return (len_of_projection);
}

static bool	_is_contact_distance_valid(double distance, t_ray const *ray, t_cylinder const *cylinder)
{
	double const	len_of_projection = _get_length_of_projection(ray, cylinder, distance);

	if (distance >= 0 && len_of_projection >= 0 && len_of_projection <= cylinder->height)
		return (true);
	else
		return (false);
}

t_vec3	get_normal(double t, t_ray *ray, t_cylinder *cylinder, t_vec3 point, bool is_inside)
{
	t_vec3	normal;
	t_vec3	cylinder_center_to_point = vec3_subtract(point, cylinder->position);
	double	len_projection = vec3_dot(cylinder_center_to_point, cylinder->normal);
	t_vec3	projection = vec3_add(cylinder->position, vec3_multiply(cylinder->normal, len_projection));

	if (is_inside)
	{
		normal = vec3_normalized_subtract(projection, point);
		// normal = vec3_normalized_subtractx(point, projection);
	}
	else
	{
		normal = vec3_normalized_subtract(point, projection);
		// normal = vec3_normalized_subtractx(projection, point);
	}
	normal = vec3_normalized_subtract(point, projection);
	return (normal);
}

double	calculate_cylinder_distance(double A, double B, double C, t_vec3 *point, t_vec3 *normal, t_ray *ray, t_cylinder *cylinder)
{
	double	t;
	double	d = B * B - 4 * A * C;
	double	t_plus;
	double	t_minus;
	bool	is_tplus_valid;
	bool	is_tminus_valid;
	t_vec3	cylinder_to_point;

	t = -1;
	if (d < 0)
		return (t);
	t_plus = (-B + sqrt(d)) / (2 * A);
	t_minus = (-B - sqrt(d)) / (2 * A);

	is_tplus_valid = _is_contact_distance_valid(t_plus, ray, cylinder);
	is_tminus_valid = _is_contact_distance_valid(t_minus, ray, cylinder);

	if (is_tplus_valid && is_tminus_valid)
	{
		if (t_plus < t_minus)
		{
			t = t_plus;
		}
		else
		{
			t = t_minus;
		}
		*point = vec3_add(ray->start, vec3_multiply(ray->direction, t));
		*normal = get_normal(t, ray, cylinder, *point, false);
		return (t);
	}
	if (is_tplus_valid)
	{
		t = t_plus;
	}
	else if (is_tminus_valid)
	{
		t = t_minus;
	}
	*point = vec3_add(ray->start, vec3_multiply(ray->direction, t));
	*normal = get_normal(t, ray, cylinder, *point, true);
	// *normal = vec3_multiply(*normal, -1);
	return (t);
}

int	get_distance_to_cylinder(t_cylinder const *cylinder, t_ray const *ray, t_intersect *out_intersect)
{
	t_vec3	const	cylinder_to_ray = vec3_subtract(cylinder->position, ray->start);
	double const	a = _cylinder_get_a(ray->direction, cylinder->normal);
	double const	b = _cylinder_get_b(ray->direction, cylinder->normal, cylinder_to_ray);
	double const	c = _cylinder_get_c(cylinder->normal, cylinder_to_ray, cylinder->r);
	double const	d = b * b - 4 * a * c;

	if (a == 0 || d < 0)
	{
		return (NO_INTERSECTION);
	}
	t_vec3	point;
	t_vec3	normal;
	double t = calculate_cylinder_distance(a, b, c, &point, &normal, ray, cylinder);
	if (t < 0)
	{
		return (NO_INTERSECTION);
	}

	out_intersect->distance = t;
	out_intersect->position = t_ray_get_point(ray, t);
	out_intersect->normal = normal;
	out_intersect->color = cylinder->color;
	return (HAS_INTERSECTION);
}
