/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:03:25 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/01 16:19:48 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CAMERA_H
#define T_CAMERA_H

#include "t_vec3.h"
#include "t_image.h"

typedef struct s_camera
{
	t_position_vec3		position;
	t_vector_vec3		orientation;
	double				field_of_view;
	t_normalized_vec3	x_basis;
	t_normalized_vec3	y_basis;
	t_normalized_vec3	direction;
}	t_camera;

#endif