/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:56:27 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/13 16:28:37 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "t_shape.h"

static t_ray	get_cylinder_ray(t_cylinder const *cylinder)
{
	t_ray	cy_ray;

	cy_ray.start = cylinder->position;
	cy_ray.direction = cylinder->normal;
	return (cy_ray);
}

static double	get_t_parameter(t_ray const *r1, t_ray const *r2)
{
	t_position_vec3	const		p1 = r1->start;
	t_normalized_vec3	const	d1 = r1->direction;
	t_position_vec3 const		p2 = r2->start;
	t_normalized_vec3 const		d2 = r2->direction;
	double						t;


	t = vec3_dotx((vec3_crossx(vec3_subtractx(p2, p1), d2)), vec3_crossx(d1, d2)) / vec3_dotx(vec3_crossx(d1, d2), vec3_crossx(d1, d2));
	//todo 分母が０の時の０割り算対策
	return (t);
}

int	get_distance_to_cylinder(t_cylinder const *cylinder, t_ray const *ray, t_intersect *out_intersect)
{
	t_ray const		cylinder_ray = get_cylinder_ray(cylinder);
	double const	cylinder_ray_t = get_t_parameter(&cylinder_ray, ray);
	double const	eye_ray_t = get_t_parameter(ray, &cylinder_ray);
	t_position_vec3	cylinder_point = t_ray_get_point(&cylinder_ray, cylinder_ray_t);
	t_position_vec3	eye_ray_point = t_ray_get_point(ray, eye_ray_t);
	t_vector_vec3	p_to_p = vec3_subtractx(cylinder_point, eye_ray_point);
	double			points_distance = vec3_lengthx(p_to_p);

	if (points_distance <= cylinder->r)
	{
		out_intersect->distance = eye_ray_t;
		out_intersect->color = cylinder->color;
		out_intersect->position = eye_ray_point;
		out_intersect->normal = 
	}

}
