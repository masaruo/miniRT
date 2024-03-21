/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:07:29 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/21 15:05:06 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include "math.h"
#include "libft.h"
#include "wrapper.h"

double	vec3_length(t_vec3 a)
{
	return (sqrt(vec3_square(a)));
}

t_vec3	vec3_default_ranged_str_init(char const *line)
{
	t_vec3	vec;

	vec = vec3_ranged_str_init(line, -100.0, 100.0);
	return (vec);
}

t_vec3	vec3_ranged_str_init(char const *line, double min, double max)
{
	t_vec3	vec;
	char	**xyz;
	char	*x;
	char	*y;
	char	*z;

	xyz = ft_xsplit(line, ',', 3);
	if (!xyz)
	{
		ft_perror_exit(EXIT_FAILURE, "vec3_str_init failed.");
	}
	x = xyz[0];
	y = xyz[1];
	z = xyz[2];
	vec = vec3_init(ft_ranged_xatod(x, min, max), \
					ft_ranged_xatod(y, min, max), \
					ft_ranged_xatod(z, min, max));
	ft_free_all(xyz);
	return (vec);
}
