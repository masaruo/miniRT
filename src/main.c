/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:20:54 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/06 16:38:37 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

int	main(int argc, char **argv)
{	
	int	status;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd("Number of argc is invalid\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	minirt_main(argv[1]);
	return (EXIT_SUCCESS);
}

/*
座標の入力値は「−１００〜＋１００」の仕様
arrow up = camera y +
arrow down = camera y -
arrow right = camera x +
arrow left = camera x -
z = camera z forward
x = camera z backward
r = camera orientation y -
t = camera orientation y +
*/
