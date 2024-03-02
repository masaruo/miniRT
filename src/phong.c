/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:17:28 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 15:18:38 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phong.h"
#include "math_utils.h"
#include <math.h>
#include "shadow.h"

static double	calc_lambertian_effect(\
	t_light const *light, t_intersect const *intersect)
{
	t_vec3_unit const	to_light = \
		vec3_normalized_subtract(light->vector, intersect->position);
	double const		lambertian_reflect = \
		vec3_dot(to_light, intersect->normal);

	return (lambertian_reflect);
}

static t_color	_get_diffuse_effect(\
	t_light const *light, t_intersect const *intersect, double lambert)
{
	t_color				diffuse;

	diffuse = tcolor_init(0, 0, 0);
	d_clamp(lambert, 0, 1);
	diffuse = tcolor_scalar_multiply(light->color, light->brightness);
	diffuse = tcolor_multiply(intersect->color, diffuse);
	diffuse = tcolor_scalar_multiply(diffuse, lambert);
	diffuse = tcolor_scalar_multiply(diffuse, 0.69);
	return (diffuse);
}

static t_color	_get_specular_effect(\
	t_light const *light, t_intersect const *intersect, \
	t_ray const *eye, double lambert)
{
	t_vec3_unit const	to_eye = vec3_multiply(eye->direction, -1);
	t_vec3_unit const	to_light = \
		vec3_normalized_subtract(light->vector, intersect->position);
	t_vec3_unit			reflect;
	double				v_dot_r;
	t_color				specular;

	specular = tcolor_init(0, 0, 0);
	reflect = vec3_multiply(\
		intersect->normal, 2 * vec3_dot(intersect->normal, to_light));
	reflect = vec3_subtract(reflect, to_light);
	v_dot_r = vec3_dot(to_eye, reflect);
	if (v_dot_r > 0)
	{
		specular = tcolor_scalar_multiply(light->color, light->brightness);
		specular = tcolor_multiply(specular, intersect->color);
		specular = tcolor_scalar_multiply(specular, pow(v_dot_r, 0.8));
		specular = tcolor_scalar_multiply(specular, 0.2);
	}
	return (specular);
}

static t_color	_calc_diffuse_and_specular(\
	t_list const *lights, t_intersect const *intersect, \
	t_ray const *ray, t_list const *const shapes)
{
	t_color	specular;
	t_color	total_effect;
	t_list	*crnt;
	t_light	*light;
	double	lambert;

	total_effect = tcolor_init(0, 0, 0);
	crnt = lights->next;
	while (crnt)
	{
		light = crnt->content;
		lambert = calc_lambertian_effect(light, intersect);
		if (lambert > 0 && test_shadow_intersection(shapes, light, intersect) \
			== NO_INTERSECTION)
		{
			total_effect = _get_diffuse_effect(light, intersect, lambert);
			specular = _get_specular_effect(light, intersect, ray, lambert);
			total_effect = tcolor_add(total_effect, specular);
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
	_calc_diffuse_and_specular(world->lights, intersect, ray, world->shapes);
	phong = tcolor_add(phong, diffuse_and_specular);
	return (phong);
}
