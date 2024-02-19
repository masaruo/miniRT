/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:18:26 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 17:04:59 by mogawa           ###   ########.fr       */
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
#define UPPER_LIMIT (100.0)
#define LOWER_LIMIT (-100.0)

static void	_validate_file_name(char const *filename)
{
	char const *dot_loc_front = ft_strchr(filename, '.');
	char const *dot_loc_back = ft_strrchr(filename, '.');

	if (dot_loc_front == dot_loc_back)
	{
		ft_perror_exit("more than one dot in the name.");
	}
	else if (filename[FIRST_CHAR] == '.')
	{
		ft_perror_exit("filename cannot start with dot.");
	}
	else if (ft_strcmp(dot_loc_front, ".rt") != 0)
	{
		ft_perror_exit("filename cannot end except '.rt'.");
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
