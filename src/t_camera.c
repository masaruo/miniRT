/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:03:56 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/07 16:00:36 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_camera.h"
#include "t_ray.h"
#include "t_world.h"
#include <math.h>
#include <math_utils.h>

static double	_get_distance_to_screen(double width, double fov)
{
	double	t;
	double	vetted_fov;

	vetted_fov = d_clamp(fov, 1, 179);
	t = (width / 2.0) / (tan(convert_degree_to_radian(vetted_fov / 2)));
	return (t);
}

static t_vec3	get_right_vec(t_vec3 fwd)
{
	t_vec3_unit	assumption;
	t_vec3_unit	right;

	assumption = vec3_init(0, 0, 0);
	if (fwd.x == 0 && fwd.z == 0)
	{
		if (fwd.y > 0.9)
		{
			assumption = vec3_init(0, 0, -1);
		}
		else if (fwd.y < -0.9)
		{
			assumption = vec3_init(0, 0, 1);
		}
	}
	else
		assumption = vec3_init(0, -1, 0);
	right = vec3_normalize(vec3_cross(fwd, assumption));
	return (right);
}

t_vec3_pos	conv_xy_to_world(\
	t_vec3 fwd, double raw_x, double raw_y, double dist)
{
	t_vec3_unit const	right = get_right_vec(fwd);
	t_vec3_unit const	up = vec3_normalize(vec3_cross(fwd, right));
	double const		screen_z = dist;
	t_vec3				point;

	point = vec3_init(0, 0, 0);
	point.x = raw_x * right.x + raw_y * right.y + screen_z * right.z;
	point.y = raw_x * up.x + raw_y * up.y + screen_z * up.z;
	point.z = raw_x * fwd.x + raw_y * fwd.y + screen_z * fwd.z;
	return (point);
}

t_ray	get_camera_ray(\
			t_camera camera, double screen_x, double screen_y, double width)
{
	double const	distance_to_screen = \
		_get_distance_to_screen(width, camera.field_of_view);
	t_vec3_pos		xy_in_world_coord;
	t_ray			camera_ray;

	xy_in_world_coord = conv_xy_to_world(\
		camera.orientation, screen_x, screen_y, distance_to_screen);
	camera_ray.light_distance = 0;
	camera_ray.start = camera.position;
	camera_ray.direction = vec3_normalized_subtract(\
		xy_in_world_coord, camera.position);
	return (camera_ray);
}
