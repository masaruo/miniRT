/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:54:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 12:28:25 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_color.h"

static uint32_t	get_hex_color(int r, int g, int b)
{
	uint32_t	color;

	color = 0;
	color |= b;
	color |= g << 8;
	color |= r << 16;
	return (color);
}

uint32_t	tcolor_to_hex(t_color color)
{
	u_int32_t	mlx_color;
	int const	r = color.red * 255;
	int const	g = color.green * 255;
	int const	b = color.blue * 255;

	mlx_color = get_hex_color(r, g, b);
	return (mlx_color);
}

t_color	tcolor_rgb_init(double r, double g, double b)
{
	t_color	new;

	new.red = r / 255.0f;
	new.green = g / 255.0f;
	new.blue = b / 255.0f;
	return (tcolor_clamp(new));
}

t_color	tcolor_init(double r, double g, double b)
{
	t_color	new;

	new.red = r;
	new.green = g;
	new.blue = b;
	return (tcolor_clamp(new));
}
