/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:34:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 13:08:59 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "validation.h"
#include "ft_atod.h"
#include "get_next_line.h"
#include "t_light.h"
#include "t_color.h"
#include "t_shape.h"
#include "wrapper.h"
#include <stdint.h>

#include "t_plane.h"

#define SPACE (' ')
#define FIRST_CHAR (0)
#define AMBIENT (1)
#define CAMERA (2)
#define LIGHT (3)
#define OBJECTS (4)

t_ambient	_get_ambient_light(char const **lines, uint8_t *flag)
{
	t_ambient	ambient;

	check_flag_error(F_AMBIENT, flag);
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

t_camera	_get_a_camera(char const **lines, uint8_t *flag)
{
	t_camera	camera;

	check_flag_error(F_CAMERA, flag);
	camera.position = vec3_str_init(lines[1]);
	camera.orientation = vec3_normalize(vec3_ranged_str_init(lines[2], -100.0, 100.0));
	camera.field_of_view = ft_ranged_xatod(lines[3], 0.0, 180.0);
	camera.x_basis = vec3_init(0, 0, 0);//?
	camera.y_basis = vec3_init(0, 0, 0);//?
	return (camera);
}

void	_parse_splitted(char const **ln, t_world *const wd, uint8_t *flg)
{
	char const	*sign = ln[FIRST_CHAR];

	if (!ft_strcmp(sign, "A"))
		wd->ambient = _get_ambient_light(ln, flg);
	else if (!ft_strcmp(sign, "C"))
		wd->camera = _get_a_camera(ln, flg);
	else if (!ft_strcmp(sign, "L"))
	{
		ft_lstadd_back(&wd->lights, ft_lstnew(_get_a_light(ln)));
		check_flag_error(F_LIGHT, flg);
	}
	else
	{
		if (!ft_strcmp(sign, "sp"))
			ft_lstadd_back(&wd->shapes, ft_lstnew(_get_a_sphere(ln)));
		else if (!ft_strcmp(sign, "pl"))
			ft_lstadd_back(&wd->shapes, ft_lstnew(_get_a_plain(ln)));
		else if (!ft_strcmp(sign, "cy"))
			ft_lstadd_back(&wd->shapes, ft_lstnew(_get_a_cylinder(ln)));
		else if (!ft_strcmp(sign, "#") || !ft_strcmp(sign, "\n"))
			return ;
		else
			ft_perror_exit(EXIT_FAILURE, "unrecognizable sign detected.");
		check_flag_error(F_SHAPE, flg);
	}
}

static uint8_t	parse_each_lines(int fd, t_world *const world)
{
	char	*line;
	char	**line_splitted;
	uint8_t	flag;

	flag = 0;
	while (gnl_wrapper(fd, &line))
	{
		line_splitted = ft_split(line, SPACE);
		free(line);
		if (!line_splitted || line_splitted[FIRST_CHAR] == NULL)
		{
			ft_perror_exit(EXIT_FAILURE, "failed to create splitted line");
		}
		_parse_splitted(line_splitted, world, &flag);
		ft_free_all(line_splitted);
	}
	return (flag);
}

void	parse_main(char const *file, t_world * const world)
{
	int		fd;
	char	*line;
	char	**split_by_space;
	uint8_t	flag;
	int		status;

	fd = get_validated_fd(file);
	flag = parse_each_lines(fd, world);
	flag_check(flag);
}
