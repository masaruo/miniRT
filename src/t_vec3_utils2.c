/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:01:56 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 15:06:29 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

t_vec3	vec3_init(double in_x, double in_y, double in_z)
{
	t_vec3	vec;

	vec.x = in_x;
	vec.y = in_y;
	vec.z = in_z;
	return (vec);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_subtract(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec3_multiply(t_vec3 a, double scalar)
{
	return (vec3_init(a.x * scalar, a.y * scalar, a.z * scalar));
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
