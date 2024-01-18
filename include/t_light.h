/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_light.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:02:06 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/18 14:53:04 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LIGHT_H
#define T_LIGHT_H
#include "t_color.h"
#include "t_vec3.h"

typedef enum
{
	e_point,
	e_directional,
}	t_light_type;

typedef struct s_light
{
	t_light_type	type;
	t_vec3			vector;//点光源の時は光源位置、面光源=光源の方向
	t_color			color;//[RGB][0.0 - 1.0]
	double			brightness;//[0.0 - 1.0]
}	t_light;

t_light	light_at(t_vec3 const *position);

#endif
