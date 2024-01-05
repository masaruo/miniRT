/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:59:21 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/05 16:13:23 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

//initialization of vector3
t_vec3	vec3_init(double in_x, double in_y, double in_z);

//vec_calc.c
double	vec3_dot(t_vec3 const *a, t_vec3 const *b);
t_vec3	vec3_cross(t_vec3 const *a, t_vec3 const *b);
double	vec3_lengthSq(t_vec3 const *a);
double	vec3_length(t_vec3 const *a);
t_vec3	vec3_normalize(t_vec3 const *a);

//vec_math.c
t_vec3	vec3_add(t_vec3 const *a, t_vec3 const *b);
t_vec3	vec3_subtract(t_vec3 const *a, t_vec3 const *b);
t_vec3	vec3_multiply(t_vec3 const *a, double scalar);

#endif