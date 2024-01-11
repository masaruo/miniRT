/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:22:03 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/10 13:22:37 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_color.h"

static double	get_minzero_maxone_number(double number)
{
	if (number < 0)
		return (0);
	else if (number > 1)
		return (1);
	else
		return (number);
}

uint32_t	get_hex_color(int r, int g, int b)
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

t_color	tcolor_normalize(t_color color)
{
	color.red = get_minzero_maxone_number(color.red);
	color.green = get_minzero_maxone_number(color.green);
	color.blue = get_minzero_maxone_number(color.blue);
	return (color);
}

t_color	tcolor_init(double r, double g, double b)
{
	t_color	new;

	new.red = get_minzero_maxone_number(r);
	new.green = get_minzero_maxone_number(g);
	new.blue = get_minzero_maxone_number(b);
	return (new);
}

t_color	tcolor_add(t_color a, t_color b)
{
	t_color new;

	new.red = get_minzero_maxone_number(a.red + b.red);
	new.green = get_minzero_maxone_number(a.green + b.green);
	new.blue = get_minzero_maxone_number(a.blue + b.blue);
	return (new);
}

t_color	tcolor_multiply(t_color a, t_color b)
{
	t_color	new;

	new.red = get_minzero_maxone_number(a.red * b.red);
	new.green = get_minzero_maxone_number(a.green * b.green);
	new.blue = get_minzero_maxone_number(a.blue * b.blue);
	return (new);
}

t_color	tcolor_scalar_multiply(t_color a, double scalar)
{
	t_color	new;

	new.red = get_minzero_maxone_number(a.red * scalar);
	new.green = get_minzero_maxone_number(a.green * scalar);
	new.blue = get_minzero_maxone_number(a.blue * scalar);
	return (new);
}
