/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:57:18 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/11 11:49:09 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAY_H
#define T_RAY_H
#include "t_vec3.h"

typedef struct s_ray
{
	t_vec3	start;//視点のいちベクトル
	t_vec3	direction;//方向ベクトル
	double	t;//?必要性？
}	t_ray;

// t_ray	t_ray_init(t_vec3 const *s, t_vec3 const *d);

#endif