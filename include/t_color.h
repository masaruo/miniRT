/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:38:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/19 17:13:30 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COLOR_H
#define T_COLOR_H

#include <stdint.h>

#include "t_shape.h"
#include "t_intersect.h"
#include "t_light.h"
#include "t_ray.h"

typedef struct s_color
{
	double	red;
	double	green;
	double	blue;
}	t_color;

uint32_t	tcolor_to_hex(t_color color);
t_color		tcolor_normalize(t_color color);
t_color		tcolor_set(double red, double green, double blue);
t_color		tcolor_add(t_color a, t_color b);
t_color		tcolor_multiply(t_color a, t_color b);
t_color		tcolor_scalar_multiply(t_color a, double scalar);
int			tcolor_convert_strcolor(t_color *color, char *rgbstr);
t_color		tcolor_calc_phong(t_shape const *nearest, t_intersect const *intersect, t_light const *light, t_ray const *eye);

// ! temporal
t_color		tcolor_convert_rgbcolor(double red, double green, double blue);
u_int32_t	get_hex_color(int r, int g, int b);

#endif