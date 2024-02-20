/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:34:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/20 09:31:16 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "ft_atod.h"
#include "get_next_line.h"
#include "t_light.h"
#include "t_color.h"
#include "t_shape.h"
// #include <fcntl.h>
#include <stdint.h>
#include "wrapper.h"

#define SPACE (' ')
#define FIRST_CHAR (0)
#define AMBIENT (1)
#define CAMERA (2)
#define LIGHT (3)
#define OBJECTS (4)

t_ambient _get_ambient_light(char const **lines)
{
	t_ambient	ambient;

	ambient.ratio = ft_ranged_xatod(lines[1], 0.0, 1.0);
	ambient.color = tcolor_str_set(lines[2]);
	return (ambient);
}

t_light	*_get_a_light(char const **lines)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	if (light == NULL)
	{
		ft_perror_exit(EXIT_FAILURE, "ft_calloc failed.");
	}
	light->vector = vec3_str_init(lines[1]);
	light->brightness = ft_ranged_xatod(lines[2], 0.0, 1.0);
	light->color = tcolor_str_set(lines[3]);
	return (light);
}

t_shape	*_get_a_sphere(char const **lines)
{
	t_shape	*sphere;

	sphere = ft_calloc(1, sizeof(t_shape));
	if (sphere == NULL)
		ft_perror_exit(EXIT_FAILURE, "ft_calloc failed.");
	sphere->type = sphere_type;
	sphere->u_obj.sphere.center = vec3_str_init(lines[1]);
	sphere->u_obj.sphere.r = ft_ranged_xatod(lines[2], 0.0, 100) / 2.0;
	sphere->u_obj.sphere.color = tcolor_str_set(lines[3]);
	return (sphere);
}

t_shape	*_get_a_plain(char const **lines)
{
	t_shape	*plane;

	plane = ft_calloc(1, sizeof(t_shape));
	if (plane == NULL)
		ft_perror_exit(EXIT_FAILURE, "ft_calloc failed.");
	plane->type = plane_type;
	plane->u_obj.plane.position = vec3_str_init(lines[1]);
	plane->u_obj.plane.normal = vec3_normalize(vec3_ranged_str_init(lines[2], -1.0, 1.0));
	plane->u_obj.plane.color = tcolor_str_set(lines[3]);
	return (plane);
}

t_shape	*_get_a_cylinder(char const **lines)
{
	t_shape	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_shape));
	if (cylinder == NULL)
		ft_perror_exit(EXIT_FAILURE, "ft_calloc failed");
	cylinder->type = cylinder_type;
	cylinder->u_obj.cylinder.position = vec3_str_init(lines[1]);
	cylinder->u_obj.cylinder.normal = vec3_normalize(vec3_ranged_str_init(lines[2], -1.0, 1.0));
	cylinder->u_obj.cylinder.r = ft_ranged_xatod(lines[3], 0.0, 100.0) / 2.0;
	cylinder->u_obj.cylinder.height = ft_ranged_xatod(lines[4], 0.0, 100.0);
	cylinder->u_obj.cylinder.color = tcolor_str_set(lines[5]);
	return (cylinder);
}

t_camera	_get_a_camera(char const **lines)
{
	t_camera	camera;

	camera.position = vec3_str_init(lines[1]);
	camera.orientation = vec3_normalize(vec3_ranged_str_init(lines[2], -100.0, 100.0));
	camera.field_of_view = ft_ranged_xatod(lines[3], 0.0, 180.0);
	camera.x_basis = vec3_init(0, 0, 0);//?
	camera.y_basis = vec3_init(0, 0, 0);//?
	return (camera);
}

int _parse_splitted_line(char const **lines, t_world * const world, uint8_t *flag)
{
	char const	*first_str = lines[FIRST_CHAR];

	if (!ft_strcmp(lines[FIRST_CHAR], "A"))
	{
		world->ambient = _get_ambient_light(lines);
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "C"))
	{
		world->camera = _get_a_camera(lines);
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "L"))
	{
		ft_lstadd_back(&world->lights, ft_lstnew(_get_a_light(lines)));
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "sp"))
	{
		ft_lstadd_back(&world->shapes, ft_lstnew(_get_a_sphere(lines)));
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "pl"))
	{
		ft_lstadd_back(&world->shapes, ft_lstnew(_get_a_plain(lines)));
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "cy"))
	{
		ft_lstadd_back(&world->shapes, ft_lstnew(_get_a_cylinder(lines)));
	}
	else if (!ft_strcmp(lines[FIRST_CHAR], "#") || !ft_strcmp(first_str, "\n"))
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_perror_exit(EXIT_FAILURE, "unrecognizable element sign detected.");
	}
	return (EXIT_SUCCESS);
}

uint8_t	parse_lines(int fd, t_world * const world)
{
	char	*line;
	char	**line_splitted;
	uint8_t	flag;

	while (gnl_wrapper(fd, &line))
	{
		line_splitted = ft_split(line, SPACE);
		free(line);
		if (!line_splitted || line_splitted[FIRST_CHAR] == NULL)
			ft_perror_exit(EXIT_FAILURE, "failed to create splitted line");
		_parse_splitted_line(line_splitted, world, &flag);
	}
}

int	parse_main(char const *file, t_world * const world)
{
	int		fd;
	char	*line;
	char	**split_by_space;
	uint8_t	flag;

	fd = get_validated_fd(file);
	flag = parse_lines(fd, world);
	return (EXIT_SUCCESS);
}
