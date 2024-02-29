/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:18:26 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 12:45:56 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "wrapper.h"
#include <stdbool.h>
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

#define FIRST_CHAR (0)
// #define UPPER_LIMIT (100.0)
// #define LOWER_LIMIT (-100.0)
#define	VALID_PARSE_BITFLG (15)

static void	_validate_file_name(char const *filename)
{
	char const	*dot_loc_front = ft_strchr(filename, '.');
	char const	*dot_loc_back = ft_strrchr(filename, '.');

	if (dot_loc_front != dot_loc_back)
	{
		ft_perror_exit(EXIT_FAILURE, "more than one dot in the name.");
	}
	else if (filename[FIRST_CHAR] == '.')
	{
		ft_perror_exit(EXIT_FAILURE, "filename cannot start with dot.");
	}
	else if (ft_strcmp(dot_loc_front, ".rt") != 0)
	{
		ft_perror_exit(EXIT_FAILURE, "filename cannot end except '.rt'.");
	}
}

int	get_validated_fd(char const *filename)
{
	int		fd;
	char	*line;
	char	**split_by_space;

	_validate_file_name(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_perror_exit(EXIT_FAILURE, "could not open the file.");
	return (fd);
}

void	check_flag_error(int flag_type, uint8_t *flag)
{
	if (flag_type == F_CAMERA && (*flag & F_CAMERA) == 0)
	{
		*flag |= F_CAMERA;
	}
	else if (flag_type == F_LIGHT && (*flag & F_LIGHT) == 0)
	{
		*flag |= F_LIGHT;
	}
	else if (flag_type == F_AMBIENT && (*flag & F_AMBIENT) == 0)
	{
		*flag |= F_AMBIENT;
	}
	else if (flag_type == F_SHAPE)
	{
		*flag |= F_SHAPE;
	}
	else
	{
		*flag |= F_ERROR;
	}
}

void	flag_check(uint8_t flg)
{
	if (flg != VALID_PARSE_BITFLG)
	{
		ft_perror_exit(EXIT_FAILURE, "number of objs is invalid.");
	}
}
