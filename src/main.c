/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:20:54 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 15:38:28 by mogawa           ###   ########.fr       */
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
	status = minirt_main(argv[1]);
	return (status);
}

//! 座標の入力値は「−１００〜＋１００」の仕様
