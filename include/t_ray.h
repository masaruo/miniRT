/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:57:18 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/22 16:43:45 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAY_H
#define T_RAY_H

#include "t_vec3.h"

typedef struct s_ray
{
	t_vec3	start;//視点の位置ベクトル
	t_vec3	direction;//方向ベクトル（ノーマライズ）
	double	light_distance;// only used for shadow
}	t_ray;

t_ray	t_ray_create_ray(t_vec3 const *start, t_vec3 const *end);
t_vec3	t_ray_get_point(t_ray const *this, double distance);

#endif