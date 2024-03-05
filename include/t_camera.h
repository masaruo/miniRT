/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:03:25 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 07:33:40 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CAMERA_H
# define T_CAMERA_H

# include "t_vec3.h"
# include "t_ray.h"

typedef struct s_camera
{
	t_vec3_pos	position;
	t_vec3_unit	orientation;
	double		field_of_view;
}	t_camera;

t_ray	get_camera_ray(t_camera camera, double in_x, double in_y, double width);

#endif
