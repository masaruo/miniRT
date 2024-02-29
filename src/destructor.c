/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:51:48 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 15:36:51 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destructor.h"
#include "stddef.h"
#include "libft.h"
#include "mlx.h"

#define ESC (65307)

int	deal_key(int key, t_world *world)
{
	if (key == ESC)
	{
		ft_destructor(world);
	}
	return (EXIT_SUCCESS);
}

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

int	ft_destructor(t_world *world)
{
	int	status;

	status = EXIT_SUCCESS;
	ft_lstclear(&world->lights, &tlist_free_content);
	ft_lstclear(&world->shapes, &tlist_free_content);
	status = mlx_destroy_window(world->mlx_ptr, world->win_ptr);
	system("leaks -q miniRT");
	return (status);
}

#else

int	ft_destructor(t_world *world)
{
	int	status;

	status = EXIT_SUCCESS;
	ft_lstclear(&world->lights, &tlist_free_content);
	ft_lstclear(&world->shapes, &tlist_free_content);
	status = mlx_destroy_window(world->mlx_ptr, world->win_ptr);
	return (status);
}

#endif
