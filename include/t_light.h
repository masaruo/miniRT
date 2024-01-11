/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_light.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:02:06 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/11 12:50:58 by mogawa           ###   ########.fr       */
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
}	e_light_type;

typedef struct s_light
{
	e_light_type	type;
	t_vec3			vector;
	t_color			color;
	double			brightness;
}	t_light;

#endif
