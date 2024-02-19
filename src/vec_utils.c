/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:07:29 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 10:17:42 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include "math.h"
#include <stdio.h>
#include "libft.h"

t_vec3	vec3_init(double in_x, double in_y, double in_z)
{
	t_vec3	vec;

	vec.x = in_x;
	vec.y = in_y;
	vec.z = in_z;
	return (vec);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_subtract(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec3_multiply(t_vec3 a, double scalar)
{
	return (vec3_init(a.x * scalar, a.y * scalar, a.z * scalar));
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
}

double	vec3_square(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double	vec3_length(t_vec3 a)
{
	return (sqrt(vec3_square(a)));
}

t_vec3	vec3_normalize(t_vec3 a)
{
	double const	length = vec3_length(a);

	if (length <= 0)
		return (vec3_init(0, 0, 0));//! error handle
	return (vec3_init(a.x / length, a.y / length, a.z / length));
}

void	vec3_print(t_vec3 const *a)
{
	printf("x=[%f], y=[%f], z=[%f]\n", a->x, a->y, a->z);
}

t_vec3	vec3_copy(t_vec3 const *a)
{
	t_vec3	new;

	new.x = a->x;
	new.y = a->y;
	new.z = a->z;
	return (new);
}

t_vec3	vec3_normalized_subtract(t_vec3 a, t_vec3 b)
{
	t_vec3	new;

	new = vec3_subtract(a, b);
	new = vec3_normalize(new);
	return (new);
}

#include <stdlib.h>//! delete
t_vec3	vec3_str_init(char const *line)
{
	t_vec3		vec;
	char const	**lines = ft_split(line, ',');
	char const	*x = lines[0];
	char const	*y = lines[1];
	char const	*z = lines[2];

	// vec = vec3_init(atof(x), atof(y), atof(z));//! atof FORBIDDEN
	vec = vec3_init(ft_atoi(x), ft_atoi(y), ft_atoi(z));
	return (vec);
}
