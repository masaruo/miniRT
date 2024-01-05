/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:23:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/05 16:13:03 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

double	vec3_dot(t_vec3 const *a, t_vec3 const *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vec3	vec3_cross(t_vec3 const *a, t_vec3 const *b)
{
	t_vec3	vector;

	vector.x = a->y * b->z - a->z * b->y;
	vector.y = a->z * b->x - a->x * b->z;
	vector.z = a->x * b->y - a->y * b->x;
	return (vector);
}

double	vec3_lengthSq(t_vec3 const *a)
{
	return (a->x * a->x + a->y * a->y + a->z * a->z);
}

double	vec3_length(t_vec3 const *a)
{
	return (sqrt(vec3_lengthSq(a)));
}

t_vec3	vec3_normalize(t_vec3 const *a)
{
	double const	length = vec3_length(a);

	return (vec3_init(a->x / length, a->y / length, a->z / length));
}
