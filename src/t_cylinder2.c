/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:00:53 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/06 17:20:40 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cylinder.h"
#include "math.h"

double	_cylinder_get_a(t_vec3_unit d, t_vec3_unit v)
{
	double const	dv = vec3_dot(d, v);
	double const	dv_pow2 = dv * dv;
	double const	a = vec3_dot(d, d) - dv_pow2;

	return (a);
}

double	_cylinder_get_b(t_vec3_unit d, t_vec3_unit v, t_vec3_unit c)
{
	double const	dv = vec3_dot(d, v);
	double const	dc = vec3_dot(d, c);
	double const	cv = vec3_dot(c, v);
	double const	b = 2 * (cv * dv - dc);

	return (b);
}

double	_cylinder_get_c(t_vec3_unit v, t_vec3_unit c, double r)
{
	double const	cc = vec3_dot(c, c);
	double const	cv = vec3_dot(c, v);
	double const	c_quadratic = cc - cv * cv - r * r;

	return (c_quadratic);
}

t_cylinder_calc	cylinder_data_init(t_cylinder const *cy, t_ray const *ray)
{
	t_cylinder_calc	cy_data;
	t_vec3 const	cy_to_eye = vec3_subtract(cy->position, ray->start);

	cy_data.cy = cy;
	cy_data.ray = ray;
	cy_data.a = _cylinder_get_a(ray->direction, cy->normal);
	cy_data.b = _cylinder_get_b(ray->direction, cy->normal, cy_to_eye);
	cy_data.c = _cylinder_get_c(cy->normal, cy_to_eye, cy->r);
	cy_data.d = cy_data.b * cy_data.b - 4 * cy_data.a * cy_data.c;
	if (cy_data.a == 0 || cy_data.d < 0)
		return (cy_data);
	cy_data.dist_plus = (-cy_data.b + sqrt(cy_data.d)) / (2 * cy_data.a);
	cy_data.dist_minus = (-cy_data.b - sqrt(cy_data.d)) / (2 * cy_data.a);
	cy_data.is_dist_p_valid = is_distance_valid_(cy_data.dist_plus, &cy_data);
	cy_data.is_dist_m_valid = is_distance_valid_(cy_data.dist_minus, &cy_data);
	cy_data.distance = -1;
	cy_data.is_inside = false;
	return (cy_data);
}

void	get_dist_n_inside(t_cylinder_calc *cy, double distance)
{
	cy->distance = distance;
	cy->is_inside = true;
}
