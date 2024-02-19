/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shape.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:39:35 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 08:57:17 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SHAPE_H
#define T_SHAPE_H

#include "t_color.h"
#include "t_vec3.h"
#include "t_intersect.h"
#include "t_ray.h"
#include "t_light.h"
#include "t_cylinder.h"
#include "t_sphere.h"
#include "t_plane.h"

#define NO_INTERSECTION (0)
#define HAS_INTERSECTION (1)

typedef enum t_shape_type
{
	sphere_type,
	plane_type,
	cylinder_type,
}	t_shape_type;

typedef struct s_shape
{
	t_shape_type	type;
	union
	{
		t_plane		plane;
		t_sphere	sphere;
		t_cylinder	cylinder;
	}	u_data;
}	t_shape;

int		test_intersection(t_shape const *shape, t_ray const *ray, t_intersect *out_intersect);
#include "libft.h"
int	test_all_intersection(t_list const * const shapes, t_ray const *ray, t_intersect *out_intersect);
int	test_shadow_intersection(t_list const * const shapes, t_light const *light, t_intersect const *intersect);

#endif
