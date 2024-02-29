/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:54:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 17:23:23 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_color.h"

// uint32_t	get_hex_color(int r, int g, int b)
// {
// 	uint32_t	color;

// 	color = 0;
// 	color |= b;
// 	color |= g << 8;
// 	color |= r << 16;
// 	return (color);
// }

// uint32_t	tcolor_to_hex(t_color color)
// {
// 	int const	r = color.red * 255;
// 	int const	g = color.green * 255;
// 	int const	b = color.blue * 255;

// 	return (get_hex_color(r, g, b));
// }

// t_color	tcolor_clamp(t_color color)
// {
// 	t_color	new;

// 	new.red = d_clamp(color.red, 0, 1);
// 	new.green = d_clamp(color.green, 0, 1);
// 	new.blue = d_clamp(color.blue, 0, 1);
// 	return (new);
// }

// t_color	tcolor_init(double r, double g, double b)
// {
// 	t_color	new;

// 	new.red = r;
// 	new.green = g;
// 	new.blue = b;
// 	return (tcolor_clamp(new));
// }
