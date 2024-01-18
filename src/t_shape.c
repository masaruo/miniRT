/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:31:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/18 11:07:55 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shape.h"
#include "math.h"
#include "math_utils.h"

// ２時関数tの解を、判別式を用いて計算
static	double	calculate_t_distance(double d, double b, double a)
{
	double			t_distance;
	double			t_plus;
	double			t_minus;

	t_distance = -1;
	if (d >= 0)
	{
		t_plus = (-b + sqrt(d)) / (2 * a);
		t_minus = (-b - sqrt(d)) / (2 * a);
		if (t_plus > 0 && t_minus > 0)
		{
			t_distance = double_min(t_plus, t_minus);
		}
		else if (t_plus > 0 || t_minus > 0)
		{
			if (t_plus > 0)
				t_distance = t_plus;
			else
				t_distance = t_minus;
		}
	}
	return (t_distance);
}

// ２次関数a b cから判定式dを計算。aは正規化されたRayの方向ベクトルなので常に１。
static	double	calculate_sphere_distance(t_sphere const *this, t_ray const *ray)
{
	t_vec3 const	sphere_to_ray = vec3_subtract(&ray->start, &this->center);
	double const	a = vec3_square(&ray->direction);
	double const	b = 2 * vec3_dot(&sphere_to_ray, &ray->direction);
	double const	c = vec3_square(&sphere_to_ray) -  pow(this->r, 2);
	double const	d = (b * b) - (4 * a * c);

	return (calculate_t_distance(d, b, a));
}

static int	test_against_sphere(t_sphere const *this, t_ray const *ray, t_intersect *out_intersect)
{
	double const	distance = calculate_sphere_distance(this, ray);
	t_vec3			center_to_intersect;

	if (distance < 0)
	{
		return (NO_INTERSECTION);
	}
	out_intersect->distance = distance;
	out_intersect->position = t_ray_get_point(ray, distance);
	center_to_intersect = vec3_subtract(&out_intersect->position, &this->center);
	out_intersect->normal = vec3_normalize(&center_to_intersect);
	return (HAS_INTERSECTION);
}

static int	test_against_plane(t_plane const *this, t_ray const *ray, t_intersect *out_intersect)
{
	t_vec3 const	plane_to_camera = vec3_subtract(&ray->start, &this->position);
	double const	numerator = vec3_dot(&plane_to_camera, &this->normal) * -1;
	double const	denominator = vec3_dot(&ray->direction, &this->normal);
	double			distance;

	if (denominator == 0)
		return (NO_INTERSECTION);
	distance = numerator / denominator;
	if (distance < 0)
		return (NO_INTERSECTION);
	out_intersect->distance = distance;
	out_intersect->position = t_ray_get_point(ray, distance);
	out_intersect->normal = this->normal;
	return (HAS_INTERSECTION);
}

int	test_intersection(t_shape const *this, t_ray const *ray, t_intersect *out_intersect)
{
	if (this->type == sphere)
	{
		return (test_against_sphere(this, ray, out_intersect));
	}
	else if (this->type == plane)
	{
		return (test_against_plane(this, ray, out_intersect));
	}
	else
	{
		return (NO_INTERSECTION);
	}
}
