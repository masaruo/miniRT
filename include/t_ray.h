/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:57:18 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 07:36:58 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAY_H
# define T_RAY_H

# include "t_vec3.h"

typedef struct s_ray
{
	t_vec3_pos	start;
	t_vec3_unit	direction;
	double		light_distance;
}	t_ray;

t_ray	t_ray_create_ray(t_vec3 const *start, t_vec3 const *end);
t_vec3	t_ray_get_point(t_ray const *this, double distance);
t_vec3	t_ray_screen_to_world(t_vec3 const *camera_pos, \
								double screen_width, double fov);

#endif
