/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:43:09 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/16 14:33:15 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow.h"

double const	g_epsilon = 1.0f / 10000.0;

t_ray	get_shadow_ray(t_intersect const *intersect, t_light const *light)
{
	t_vec3 const		to_light = \
		vec3_subtract(light->vector, intersect->position);
	t_vec3_unit const	to_light_dir = vec3_normalize(to_light);
	t_vec3_pos const	epsilon_pos = \
		vec3_multiply(intersect->normal, g_epsilon);
	double const		distance_to_light = vec3_length(to_light);
	t_ray				shadow_ray;

	shadow_ray.start = vec3_add(intersect->position, epsilon_pos);
	shadow_ray.direction = to_light_dir;
	shadow_ray.light_distance = distance_to_light - g_epsilon;
	return (shadow_ray);
}
