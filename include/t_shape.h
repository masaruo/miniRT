/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shape.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:39:35 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/23 11:30:56 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SHAPE_H
#define T_SHAPE_H

#include "t_color.h"
#include "t_vec3.h"
#include "t_intersect.h"
#include "t_ray.h"
#include "t_material.h"
#include "t_light.h"

#define NO_INTERSECTION (0)
#define HAS_INTERSECTION (1)

typedef struct s_sphere
{
	t_vec3	center;
	double	r;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	position;
	t_vec3	normal;
}	t_plane;

typedef enum t_shape_type
{
	sphere_type,
	plane_type,
}	t_shape_type;

typedef struct s_shape
{
	t_shape_type	type;
	union
	{
		t_plane		plane;
		t_sphere	sphere;
	}	u_data;
	t_material		material;
	// t_color			color;
}	t_shape;

int		test_intersection(t_shape const *shape, t_ray const *ray, t_intersect *out_intersect);
#include "libft.h"
int	test_all_intersection(t_list const * const shapes, t_ray const *ray, t_intersect *out_intersect);
int	test_shadow_intersection(t_list const * const shapes, t_light const *light, t_intersect const *intersect);

#endif