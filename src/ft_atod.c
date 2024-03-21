/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:04:13 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/20 10:21:18 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#define BASE10 (10)
#define ONE_AFTER_DOT (1)

static size_t	_cnt_digits(char const *const dot_location)
{
	char const *const	start_of_decimal = dot_location + ONE_AFTER_DOT;
	size_t				i;
	size_t				cnt;

	i = 0;
	cnt = 0;
	while (start_of_decimal[i])
	{
		if (ft_isdigit(start_of_decimal[i]))
		{
			cnt++;
		}
		i++;
	}
	return (cnt);
}

static double	_get_decimal_part(char const *const str_num)
{
	char const *const	dot_location = ft_strchr(str_num, '.');
	double				decimal;
	size_t				how_many_digits;
	char				*decimal_in_str;
	long				decimal_in_long;

	decimal = 0;
	if (dot_location == NULL)
		return (decimal);
	how_many_digits = _cnt_digits(dot_location);
	decimal_in_str = ft_substr(dot_location, ONE_AFTER_DOT, how_many_digits);
	decimal_in_long = ft_strtol(decimal_in_str, NULL, BASE10);
	decimal += (double)(decimal_in_long / pow(BASE10, how_many_digits));
	free(decimal_in_str);
	return (decimal);
}

double	ft_atod(char const *const str_num)
{
	double			double_num;
	double const	int_part = ft_strtol(str_num, NULL, BASE10);
	double const	decimal_part = _get_decimal_part(str_num);

	double_num = 0;
	double_num += int_part;
	double_num += decimal_part;
	return (double_num);
}
