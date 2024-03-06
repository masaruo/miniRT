/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:40:01 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/06 18:04:58 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include "libft.h"

// decided not to include ft_destructor() to clean up as it is exit.
#ifdef LEAK

void	ft_perror_exit(int status, char const *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	system("leaks -q miniRT");
	exit(status);
}
#else

void	ft_perror_exit(int status, char const *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(status);
}
#endif
