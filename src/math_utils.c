/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:04:33 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/10 20:11:27 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

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
