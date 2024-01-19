/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_intersect.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:21:56 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/19 16:17:19 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_INTERSECT_H
#define T_INTERSECT_H

#include "t_vec3.h"
#include "t_shape.h"
#include "t_ray.h"
#include "t_world.h"

#define NO_INTERSECTION (0)
#define HAS_INTERSECTION (1)
#define EPSILON (1.0f / 512)

typedef struct s_intersect
{
	double	distance;
	t_vec3	position;
	t_vec3	normal;//標準化後
	// t_shape	*nearest_shape;
}	t_intersect;

// int	get_intersect(t_shape const *shape, t_ray const *ray, t_intersect *ans);

#endif