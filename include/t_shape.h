/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shape.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:39:35 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 07:37:24 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SHAPE_H
# define T_SHAPE_H

# include "t_color.h"
# include "t_vec3.h"
# include "t_intersect.h"
# include "t_ray.h"
# include "t_light.h"
# include "t_cylinder.h"
# include "t_sphere.h"
# include "t_plane.h"

# define NO_INTERSECTION (0)
# define HAS_INTERSECTION (1)

typedef enum e_shape_type
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
	}	u_obj;
}	t_shape;

#endif
