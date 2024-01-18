/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shape.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:39:35 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/18 10:37:54 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SHAPE_H
#define T_SHAPE_H
#include "t_vec3.h"
#include "t_color.h"
#include "t_intersect.h"
#include "t_ray.h"

#define NO_INTERSECTION (0)
#define HAS_INTERSECTION (1)

// マテリアル構造体
typedef struct s_material
{
	double	ambient;
	double	diffuse;
	double	specular;
	t_color	color;
}	t_material;

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
	sphere,
	plane,
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
	t_color			color;
}	t_shape;

int	test_intersection(t_shape const *this, t_ray const *ray, t_intersect *out_intersect);

#endif