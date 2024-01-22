/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:17:28 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/21 15:07:17 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phong.h"
#include "math_utils.h"
#include <math.h>

static t_color	_get_ambient_effect(t_shape const *nearest)
{
	t_color	const	ambient = nearest->material.ambient;
	t_color			ans;
	t_color			temp_brightness = tcolor_set(0.5, 0.5, 0.5);

	ans = tcolor_set(0, 0, 0);
	ans = tcolor_multiply(ambient, temp_brightness);
	return (ans);
}

static t_color	_get_diffuse_effect(t_shape const *nearest, t_list const *lights, t_intersect const *intersect)
{
	t_color	const diffuse = nearest->material.diffuse;
	t_list	*crnt;
	t_light	*light;
	t_vec3	l;
	double	n_dot_l;
	t_color	tmp;
	t_color ans;

	ans = tcolor_set(0, 0, 0);
	crnt = lights->next;
	while (crnt)
	{
		light = crnt->content;
		l = vec3_normalized_subtract(&light->vector, &intersect->position);
		n_dot_l = vec3_dot(&intersect->normal, &l);
		if (n_dot_l > 0)
		{
			n_dot_l = double_clamp(n_dot_l, 0, 1);//!ここわかってない！
			tmp = tcolor_scalar_multiply(diffuse, n_dot_l);
			tmp = tcolor_multiply(tmp, light->brightness);
			ans = tcolor_add(tmp, ans);
		}
		crnt = crnt->next;
	}
	return (ans);
}

static t_color	_get_specular_effect(t_shape const *nearest, t_list const *lights, t_intersect const *intersect, t_ray const *eye)
{
	t_color			specular;
	double const	alpha = nearest->material.shininess;
	t_list			*crnt;
	t_light			*light;
	t_vec3			l;
	t_vec3			r;
	t_vec3			v;
	double			n_dot_l;
	double			v_dot_r;
	t_color			ans;
	t_color			tmp;

	ans = tcolor_set(0, 0, 0);
	specular = nearest->material.specular;
	crnt = lights->next;
	while (crnt)
	{
		light = crnt->content;
		l = vec3_normalized_subtract(&light->vector, &intersect->position);
		n_dot_l = vec3_dot(&intersect->normal, &l);
		if (n_dot_l > 0)
		{
			n_dot_l = double_clamp(n_dot_l, 0, 1);
			r = vec3_multiply(&intersect->normal, 2 * n_dot_l);
			r = vec3_subtract(&r, &l);
			v = vec3_multiply(&eye->direction, -1);
			v_dot_r = vec3_dot(&v, &r);
			if (v_dot_r > 0)
			{
				tmp = tcolor_scalar_multiply(specular, pow(v_dot_r, alpha));
				tmp = tcolor_multiply(tmp, light->brightness);
				ans = tcolor_add(tmp, ans);
			}
		}
		crnt = crnt->next;
	}
	return (ans);
}

t_color	tcolor_calc_phong(t_shape const *nearest, t_list const *light, t_intersect const *intersect, t_ray const *eye)
{
	t_color			phong;

	phong = tcolor_set(0, 0, 0);
	phong = tcolor_add(phong, _get_ambient_effect(nearest));
	phong = tcolor_add(phong, _get_diffuse_effect(nearest, light, intersect));
	phong = tcolor_add(phong, _get_specular_effect(nearest, light, intersect, eye));
	return (phong);
}
