/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:22:03 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 12:29:10 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_color.h"
#include <math.h>
#include "math_utils.h"
#include "libft.h"
#include "wrapper.h"

t_color	tcolor_clamp(t_color color)
{
	t_color	new;

	new.red = d_clamp(color.red, 0, 1);
	new.green = d_clamp(color.green, 0, 1);
	new.blue = d_clamp(color.blue, 0, 1);
	return (new);
}

t_color	tcolor_add(t_color a, t_color b)
{
	t_color	new;

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

t_color	tcolor_str_init(char const *line)
{
	t_color	color;
	char	**rgb;
	char	*r;
	char	*g;
	char	*b;

	rgb = ft_xsplit(line, ',', 3);
	if (!rgb)
	{
		ft_perror_exit(EXIT_FAILURE, "tcolor_str_set failed.");
	}
	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	color = tcolor_rgb_init(\
		ft_ranged_xatod(r, 0, 255), \
		ft_ranged_xatod(g, 0, 255), \
		ft_ranged_xatod(b, 0, 255));
	ft_free_all(rgb);
	return (color);
}
