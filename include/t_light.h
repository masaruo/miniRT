/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_light.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:02:06 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 10:47:35 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LIGHT_H
#define T_LIGHT_H

#include "t_color.h"
#include "t_vec3.h"

typedef struct s_light
{
	t_vec3_pos	vector;//光源位置
	t_color		color;//[RGB][0.0 - 1.0]
	double		brightness;//[0.0 - 1.0]
}	t_light;

#endif
