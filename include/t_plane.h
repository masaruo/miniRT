/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_plane.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:47:38 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 13:04:48 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PLANE_H
#define T_PLANE_H

# include "t_vec3.h"
# include "t_color.h"
# include "t_intersect.h"
# include "t_ray.h"

typedef struct s_plane
{
	t_vec3_pos	position;
	t_vec3_unit	normal;
	t_color		color;
}	t_plane;

int	get_distance_to_plane(t_plane const *plane, t_ray const *ray, t_intersect *out_intersect);

#endif
