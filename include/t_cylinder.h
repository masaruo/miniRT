/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:18:12 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 08:27:35 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CYLINDER_H
#define T_CYLINDER_H

# include "t_vec3.h"
# include "t_color.h"
# include "t_ray.h"
# include "t_intersect.h"

typedef struct s_cylinder
{
	t_position_vec3		position;
	t_normalized_vec3	normal;
	double				r;
	double				height;
	t_color				color;
}	t_cylinder;

int	get_distance_to_cylinder(t_cylinder const *cylinder, t_ray const *ray, t_intersect *out_intersect);

#endif
