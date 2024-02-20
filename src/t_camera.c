/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:03:56 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/20 14:16:27 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_camera.h"
#include <math.h>
#include <math_utils.h>

static double	_get_distance_to_screen(double width, double fov)
{
	double const	t = (width / 2.0) / (tan(convert_degree_to_radian(fov/2)));

	return (t);
}

t_vec3_unit get_world_ray_direction(double x, double y, t_vec3_pos s, t_vec3_unit d, double width, double fov)
{
	t_vec3_pos const	k = vec3_init(x, y, 0.0);
	double const		t = _get_distance_to_screen(width, fov);
	t_vec3_pos const	td = vec3_multiply(d, t);
	t_vec3				s_plus_td = vec3_add(s, td);
	t_vec3_pos			p;
	t_vec3_unit			direction_vector;

	p = vec3_subtract(vec3_add(s_plus_td, s_plus_td), k);
	direction_vector = vec3_normalized_subtract(p, s);
}
