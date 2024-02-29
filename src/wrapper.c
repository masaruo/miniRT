/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:58:13 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 11:06:57 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include "libft.h"
#include "ft_atod.h"

// decided not to include destructor() to clean up as it is exit.
#ifdef LEAK
# include <stdlib.h>

void	ft_perror_exit(int status, char const *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(status);
	system("leaks -q miniRT");
}
#else

void	ft_perror_exit(int status, char const *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(status);
}
#endif

static int	ft_isaccepted_char(int c)
{
	if (c == '.' || c == '\n' || c == '-')
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
		if (!ft_isdigit(str_num[i]) && !ft_isaccepted_char(str_num[i]))
		{
			ft_perror_exit(EXIT_FAILURE, "ft_xatod: no digit nor dot detected.");
		}
		i++;
	}
	return (ft_atod(str_num));
}

double	ft_ranged_xatod(char const * const str_num, int min, int max)
{
	double	num;

	num = ft_xatod(str_num);
	if (num < min || max < num)
	{
		ft_perror_exit(EXIT_FAILURE, "ft_ranged_xatod: input is out of the acceptable range.");
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
		ft_perror_exit(EXIT_FAILURE, "ft_xsplit: number of inputs to split is not correct.");
	}
	else
		return (splitted);
}
