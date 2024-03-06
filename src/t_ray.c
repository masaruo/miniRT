/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:32:22 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/06 14:54:50 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_ray.h"
#include <math.h>
#include "math_utils.h"

t_ray	t_ray_create_ray(t_vec3 const *start, t_vec3 const *end)
{
	t_ray			new;
	t_vec3 const	start_to_screen = vec3_subtract(*end, *start);

	new.start = *start;
	new.direction = vec3_normalize(start_to_screen);
	return (new);
}

t_vec3	t_ray_get_point(t_ray const *this, double distance)
{
	t_vec3	point;
	t_vec3	td;

	td = vec3_multiply(this->direction, distance);
	point = vec3_add(this->start, td);
	return (point);
}
