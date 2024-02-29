/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:04:06 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 15:08:20 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
}

double	vec3_square(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

t_vec3	vec3_normalize(t_vec3 a)
{
	double const	length = vec3_length(a);

	if (length <= 0)
		return (vec3_init(0, 0, 0));
	return (vec3_init(a.x / length, a.y / length, a.z / length));
}

t_vec3	vec3_normalized_subtract(t_vec3 a, t_vec3 b)
{
	t_vec3	new;

	new = vec3_subtract(a, b);
	new = vec3_normalize(new);
	return (new);
}
