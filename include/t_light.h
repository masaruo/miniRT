/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_light.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:02:06 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/01 15:13:36 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LIGHT_H
#define T_LIGHT_H

#include "t_color.h"
#include "t_vec3.h"

typedef struct s_light
{
	t_vec3			vector;//光源位置
	t_color			color;//[RGB][0.0 - 1.0]
	double			bright;//[0.0 - 1.0]
	t_color			brightness;
}	t_light;

// t_light	light_at(t_vec3 const *position);

#endif
