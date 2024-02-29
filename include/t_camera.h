/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:03:25 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 14:09:23 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CAMERA_H
#define T_CAMERA_H

#include "t_vec3.h"
#include "t_ray.h"

typedef struct s_camera
{
	t_vec3_pos	position;
	t_vec3_unit	orientation;
	double		field_of_view;
	// t_vec3_unit	x_basis;
	// t_vec3_unit	y_basis;
}	t_camera;

t_ray	get_camera_ray(t_camera camera, double screen_x, double screen_y, double width);

#endif
