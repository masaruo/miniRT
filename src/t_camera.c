/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:03:56 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/21 11:36:39 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_camera.h"
#include "t_ray.h"
#include "t_world.h"
#include <math.h>
#include <math_utils.h>

static double	_get_distance_to_screen(double width, double fov)
{
	double const	t = (width / 2.0) / (tan(convert_degree_to_radian(fov/2)));

	return (t);
}

t_vec3_pos	convert_xy_to_world_coord(t_vec3_unit d, double screen_x, double screen_y, double distance)
{
	t_vec3_unit	const	forward = d;
	t_vec3_unit const	right = vec3_normalize(vec3_cross(vec3_init(0, 1, 0), forward));
	t_vec3_unit const	up = vec3_normalize(vec3_cross(forward, right));
	double const		screen_z = distance;
	t_vec3				point;

	double	x;
	double	y;
	double	z;

	x = screen_x * right.x + screen_y * right.y + screen_z * right.z;
	y = screen_x * up.x + screen_y * up.y + screen_z * up.z;
	z = screen_x * forward.x + screen_y * forward.y + screen_z * forward.z;
	
	point = vec3_init(x, y, z);

	return (point);
}

t_ray	get_camera_ray(t_camera camera, double screen_x, double screen_y, double width)
{
	t_vec3_pos	xy_in_world_coord;
	t_ray		camera_ray;
	double const	distance_to_screen = _get_distance_to_screen(width, camera.field_of_view);

	xy_in_world_coord = convert_xy_to_world_coord(camera.orientation, screen_x, screen_y, distance_to_screen);
	camera_ray.light_distance = 0;
	camera_ray.start = camera.position;
	camera_ray.direction = vec3_normalized_subtract(xy_in_world_coord, camera.position);
	return (camera_ray);
}
