/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:19:09 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/05 08:58:37 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "validation.h"
#include "t_color.h"
#include "wrapper.h"

t_light	*_get_a_light(char **lines)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	if (light == NULL)
	{
		ft_perror_exit(EXIT_FAILURE, "ft_calloc failed.");
	}
	light->vector = vec3_defalt_ranged_str_init(lines[1]);
	light->brightness = ft_ranged_xatod(lines[2], 0.0, 1.0);
	light->color = tcolor_str_init(lines[3]);
	return (light);
}

t_shape	*_get_a_sphere(char **lines)
{
	t_shape	*sphere;

	sphere = ft_calloc(1, sizeof(t_shape));
	if (sphere == NULL)
		ft_perror_exit(EXIT_FAILURE, "ft_calloc failed.");
	sphere->type = sphere_type;
	sphere->u_obj.sphere.center = vec3_defalt_ranged_str_init(lines[1]);
	sphere->u_obj.sphere.r = ft_ranged_xatod(lines[2], 0.1, 100) / 2.0;
	sphere->u_obj.sphere.color = tcolor_str_init(lines[3]);
	return (sphere);
}

t_shape	*_get_a_plain(char **lines)
{
	t_shape	*plane;

	plane = ft_calloc(1, sizeof(t_shape));
	if (plane == NULL)
		ft_perror_exit(EXIT_FAILURE, "ft_calloc failed.");
	plane->type = plane_type;
	plane->u_obj.plane.position = vec3_defalt_ranged_str_init(lines[1]);
	plane->u_obj.plane.normal = \
		vec3_normalize(vec3_ranged_str_init(lines[2], -1.0, 1.0));
	plane->u_obj.plane.color = tcolor_str_init(lines[3]);
	return (plane);
}

t_shape	*_get_a_cylinder(char **lines)
{
	t_shape	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_shape));
	if (cylinder == NULL)
		ft_perror_exit(EXIT_FAILURE, "ft_calloc failed");
	cylinder->type = cylinder_type;
	cylinder->u_obj.cylinder.position = vec3_defalt_ranged_str_init(lines[1]);
	cylinder->u_obj.cylinder.normal = \
		vec3_normalize(vec3_ranged_str_init(lines[2], -1.0, 1.0));
	cylinder->u_obj.cylinder.r = ft_ranged_xatod(lines[3], 0.1, 100.0) / 2.0;
	cylinder->u_obj.cylinder.height = ft_ranged_xatod(lines[4], 0.1, 100.0);
	cylinder->u_obj.cylinder.color = tcolor_str_init(lines[5]);
	return (cylinder);
}
