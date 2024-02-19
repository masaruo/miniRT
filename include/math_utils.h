/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:05:28 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 09:34:59 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

double	d_min(double a, double b);
double	d_max(double a, double b);
double	d_clamp(double num, double min, double max);
double	convert_degree_to_radian(double degree);

#endif
