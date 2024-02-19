/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:34:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 13:51:17 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "ft_atod.h"
#include "get_next_line.h"
#include "t_light.h"
#include "t_color.h"
#include "t_shape.h"
#include <fcntl.h>

#define SPACE (' ')
#define FIRST_CHAR (0)

t_ambient _get_ambient_light(char const **lines)
{
	t_ambient	ambient;

	ambient.ratio = ft_atod(lines[1]);
	ambient.color = tcolor_str_set(lines[2]);
	return (ambient);
}

t_light	*_get_a_light(char const **lines)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	if (light == NULL)
	{
		//todo error handle
		exit (1);
	}
	light->vector = vec3_str_init(lines[1]);
	light->brightness = ft_atod(lines[2]);
	light->color = tcolor_str_set(lines[3]);
	return (light);
}

t_shape	*_get_a_sphere(char const **lines)
{
	t_shape	*sphere;

	sphere = ft_calloc(1, sizeof(t_shape));
	//todo malloc error
	sphere->type = sphere_type;
	sphere->u_obj.sphere.center = vec3_str_init(lines[1]);
	sphere->u_obj.sphere.r = ft_atod(lines[2]) / 2.0;
	sphere->u_obj.sphere.color = tcolor_str_set(lines[3]);
	return (sphere);
}

t_shape	*_get_a_plain(char const **lines)
{
	t_shape	*plane;

	plane = ft_calloc(1, sizeof(t_shape));
	//todo malloc error
	plane->type = plane_type;
	plane->u_obj.plane.position = vec3_str_init(lines[1]);
	plane->u_obj.plane.normal = vec3_normalize(vec3_str_init(lines[2]));
	plane->u_obj.plane.color = tcolor_str_set(lines[3]);
	return (plane);
}

t_shape	*_get_a_cylinder(char const **lines)
{
	t_shape	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_shape));
	//todo malloc error
	cylinder->type = cylinder_type;
	cylinder->u_obj.cylinder.position = vec3_str_init(lines[1]);
	cylinder->u_obj.cylinder.normal = vec3_normalize(vec3_str_init(lines[2]));
	cylinder->u_obj.cylinder.r = ft_atod(lines[3]) / 2.0;
	cylinder->u_obj.cylinder.height = ft_atod(lines[4]);
	cylinder->u_obj.cylinder.color = tcolor_str_set(lines[5]);
	return (cylinder);
}

t_camera	_get_a_camera(char const **lines)
{
	t_camera	camera;

	camera.position = vec3_str_init(lines[1]);
	camera.orientation = vec3_normalize(vec3_str_init(lines[2]));
	camera.field_of_view = ft_atoi(lines[3]);
	camera.x_basis = vec3_init(0, 0, 0);//?
	camera.y_basis = vec3_init(0, 0, 0);//?
	return (camera);
}

//todo 大文字のときの処理の停止
int _parse_split_line(char const **lines, t_world * const world)
{
	if (!ft_strcmp(lines[FIRST_CHAR], "A"))
	{
		world->ambient = _get_ambient_light(lines);
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "sp"))
	{
		ft_lstadd_back(&world->shapes, ft_lstnew(_get_a_sphere(lines)));
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "pl"))
	{
		ft_lstadd_back(&world->shapes, ft_lstnew(_get_a_plain(lines)));
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "L"))
	{
		ft_lstadd_back(&world->lights, ft_lstnew(_get_a_light(lines)));
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "cy"))
	{
		ft_lstadd_back(&world->shapes, ft_lstnew(_get_a_cylinder(lines)));
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "C"))
	{
		world->camera = _get_a_camera(lines);
	}
	else
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parse_controller(char const *rt_file, t_world * const world)
{
	char		*read_line;
	char		**split_line;
	int			fd;

	//todo validation
	fd = open(rt_file, O_RDONLY);
	if (fd == -1)
	{
		//todo open fail
		return (EXIT_FAILURE);
	}
	while(gnl_wrapper(fd, &read_line))
	{
		split_line = ft_split(read_line, ' ');
		_parse_split_line(split_line, world);
		//todo ft_split leak
	}
	return (EXIT_SUCCESS);
}
