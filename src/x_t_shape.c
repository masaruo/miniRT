/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_t_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:31:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 09:49:22 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shape.h"
#include <math.h>
#include "math_utils.h"
#include "shadow.h"

// int	test_intersection(t_shape const *shape, t_ray const *ray, t_intersect *out_intersect)
// {
// 	if (shape->type == sphere_type)
// 	{
// 		return (get_distance_to_sphere(&shape->u_data.sphere, ray, out_intersect));
// 	}
// 	else if (shape->type == plane_type)
// 	{
// 		return (get_distance_to_plane(&shape->u_data.plane, ray, out_intersect));
// 	}
// 	else if (shape->type == cylinder_type)
// 	{
// 		return (get_distance_to_cylinder(&shape->u_data.cylinder, ray, out_intersect));
// 	}
// 	else
// 	{
// 		return (NO_INTERSECTION);
// 	}
// }

// int	test_all_intersection(t_list const * const shapes, t_ray const *ray, t_intersect *out_intersect)
// {
// 	t_list		*crnt;
// 	t_shape		*shape;
// 	t_intersect	crnt_intersect;
// 	bool		has_intersection;

// 	has_intersection = false;
// 	crnt = shapes->next;
// 	while (crnt)
// 	{
// 		shape = crnt->content;
// 		if(test_intersection(shape, ray, &crnt_intersect))
// 		{
// 			if (crnt_intersect.distance < out_intersect->distance)
// 			{
// 				out_intersect->distance = crnt_intersect.distance;
// 				out_intersect->normal = crnt_intersect.normal;
// 				out_intersect->position = crnt_intersect.position;
// 				if (shape->type == sphere_type)
// 					out_intersect->color = shape->u_data.sphere.color;
// 				else if (shape->type == plane_type)
// 					out_intersect->color = shape->u_data.plane.color;
// 				else
// 					out_intersect->color = shape->u_data.cylinder.color;
// 				has_intersection = true;
// 			}
// 		}
// 		crnt = crnt->next;
// 	}
// 	return (has_intersection);
// }

// int	test_shadow_intersection(t_list const * const shapes, t_light const *light, t_intersect const *intersect)
// {
// 	t_vec3	vector_light;
// 	t_ray	shadow_ray;
// 	t_list	*crnt;
// 	t_shape	*shape;
// 	t_intersect shadow_intersect;

// 	vector_light = vec3_subtract(&light->vector, &intersect->position);
// 	double	light_distance = vec3_length(&vector_light);
// 	double	light_distance_minus_epsilon = light_distance - EPSILON;

// 	shadow_ray.direction = vec3_normalize(&vector_light);
// 	t_vec3	tmp;
// 	tmp = vec3_multiply(&shadow_ray.direction, EPSILON);
// 	shadow_ray.start = vec3_add(&intersect->position, &tmp);

// 	crnt = shapes->next;
// 	while (crnt)
// 	{
// 		shape = crnt->content;
// 		if (test_intersection(shape, &shadow_ray, &shadow_intersect) == HAS_INTERSECTION)
// 		{
// 			if (shadow_intersect.distance < light_distance_minus_epsilon)
// 				return (HAS_INTERSECTION);
// 		}
// 		crnt = crnt->next;
// 	}
// 	return (NO_INTERSECTION);
// }
