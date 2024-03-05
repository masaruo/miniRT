/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:34:50 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/05 09:01:21 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "validation.h"
#include "get_next_line.h"
#include "t_color.h"
#include "wrapper.h"
#include <stdint.h>
#define SPACE (' ')

t_ambient	_get_ambient_light(char **lines, uint8_t *flag)
{
	t_ambient	ambient;

	check_flag_error(F_AMBIENT, flag);
	ambient.ratio = ft_ranged_xatod(lines[1], 0.0, 1.0);
	ambient.color = tcolor_str_init(lines[2]);
	return (ambient);
}

t_camera	_get_a_camera(char **lines, uint8_t *flag)
{
	t_camera	camera;

	check_flag_error(F_CAMERA, flag);
	camera.position = vec3_defalt_ranged_str_init(lines[1]);
	camera.orientation = \
		vec3_normalize(vec3_ranged_str_init(lines[2], -100.0, 100.0));
	camera.field_of_view = ft_ranged_xatod(lines[3], 0.0, 180.0);
	return (camera);
}

static void	_parse_splitted(char **ln, t_world *const wd, uint8_t *flg)
{
	char const	*sign = ln[FIRST_STR];

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
		if (!line_splitted || line_splitted[FIRST_STR] == NULL)
		{
			ft_perror_exit(EXIT_FAILURE, "failed to create splitted line");
		}
		_parse_splitted(line_splitted, world, &flag);
		ft_free_all(line_splitted);
	}
	return (flag);
}

void	parse_main(char const *file, t_world *const world)
{
	int		fd;
	uint8_t	err_bit_flag;

	fd = get_validated_fd(file);
	err_bit_flag = parse_each_lines(fd, world);
	flag_check(err_bit_flag);
}
