/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_light.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:02:06 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 07:35:53 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LIGHT_H
# define T_LIGHT_H

# include "t_color.h"
# include "t_vec3.h"

typedef struct s_light
{
	t_vec3_pos	vector;
	t_color		color;
	double		brightness;
}	t_light;

#endif
