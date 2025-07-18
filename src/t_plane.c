/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:48:11 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/09 19:20:49 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_plane.h"
#include "t_vec3.h"

static t_vec3_unit	get_normal(t_vec3_unit ray_dir, t_vec3_unit hit_normal)
{
	double const	ray_dot_hit = vec3_dot(ray_dir, hit_normal);
	t_vec3_unit		normal;

	if (ray_dot_hit <= 0)
	{
		normal = hit_normal;
	}
	else
	{
		normal = vec3_multiply(hit_normal, -1);
	}
	return (normal);
}

int	get_distance_to_plane(t_plane const *plane, \
				t_ray const *ray, t_intersect *out_intersect)
{
	t_vec3 const	pl_to_cam = vec3_subtract(ray->start, plane->position);
	double const	numerator = vec3_dot(pl_to_cam, plane->normal) * -1;
	double const	denominator = vec3_dot(ray->direction, plane->normal);
	double			distance;

	if (denominator == 0)
		return (NO_INTERSECTION);
	distance = numerator / denominator;
	if (distance < 0.0)
		return (NO_INTERSECTION);
	out_intersect->distance = distance;
	out_intersect->position = t_ray_get_point(ray, distance);
	out_intersect->normal = get_normal(ray->direction, plane->normal);
	out_intersect->color = plane->color;
	return (HAS_INTERSECTION);
}
