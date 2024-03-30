/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:58:13 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/30 18:31:36 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include "libft.h"
#include "ft_atod.h"

static int	ft_isaccepted_char(int c)
{
	if (c == '.' || c == '-')
		return (1);
	else if (ft_isdigit(c))
		return (1);
	else
		return (0);
}

double	ft_xatod(char const *const str_num)
{
	size_t	i;
	char	*rf_trimmed;
	double	num;

	rf_trimmed = ft_strtrim(str_num, "\n");
	if (!rf_trimmed)
		ft_perror_exit(EXIT_FAILURE, "ft_strtrim failed.");
	i = 0;
	while (rf_trimmed[i])
	{
		if (!ft_isaccepted_char((int) rf_trimmed[i]))
		{
			ft_perror_exit(EXIT_FAILURE, \
						"ft_xatod: no digit nor dot detected.");
		}
		i++;
	}
	num = ft_atod(rf_trimmed);
	free(rf_trimmed);
	return (num);
}

double	ft_ranged_xatod(char const *const str_num, double min, double max)
{
	double	num;

	num = ft_xatod(str_num);
	if (num < min || max < num)
	{
		ft_perror_exit(EXIT_FAILURE, \
					"ft_ranged_xatod: input is out of the acceptable range.");
	}
	return (num);
}

void	check_num_childs_valid(char **splitted, size_t num_childs)
{
	size_t	i;

	i = 0;
	while (splitted[i])
	{
		i++;
	}
	if (i != num_childs)
	{
		ft_perror_exit(EXIT_FAILURE, \
			"number of inputs to split is not correct.");
	}
}

char	**ft_xsplit(char const *s, char c, size_t num_childs)
{
	char	**splitted;

	splitted = ft_split(s, c);
	check_num_childs_valid(splitted, num_childs);
	return (splitted);
}
