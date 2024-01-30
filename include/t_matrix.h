/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_matrix.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:30:03 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/30 13:47:19 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MATRIX_H
#define T_MATRIX_H

#include "t_vec3.h"

typedef struct s_mat
{
	double	elem[4][4];
}	t_mat;

t_vec3	matrix_multiplication(t_vec3 const *src, double const **m);
t_mat	t_mat_lookat(t_vec3 const *from, t_vec3 const *to, t_vec3 const *up);//!頂上と真下のハンドル
double	**camera_to_world_matrix(t_vec3 const *from, t_vec3 const *to, t_vec3 const *up);
t_vec3	matrix_dir_multiplication(t_vec3 const *src, double const **m);
t_vec3	matrix_multiplication(t_vec3 const *src, double const **m);

#endif