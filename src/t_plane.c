/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:48:11 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 10:21:08 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_plane.h"

int	get_distance_to_plane(t_plane const *plane, t_ray const *ray, t_intersect *out_intersect)
{
	t_vec3 const	plane_to_camera = vec3_subtract(ray->start, plane->position);
	double const	numerator = vec3_dot(plane_to_camera, plane->normal) * -1;
	double const	denominator = vec3_dot(ray->direction, plane->normal);
	double			distance;

	if (denominator == 0)
		return (NO_INTERSECTION);
	distance = numerator / denominator;
	if (distance < 0)
		return (NO_INTERSECTION);
	out_intersect->distance = distance;
	out_intersect->position = t_ray_get_point(ray, distance);
	out_intersect->normal = plane->normal;
	out_intersect->color = plane->color;
	return (HAS_INTERSECTION);
}
