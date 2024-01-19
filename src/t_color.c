/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:22:03 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/19 16:58:38 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "math_utils.h"
#include "t_color.h"

static t_color	tcolor_clamp(t_color color)
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

int	tcolor_convert_strcolor(t_color *color, char *rgbstr)
{
	return 0;
}

t_color	tcolor_convert_rgbcolor(double r, double g, double b)
{
	t_color	new;

	new.red = r / 255;
	new.green = g / 255;
	new.blue = b / 255;
	return (tcolor_clamp(new));
}

//! phong effect calculation

static t_color	_get_ambient_effect(t_shape const *nearest)
{
	return (nearest->material.ambient);
}

static t_color	_get_diffuse_effect(t_shape const *nearest, double n_dot_l)
{
	if (n_dot_l < 0)
	{
		return (tcolor_scalar_multiply(nearest->material.diffuse, 0));
	}
	else
	{
		return (tcolor_scalar_multiply(nearest->material.diffuse, n_dot_l));
	}
}

static t_color	_get_specular_effect(t_shape const *nearest, double v_dot_r)
{
	t_color	const	specular = nearest->material.specular;
	double const	alpha = nearest->material.shininess;
	
	if (v_dot_r < 0)
	{
		return (tcolor_scalar_multiply(specular, 0));
	}
	else
	{
		return (tcolor_scalar_multiply(specular, pow(v_dot_r, alpha)));
	}
}

t_color	tcolor_calc_phong(t_shape const *nearest, t_intersect const *intersect, t_light const *light, t_ray const *eye)
{
	t_color			phong;
	t_vec3 const	l = vec3_normalized_subtract(&light->vector, &intersect->position);
	double const	n_dot_l = vec3_dot(&intersect->normal, &l);
	t_vec3	const	v = vec3_multiply(&eye->direction, -1);
	t_vec3			r;
	double			v_dot_r;


	r = vec3_multiply(&intersect->normal, 2 * n_dot_l);
	r = vec3_subtract(&r, &l);
	v_dot_r = vec3_dot(&v, &r);

	phong = tcolor_set(0, 0, 0);
	phong = tcolor_add(phong, _get_ambient_effect(nearest));
	phong = tcolor_add(phong, _get_diffuse_effect(nearest, n_dot_l));
	phong = tcolor_add(phong, _get_specular_effect(nearest, v_dot_r));
	return (phong);
}
