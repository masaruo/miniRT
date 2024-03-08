/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:04:33 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/08 15:18:15 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	d_clamp(double num, double min, double max)
{
	if (num < min)
		return (min);
	else if (num > max)
		return (max);
	else
		return (num);
}

double	d_min(double a, double b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

double	d_max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

// 360 = 2pi, 180 = pi
double	convert_degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}
