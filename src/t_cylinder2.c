/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:00:53 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 16:49:09 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cylinder.h"

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
