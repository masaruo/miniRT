/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:17:12 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/23 12:28:00 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONG_H
# define PHONG_H

# include "t_intersect.h"
# include "t_ray.h"
# include "t_world.h"

t_color	tcolor_calc_phong(t_world const *const world, \
				t_intersect const *intersect, t_ray const *eye);
double	calc_lambertian_effect(\
	t_light const *light, t_intersect const *intersect);
t_color	get_phong_effect(\
	t_list const *lights, t_intersect const *intersect, \
	t_ray const *ray, t_list const *const shapes);
t_color	_get_diffuse_effect(\
	t_light const *light, t_intersect const *intersect, double lambert);

#endif
