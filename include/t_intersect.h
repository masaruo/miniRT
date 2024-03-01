/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_intersect.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:21:56 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 07:57:17 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_INTERSECT_H
# define T_INTERSECT_H

# include "t_vec3.h"
# include "t_color.h"
# include "libft.h"
# include "t_ray.h"
# include "t_light.h"

# define NO_INTERSECTION (0)
# define HAS_INTERSECTION (1)
// # define EPSILON (1.0f / 512)
// double const	g_epsilon = 1.0f / 512.0;
// extern double const	g_epsilon;

typedef struct s_intersect
{
	double		distance;
	t_vec3_pos	position;
	t_vec3_unit	normal;
	t_color		color;
}	t_intersect;

int	test_all_intersection(t_list const *const shapes, \
							t_ray const *ray, t_intersect *out_intersect);
int	test_shadow_intersection(t_list const *const shapes, \
						t_light const *light, t_intersect const *intersect);

#endif
