/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_sphere.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:29:26 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 08:39:13 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SPHERE_H
#define T_SPHERE_H

# include "t_vec3.h"
# include "t_color.h"
# include "t_ray.h"
# include "t_intersect.h"

typedef struct s_sphere
{
	t_vec3_pos	center;
	double		r;
	t_color		color;
}	t_sphere;

int	get_distance_to_sphere(t_sphere const *sphere, t_ray const *ray, t_intersect *out_intersect);

#endif
