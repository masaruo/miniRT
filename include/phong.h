/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:17:12 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/01 16:03:04 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONG_H
#define PHONG_H

#include "t_shape.h"
#include "t_color.h"
#include "t_intersect.h"
#include "t_ray.h"
#include "t_light.h"
#include "t_world.h"

t_color	tcolor_calc_phong(t_world const * const world, t_intersect const *intersect, t_ray const *eye);

#endif