/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:58:13 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 21:17:34 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include "libft.h"
#include "ft_atod.h"

void	ft_perror_exit(int status, char const *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(status);
}

static int	ft_isdot(int c)
{
	if (c == '.')
		return (1);
	else
		return (0);
}

double	ft_xatod(char const * const str_num)
{
	size_t	i;

	i = 0;
	while (str_num[i])
	{
		if (!ft_isdigit(str_num[i]) || !ft_isdot(str_num[i]))
		{
			ft_perror_exit(EXIT_FAILURE, "no digit nor dot is not allowed.");
		}
		i++;
	}
	return (ft_atod(str_num));
}

double	ft_ranged_xatod(char const * const str_num, size_t min, size_t max)
{
	double	num;

	num = ft_xatod(str_num);
	if (num < min || max < num)
	{
		ft_perror_exit(EXIT_FAILURE, "number is out of the accepted range.");
	}
	else
		return (num);
}

char** ft_xsplit(char const *s, char c, size_t num_childs)
{
	size_t	i;
	char	**splitted;

	i = 0;
	splitted = ft_split(s, c);
	while (splitted[i])
	{
		i++;
	}
	if (i < num_childs)
	{
		ft_perror_exit(EXIT_FAILURE, "number of inputs is not correct.");
	}
	else
		return (splitted);
}
