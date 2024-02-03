/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:22:03 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/03 14:20:29 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "math_utils.h"
#include "t_color.h"
#include "libft.h"

t_color	tcolor_clamp(t_color color)
{
	t_color	new;

	new.red = double_clamp(color.red, 0, 1);
	new.green = double_clamp(color.green, 0, 1);
	new.blue = double_clamp(color.blue, 0, 1);
	return (new);
}

uint32_t	get_hex_color(int r, int g, int b)//todo to be static
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
	return(get_hex_color(color.red * 255, color.green * 255, color.blue * 255));
}

//rgb data is already clamped
t_color	tcolor_set(double r, double g, double b)
{
	t_color	new;

	new.red = r;
	new.green = g;
	new.blue = b;
	return (tcolor_clamp(new));
}

t_color	tcolor_add(t_color a, t_color b)
{
	t_color new;

	new.red = a.red + b.red;
	new.green = a.green + b.green;
	new.blue = a.blue + b.blue;
	return (tcolor_clamp(new));
}

t_color	tcolor_multiply(t_color a, t_color b)
{
	t_color	new;

	new.red = a.red * b.red;
	new.green = a.green * b.green;
	new.blue = a.blue * b.blue;
	return (tcolor_clamp(new));
}

t_color	tcolor_scalar_multiply(t_color a, double scalar)
{
	t_color	new;

	new.red = a.red * scalar;
	new.green = a.green * scalar;
	new.blue = a.blue * scalar;
	return (tcolor_clamp(new));
}

t_color	tcolor_convert_rgbcolor(double r, double g, double b)
{
	t_color	new;

	new.red = r / 255.0f;
	new.green = g / 255.0f;
	new.blue = b / 255.0f;
	return (tcolor_clamp(new));
}

#include <stdlib.h>//! delete
t_color	tcolor_str_set(char const *line)
{
	t_color		color;
	char const	**lines = ft_split(line, ',');//! handle leak
	char const	*r = lines[0];
	char const	*g = lines[1];
	char const	*b = lines[2];

	// color = tcolor_set(atof(r), atof(g), atof(b));//! FORBIDDEN ATOF
	// color = tcolor_set(ft_atoi(r), ft_atoi(g), ft_atoi(b));
	color = tcolor_convert_rgbcolor(ft_atoi(r), ft_atoi(g), ft_atoi(b));
	return (color);
}
