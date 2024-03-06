/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:51:48 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/06 16:44:36 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destructor.h"
#include "stddef.h"
#include "libft.h"
#include "mlx.h"

int	click_close_button(t_world *world)
{
	ft_destructor(world);
	return (EXIT_SUCCESS);
}

static void	tlist_free_content(void *content)
{
	free (content);
	content = NULL;
}

#ifdef LEAK

void	ft_destructor(t_world *world)
{
	ft_lstclear(&world->lights, &tlist_free_content);
	ft_lstclear(&world->shapes, &tlist_free_content);
	mlx_destroy_window(world->mlx_ptr, world->win_ptr);
	ft_putstr_fd("ft_destractor called. Bye.\n", STDOUT_FILENO);
	system("leaks -q miniRT");
	exit(EXIT_SUCCESS);
}

#else

void	ft_destructor(t_world *world)
{
	ft_lstclear(&world->lights, &tlist_free_content);
	ft_lstclear(&world->shapes, &tlist_free_content);
	mlx_destroy_window(world->mlx_ptr, world->win_ptr);
	ft_putstr_fd("ft_destractor called. Bye.\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

#endif
