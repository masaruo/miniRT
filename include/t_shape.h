/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shape.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:39:35 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/16 14:38:00 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SHAPE_H
#define T_SHAPE_H
#include "t_vec3.h"
#include "t_color.h"

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

typedef enum
{
	e_sphere,
	e_plane,
}	e_shape_type;

typedef struct s_shape
{
	e_shape_type	type;
	union
	{
		t_plane		plane;
		t_sphere	sphere;
	}	u_data;
	t_material	material;
	t_color		color;
}	t_shape;


// t_sphere t_sphere_init(t_vec3 const *center, double in_r);

#endif