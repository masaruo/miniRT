/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:03:25 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/20 13:28:51 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CAMERA_H
#define T_CAMERA_H

#include "t_vec3.h"

typedef struct s_camera
{
	t_vec3_pos	position;
	t_vec3_unit	orientation;
	double		field_of_view;
	t_vec3_unit	x_basis;
	t_vec3_unit	y_basis;
}	t_camera;

t_vec3_unit get_world_ray_direction(double x, double y, t_vec3_pos s, t_vec3_unit d, double width, double fov);

#endif
