/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:17:28 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 12:53:38 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phong.h"
#include "math_utils.h"
#include <math.h>
#include "shadow.h"

static t_color	_get_diffuse_effect(\
	t_light const *light, t_intersect const *intersect)
{
	t_vec3_unit const	to_light = \
		vec3_normalized_subtract(light->vector, intersect->position);
	double const		n_dot_l = vec3_dot(to_light, intersect->normal);
	t_color				diffuse;

		diffuse = tcolor_init(0, 0, 0);
	if (n_dot_l > 0)
	{
		diffuse = tcolor_scalar_multiply(light->color, light->brightness);
		diffuse = tcolor_multiply(intersect->color, diffuse);
		diffuse = tcolor_scalar_multiply(diffuse, n_dot_l);
	}
	return (diffuse);
}

static t_color	_get_specular_effect(\
	t_light const *light, t_intersect const *intersect, t_ray const *eye)
{
	t_vec3			l;
	t_vec3			r;
	t_vec3			v;
	double			n_dot_l;
	double			v_dot_r;
	t_color			ans;
	t_color			tmp;

	ans = tcolor_init(0, 0, 0);
	l = vec3_normalized_subtract(light->vector, intersect->position);
	n_dot_l = vec3_dot(intersect->normal, l);
	if (n_dot_l > 0)
	{
		n_dot_l = d_clamp(n_dot_l, 0, 1);
		r = vec3_multiply(intersect->normal, 2 * n_dot_l);
		r = vec3_subtract(r, l);
		v = vec3_multiply(eye->direction, -1);
		v_dot_r = vec3_dot(v, r);
		if (v_dot_r > 0)
		{
			tmp = tcolor_scalar_multiply(light->color, light->brightness);
			// tmp = tcolor_multiply(intersect->material.color, tmp);//changed
			tmp = tcolor_multiply(intersect->color, tmp);
			tmp = tcolor_scalar_multiply(tmp, pow(v_dot_r, 0.8));//changed from alpha
			tmp = tcolor_clamp(tmp);//???　必要？
			ans = tmp;
		}
	}
	return (ans);
}

static t_color	_calc_diffse_and_specular(\
	t_list const *lights, t_intersect const *intersect, \
	t_ray const *ray, t_list const *const shapes)
{
	t_color	diffuse;
	t_color	specular;
	t_color	total_effect;
	t_list	*crnt;
	t_light	*light;

	total_effect = tcolor_init(0, 0, 0);
	crnt = lights->next;
	while (crnt)
	{
		light = crnt->content;
		if (test_shadow_intersection(shapes, light, intersect) \
			== NO_INTERSECTION)
		{
			total_effect = _get_diffuse_effect(light, intersect);
			// specular = _get_specular_effect(light, intersect, ray);
			// total_effect = tcolor_add(total_effect, specular);
		}
		crnt = crnt->next;
	}
	return (total_effect);
}

t_color	tcolor_calc_phong(\
	t_world const *const world, t_intersect const *intersect, t_ray const *ray)
{
	t_color			phong;
	t_color const	ambient = \
		tcolor_scalar_multiply(world->ambient.color, world->ambient.ratio);
	t_color			diffuse_and_specular;

	phong = ambient;
	diffuse_and_specular = \
		_calc_diffse_and_specular(world->lights, intersect, ray, world->shapes);
	phong = tcolor_add(phong, diffuse_and_specular);
	return (phong);
}
