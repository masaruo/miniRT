/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_intersect.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:21:56 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/16 11:33:04 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_INTERSECT_H
#define T_INTERSECT_H
#include "t_vec3.h"
#include "t_shape.h"
#include "t_ray.h"
#include "t_scene.h"

#define NO_INTERSECTION (0)
#define HAS_INTERSECTION (1)

typedef struct s_intersect
{
	double	distance;
	t_vec3	position;
	t_vec3	normal;//標準化後
}	t_intersect;

int	get_intersect(t_shape const *shape, t_ray const *ray, t_intersect *ans);
int	get_nearest_shape(t_scene const *scene, t_ray const *ray, double max_distance, int exit_once_found, t_shape **out_shape, t_intersect *out_intersect);

#endif