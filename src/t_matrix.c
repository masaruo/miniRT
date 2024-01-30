/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_matrix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:30:08 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/29 14:55:25 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_matrix.h"

// t_mat	t_mat_lookat(t_vec3 const *from, t_vec3 const *to, t_vec3 const *up)
// {
// 	t_mat			m;
// 	t_vec3 const	forward = vec3_normalized_subtract(from, to);
// 	t_vec3 const	right = vec3_cross(up, &forward);
// 	t_vec3 const	new_up = vec3_cross(&forward, &right);

// 	m.elem[0][0] = right.x, m.elem[0][1] = right.y, m.elem[0][2] = right.z;
// 	m.elem[1][0] = new_up.x, m.elem[1][1] = new_up.y, m.elem[1][2] = new_up.z;
// 	m.elem[2][0] = forward.x, m.elem[2][1] = forward.y, m.elem[2][2] = forward.z;
// 	m.elem[3][0] = from->x, m.elem[3][1] = from->y, m.elem[3][2] = from->z;
// 	return (m);
// }

double	**camera_to_world_matrix(t_vec3 const *from, t_vec3 const *to, t_vec3 const *up)
{
	double	m[4][4];
	t_vec3 const	forward = vec3_normalized_subtract(from, to);
	t_vec3 const	right = vec3_cross(up, &forward);
	t_vec3 const	new_up = vec3_cross(&forward, &right);

	m[0][0] = right.x;
	m[0][1] = right.y;
	m[0][2] = right.z;
	m[1][0] = new_up.x;
	m[1][1] = new_up.y;
	m[1][2] = new_up.z;
	m[2][0] = forward.x;
	m[2][1] = forward.y;
	m[2][2] = forward.z;
	m[3][0] = from->x;
	m[3][1] = from->y;
	m[3][2] = from->z;
	return (m);
}

t_vec3	matrix_dir_multiplication(t_vec3 const *src, double const **m)
{
	t_vec3	dst;

	dst.x = src->x * m[0][0] + src->y * m[1][0] + src->z * m[2][0] + m[3][0];
	dst.y = src->x * m[0][1] + src->y * m[1][1] + src->z * m[2][1] + m[3][1];
	dst.z = src->x * m[0][2] + src->y * m[1][2] + src->z * m[2][2] + m[3][2];
	return (dst);
}

t_vec3	matrix_multiplication(t_vec3 const *src, double const **m)
{
	t_vec3	dst;
	double	w;

	dst = matrix_dir_multiplication(src, m);
	w = src->x * m[0][3] + src->y * m[1][3] + src->z * m[2][3] + m[3][3];
	if (w != 1 && w != 0)
	{
		dst.x /= w;
		dst.y /= w;
		dst.z /= w;
	}
	return (dst);
}

// t_vec3	t_matrix_multiplication(t_vec3 const *src, t_matrix const *m)
// {
// 	t_vec3	dst;
// 	double	w;

// 	dst.x = src->x * m[0][0] + src->y * m[1][0] + src->z * m[2][0] + m[3][0];
// 	dst.y = src->x * m[0][1] + src->y * m[1][1] + src->z * m[2][1] + m[3][1];
// 	dst.z = src->x * m[0][2] + src->y * m[1][2] + src->z * m[2][2] + m[3][2];
// 	w = src->x * m->matrix[0][3] + src->y * m->matrix[1][3] + src->z * m->matrix[2][3] + m->matrix[3][3];
// }