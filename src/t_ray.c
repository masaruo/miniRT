/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:32:22 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 10:02:07 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_ray.h"
#include <math.h>
#include "math_utils.h"

t_ray	t_ray_create_ray(t_vec3 const *start, t_vec3 const *end)
{
	t_ray	new;
	t_vec3 const	start_to_screen = vec3_subtract(end, start);

	new.start = *start;
	new.direction = vec3_normalize(&start_to_screen);
	return (new);
}

t_vec3	t_ray_get_point(t_ray const *this, double distance)
{
	t_vec3	point;
	t_vec3	td;

	td = vec3_multiply(&this->direction, distance);
	point = vec3_add(this->start, td);
	return (point);
}

//!マイナス回転
t_vec3	_rotate_x(t_vec3 const *vec, double cosB, double sinB)
{
	t_vec3			rotated;

	rotated.x = vec->x;
	rotated.y = vec->y * cosB + vec->z * sinB;
	rotated.z = vec->z * cosB - vec->y * sinB;
	return (rotated);
}

t_vec3	_rotate_y(t_vec3 const *vec, double cosA, double sinA)
{
	t_vec3			rotated;

	rotated.y = vec->y;
	rotated.x = vec->x * cosA - vec->z * sinA;
	rotated.z = vec->z * cosA + vec->x * sinA;
	return (rotated);
}

//!マイナス回転
t_vec3	_rotate_z(t_vec3 const *vec, double cosG, double sinG)
{
	t_vec3			rotated;

	rotated.z = vec->z;
	rotated.x = vec->x * cosG + vec->y * sinG;
	rotated.y = vec->y * cosG - vec->x * sinG;
	return (rotated);
}

t_vec3	t_ray_screen_to_world(t_vec3 const *camera_pos, double screen_width, double fov)
{
	t_vec3	base;
	t_vec3	s = *camera_pos;
	double	t;
	t_vec3	camera_to_target;
	t_vec3	d;
	t_vec3	td;
	t_vec3 const	target = vec3_init(0, 0, 0);
	double	gamma = 0;

	// todo get_screen_base_on_world
	t = (screen_width / 2) * (1 / tan(1 / 2 * fov));
	d = vec3_normalized_subtract(&target, &s);
	td = vec3_multiply(&d, t);
	base = vec3_add(s, td);

	//sin cos
	double sin_a = d.x / sqrt(d.x * d.x + d.z * d.z);
	double cos_a = d.z / sqrt(d.x * d.x + d.z * d.z);
	double sin_b = d.y;
	double cos_b = sqrt(d.x * d.x + d.z * d.z);
	double cos_g = cos(convert_degree_to_radian(gamma));
	double sin_g = sin(convert_degree_to_radian(gamma));

	//rotation
	t_vec3	camera_on_world;
	camera_on_world = *camera_pos;
	camera_on_world = _rotate_z(&camera_on_world, cos_g, sin_g);
	camera_on_world = _rotate_x(&camera_on_world, cos_b, sin_b);
	camera_on_world = _rotate_y(&camera_on_world, cos_a, sin_a);
	// camera_on_world.x = camera_pos->x * (cos_a * cos_g + sin_a * sin_b * sin_g) + camera_pos->y * (cos_a * sin_g - sin_a * sin_b * cos_g) + camera_pos->z * (sin_a * cos_b) + base.x;
	// camera_on_world.y = -camera_pos->x * (cos_b * sin_g) + camera_pos->y * cos_b * cos_g + camera_pos->z * sin_b + base.y;
	// camera_on_world.z = -camera_pos->x * (sin_a * cos_g - cos_a * sin_b * sin_g) - camera_pos->y * (sin_a * sin_g + cos_a + sin_b * cos_g) + camera_pos->z * cos_a * cos_b + base.z;
	camera_on_world = vec3_add(camera_on_world, base);
	return (camera_on_world);
}
