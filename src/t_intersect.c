/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_intersect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:28:11 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 12:28:21 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_intersect.h"
#include "t_shape.h"
#include "phong.h"
#include "shadow.h"

extern	double const	g_epsilon;

static int	test_intersection_by_shape(\
	t_shape const *shape, t_ray const *ray, t_intersect *out_intersect)
{
	if (shape->type == sphere_type)
	{
		return (get_distance_to_sphere(\
			&shape->u_obj.sphere, ray, out_intersect));
	}
	else if (shape->type == plane_type)
	{
		return (get_distance_to_plane(&shape->u_obj.plane, ray, out_intersect));
	}
	else if (shape->type == cylinder_type)
	{
		return (get_distance_to_cylinder(\
			&shape->u_obj.cylinder, ray, out_intersect));
	}
	else
	{
		return (NO_INTERSECTION);
	}
}

static bool	test_intersection(t_list const *const shapes, \
						t_ray const *ray, t_intersect *out_intersect)
{
	t_list		*crnt;
	t_shape		*shape;
	t_intersect	crnt_intersect;
	bool		has_intersection;

	has_intersection = false;
	crnt = shapes->next;
	while (crnt)
	{
		shape = crnt->content;
		if (test_intersection_by_shape(shape, ray, &crnt_intersect))
		{
			if (crnt_intersect.distance < out_intersect->distance)
			{
				*out_intersect = crnt_intersect;
				has_intersection = true;
			}
		}
		crnt = crnt->next;
	}
	return (has_intersection);
}

int	test_shadow_intersection(t_list const *const shapes, \
						t_light const *light, t_intersect const *intersect)
{
	t_ray		shadow_ray;
	t_list		*crnt;
	t_shape		*shape;
	t_intersect	shadow_intersect;

	shadow_ray = get_shadow_ray(intersect, light);
	crnt = shapes->next;
	while (crnt)
	{
		shape = crnt->content;
		if (test_intersection_by_shape(\
				shape, &shadow_ray, &shadow_intersect) == HAS_INTERSECTION)
		{
			if (shadow_intersect.distance < shadow_ray.light_distance)
				return (HAS_INTERSECTION);
		}
		crnt = crnt->next;
	}
	return (NO_INTERSECTION);
}

t_color	get_color_at_xy_coord(t_world const *world, t_ray const *eye_ray)
{
	t_intersect	intersection_data;
	t_color		paint_color;

	intersection_data.distance = __DBL_MAX__;
	if (test_intersection(world->shapes, eye_ray, &intersection_data) == true)
	{
		paint_color = tcolor_calc_phong(world, &intersection_data, eye_ray);
	}
	else
	{
		paint_color = tcolor_rgb_init(100, 149, 237);
	}
	return (paint_color);
}
