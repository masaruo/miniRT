/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:56:27 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/05 18:08:18 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cylinder.h"
#include <stdbool.h>
#include "math_utils.h"
#include <math.h>

static double	get_projection_len_(t_cylinder_calc *cy_data, double distance)
{
	t_vec3_pos	point;
	t_vec3		cy_to_point;
	double		len_of_projection;

	point = vec3_add(cy_data->ray->start, \
			vec3_multiply(cy_data->ray->direction, distance));
	cy_to_point = vec3_subtract(point, cy_data->cy->position);
	len_of_projection = vec3_dot(cy_to_point, cy_data->cy->normal);
	return (len_of_projection);
}

static bool	is_distance_valid_(double distance, t_cylinder_calc *cy_data)
{
	double const	len_of_projection = get_projection_len_(cy_data, distance);

	if (len_of_projection >= 0 && len_of_projection <= cy_data->cy->height)
		return (true);
	else
		return (false);
}

t_vec3	get_normal(t_cylinder_calc *cy_data, double distance, bool is_inside)
{
	t_vec3_unit		normal;
	t_vec3_pos		projection;
	t_vec3_pos		point;
	double const	proj_len = get_projection_len_(cy_data, distance);

	point = t_ray_get_point(&cy_data->ray->start, distance);
	projection = vec3_add(cy_data->cy->position, \
				vec3_multiply(cy_data->cy->normal, proj_len));
	if (is_inside)
	{
		normal = vec3_normalized_subtract(projection, point);
	}
	else
	{
		normal = vec3_normalized_subtract(point, projection);
	}
	return (normal);
}

double	calculate_cylinder_distance(t_cylinder_calc *cy_data)
{
	double	t_distance;
	double	t_plus;
	double	t_minus;
	bool	is_tplus_valid;
	bool	is_tminus_valid;

	t_distance = -1;
	t_plus = (-(cy_data->b) + sqrt(cy_data->d)) / (2 * cy_data->a);
	is_tplus_valid = is_distance_valid_(t_plus, cy_data);
	t_minus = (-(cy_data->b) - sqrt(cy_data->d)) / (2 * cy_data->a);
	is_tminus_valid = is_distance_valid_(t_minus, cy_data);
	if (t_plus > 0 && t_minus > 0)
	{
		if (t_plus <= t_minus)
		{
			if (!is_tplus_valid)
			{
				if (is_tminus_valid)
				{
					t_distance = t_minus;
					cy_data->is_inside = true;
				}
			}
			else
			t_distance = t_plus;
		}
		else if (t_minus < t_plus)
		{
			if (!is_tminus_valid)
			{
				if (is_tplus_valid)
				{
					t_distance = t_plus;
					cy_data->is_inside = true;
				}
			}
			else
				t_distance = t_minus;
		}
	}
	else if (t_plus > 0)
	{
		if (is_tplus_valid)
			t_distance = t_plus;
	}
	else if (t_minus > 0)
	{
		if (is_tminus_valid)
			t_distance = t_minus;
	}
	return (t_distance);
}

int	get_distance_to_cylinder(t_cylinder const *cylinder, \
			t_ray const *ray, t_intersect *out_intersect)
{
	t_cylinder_calc	cy_data;
	double			t_distance;

	cy_data = cylinder_data_init(cylinder, ray);
	if (cy_data.a == 0 || cy_data.d < 0)
		return (NO_INTERSECTION);
	t_distance = calculate_cylinder_distance(&cy_data);
	if (t_distance < 0)
		return (NO_INTERSECTION);
	out_intersect->distance = t_distance;
	out_intersect->position = t_ray_get_point(ray, t_distance);
	out_intersect->normal = get_normal(&cy_data, t_distance, cy_data.is_inside);
	out_intersect->color = cylinder->color;
	return (HAS_INTERSECTION);
}
