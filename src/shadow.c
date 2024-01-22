/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:43:09 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/22 17:19:00 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow.h"
#include "t_ray.h"
#include "t_intersect.h"
#include "t_light.h"

t_ray	get_shadow_ray(t_intersect const *intersect, t_light const *light)
{
	t_ray	shadow_ray;
	t_vec3 const	intersect_to_light = vec3_subtract(&light->vector, &intersect->position);
	double			distance_to_light = vec3_length(&intersect_to_light);
	t_vec3 const	normalized_intersect_to_light = vec3_normalize(&intersect_to_light);
	t_vec3 const	normalized_intersect_to_light_plus_epsilon = vec3_multiply(&normalized_intersect_to_light, EPSILON);

	shadow_ray.start = vec3_add(&intersect->position, &normalized_intersect_to_light_plus_epsilon);
	shadow_ray.direction = normalized_intersect_to_light;
	shadow_ray.light_distance = distance_to_light - EPSILON;
	return (shadow_ray);
}
