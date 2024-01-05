/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:07:29 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/05 15:28:57 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vec3_init(double in_x, double in_y, double in_z)
{
	t_vec3	vec;

	vec.x = in_x;
	vec.y = in_y;
	vec.z = in_z;
	return (vec);
}
