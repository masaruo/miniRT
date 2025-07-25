/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:18:12 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/06 14:46:11 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CYLINDER_H
# define T_CYLINDER_H

# include "t_vec3.h"
# include "t_color.h"
# include "t_ray.h"
# include "t_intersect.h"

typedef struct s_cylinder
{
	t_vec3_pos	position;
	t_vec3_unit	normal;
	double		r;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_cylinder_calc
{
	t_cylinder const	*cy;
	t_ray const			*ray;
	double				a;
	double				b;
	double				c;
	double				d;
	double				dist_plus;
	double				dist_minus;
	bool				is_dist_p_valid;
	bool				is_dist_m_valid;
	double				distance;
	bool				is_inside;
}	t_cylinder_calc;

int				get_distance_to_cylinder(t_cylinder const *cylinder, \
					t_ray const *ray, t_intersect *out_intersect);
double			_cylinder_get_a(t_vec3_unit d, t_vec3_unit v);
double			_cylinder_get_b(t_vec3_unit d, t_vec3_unit v, t_vec3_unit c);
double			_cylinder_get_c(t_vec3_unit v, t_vec3_unit c, double r);
t_cylinder_calc	cylinder_data_init(t_cylinder const *cy, t_ray const *ray);
bool			is_distance_valid_(double distance, \
								t_cylinder_calc const *cy_data);
void			get_dist_n_inside(t_cylinder_calc *cy, double distance);

#endif
