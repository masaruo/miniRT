/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:56:27 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/06 14:48:06 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cylinder.h"
#include <stdbool.h>
#include "math_utils.h"

static double	get_proj_len_(t_cylinder_calc const *cy_data, double distance)
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

bool	is_distance_valid_(double distance, t_cylinder_calc const *cy_data)
{
	double const	len_of_projection = get_proj_len_(cy_data, distance);

	if (len_of_projection >= 0 && len_of_projection <= cy_data->cy->height)
		return (true);
	else
		return (false);
}

t_vec3	get_normal(t_cylinder_calc const *cy_data, double distance)
{
	t_vec3_unit		normal;
	t_vec3_pos		projection;
	t_vec3_pos		point;
	double const	proj_len = get_proj_len_(cy_data, distance);

	point = t_ray_get_point(&cy_data->ray->start, distance);
	projection = vec3_add(cy_data->cy->position, \
				vec3_multiply(cy_data->cy->normal, proj_len));
	if (cy_data->is_inside)
	{
		normal = vec3_normalized_subtract(projection, point);
	}
	else
	{
		normal = vec3_normalized_subtract(point, projection);
	}
	return (normal);
}

static void	calculate_cylinder_distance(t_cylinder_calc *cy_data)
{
	if (cy_data->dist_plus > 0 && cy_data->dist_minus > 0)
	{
		if (cy_data->dist_plus <= cy_data->dist_minus)
		{
			if (cy_data->is_dist_p_valid)
				cy_data->distance = cy_data->dist_plus;
			else if (cy_data->is_dist_m_valid)
				get_dist_n_inside(cy_data, cy_data->dist_minus);
		}
		else
		{
			if (cy_data->is_dist_m_valid)
				cy_data->distance = cy_data->dist_minus;
			else if (cy_data->is_dist_p_valid)
				get_dist_n_inside(cy_data, cy_data->dist_plus);
		}
	}
	else if (cy_data->dist_plus > 0 && cy_data->is_dist_p_valid)
		cy_data->distance = cy_data->dist_plus;
	else if (cy_data->dist_minus > 0 && cy_data->is_dist_m_valid)
		cy_data->distance = cy_data->dist_minus;
}

int	get_distance_to_cylinder(t_cylinder const *cylinder, \
			t_ray const *ray, t_intersect *out_intersect)
{
	t_cylinder_calc	cy_data;
	double			t_distance;

	cy_data = cylinder_data_init(cylinder, ray);
	if (cy_data.a == 0 || cy_data.d < 0)
		return (NO_INTERSECTION);
	calculate_cylinder_distance(&cy_data);
	t_distance = cy_data.distance;
	if (t_distance < 0)
		return (NO_INTERSECTION);
	out_intersect->distance = t_distance;
	out_intersect->position = t_ray_get_point(ray, t_distance);
	out_intersect->normal = get_normal(&cy_data, t_distance);
	out_intersect->color = cylinder->color;
	return (HAS_INTERSECTION);
}
