/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:38:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 12:28:21 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COLOR_H
# define T_COLOR_H

# include <stdint.h>

typedef struct s_color
{
	double	red;
	double	green;
	double	blue;
}	t_color;

uint32_t	tcolor_to_hex(t_color color);
t_color		tcolor_init(double red, double green, double blue);
t_color		tcolor_add(t_color a, t_color b);
t_color		tcolor_multiply(t_color a, t_color b);
t_color		tcolor_scalar_multiply(t_color a, double scalar);
t_color		tcolor_clamp(t_color color);
t_color		tcolor_rgb_init(double red, double green, double blue);
t_color		tcolor_str_init(char const *line);

#endif
