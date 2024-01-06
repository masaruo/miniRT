/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:58:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/06 15:47:17 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

t_vec3	vec3_add(t_vec3 const *a, t_vec3 const *b)
{
	return (vec3_init(a->x + b->x, a->y + b->y, a->z + b->z));
}

t_vec3	vec3_subtract(t_vec3 const *a, t_vec3 const *b)
{
	return (vec3_init(a->x - b->x, a->y - b->y, a->z - b->z));
}

t_vec3	vec3_multiply(t_vec3 const *a, double scalar)
{
	return (vec3_init(a->x * scalar, a->y * scalar, a->z * scalar));
}
