/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:17:28 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/19 22:22:08 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phong.h"
#include <math.h>

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
