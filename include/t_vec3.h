/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:59:21 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/12 14:16:27 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_VEC3_H
#define T_VEC3_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	vec3_init(double in_x, double in_y, double in_z);

t_vec3	vec3_add(t_vec3 const *a, t_vec3 const *b);
t_vec3	vec3_subtract(t_vec3 const *a, t_vec3 const *b);
t_vec3	vec3_multiply(t_vec3 const *a, double scalar);

double	vec3_dot(t_vec3 const *a, t_vec3 const *b);
t_vec3	vec3_cross(t_vec3 const *a, t_vec3 const *b);
double	vec3_lengthSq(t_vec3 const *a);
double	vec3_length(t_vec3 const *a);
t_vec3	vec3_normalize(t_vec3 const *a);
void	vec3_print(t_vec3 const *a);
t_vec3	vec3_copy(t_vec3 const *a);

#endif