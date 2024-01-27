/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:04:33 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/25 11:33:44 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <math.h>
#include "t_vec3.h"

double	double_clamp(double num, double min, double max)
{
	if (num < min)
		return (min);
	else if (num > max)
		return (max);
	else
		return (num);
}

double	double_min(double a, double b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

double double_max(double a, double b)
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

