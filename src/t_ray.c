/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:32:22 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/12 13:57:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_ray.h"

t_ray	t_ray_init(t_vec3 const *start, t_vec3 const *xy)
{
	t_ray	new;
	t_vec3 const	start_to_screen = vec3_subtract(xy, start);

	new.start = *start;
	new.direction = vec3_normalize(&start_to_screen);
	return (new);
}

void	t_ray_constructor(struct s_ray *self, t_vec3 const *start, t_vec3 const *direction)
{
	self->direction = *direction;
	self->start = *start;
	return ;
}
