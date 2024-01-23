/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_intersect.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:21:56 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/23 09:44:17 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_INTERSECT_H
#define T_INTERSECT_H

#include "t_vec3.h"
// #include "t_color.h"
#include <stdbool.h>
// #include "t_ray.h"
// #include "t_world.h"
#include "t_material.h"

#define NO_INTERSECTION (0)
#define HAS_INTERSECTION (1)
#define EPSILON (1.0f / 512)

typedef struct s_intersect
{
	bool		has_intersection;
	double		distance;
	t_vec3		position;
	t_vec3		normal;//標準化後
	t_material	material;
}	t_intersect;

#endif