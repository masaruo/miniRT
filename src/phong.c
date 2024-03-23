/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:17:28 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/23 12:17:52 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phong.h"
#include "math_utils.h"
#include <math.h>
#include "shadow.h"

double	calc_lambertian_effect(\
	t_light const *light, t_intersect const *intersect)
{
	t_vec3_unit const	to_light = \
		vec3_normalized_subtract(light->vector, intersect->position);
	double const		lambertian_reflect = \
		vec3_dot(to_light, intersect->normal);

	return (lambertian_reflect);
}

t_color	_get_diffuse_effect(\
	t_light const *light, t_intersect const *intersect, double lambert)
{
	t_color				diffuse;

	diffuse = tcolor_init(0, 0, 0);
	d_clamp(lambert, 0, 1);
	diffuse = tcolor_scalar_multiply(light->color, light->brightness);
	diffuse = tcolor_multiply(intersect->color, diffuse);
	diffuse = tcolor_scalar_multiply(diffuse, lambert);
	diffuse = tcolor_scalar_multiply(diffuse, 0.6);
	return (diffuse);
}

t_color	tcolor_calc_phong(\
	t_world const *const world, t_intersect const *intersect, t_ray const *ray)
{
	t_color			phong;
	t_color const	ambient = \
	tcolor_scalar_multiply(world->ambient.color, world->ambient.ratio * 0.3);
	t_color			diffuse_and_specular;

	phong = ambient;
	diffuse_and_specular = \
	get_phong_effect(world->lights, intersect, ray, world->shapes);
	phong = tcolor_add(phong, diffuse_and_specular);
	return (phong);
}
