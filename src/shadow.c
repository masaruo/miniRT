/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:43:09 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 10:10:33 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow.h"

t_ray	get_shadow_ray(t_intersect const *intersect, t_light const *light)
{
	t_vec3 const	intersect_to_light = vec3_subtract(light->vector, intersect->position);
	t_vec3 const	normalized_intersect_to_light = vec3_normalize(intersect_to_light);
	t_vec3 const	normalized_intersect_to_light_plus_epsilon = vec3_multiply(&normalized_intersect_to_light, EPSILON);
	t_ray			shadow_ray;
	double			distance_to_light = vec3_length(intersect_to_light);

	shadow_ray.start = vec3_add(intersect->position, normalized_intersect_to_light_plus_epsilon);
	shadow_ray.direction = normalized_intersect_to_light;
	shadow_ray.light_distance = distance_to_light - EPSILON;
	return (shadow_ray);
}
