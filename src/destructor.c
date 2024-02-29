/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:51:48 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 14:20:07 by mogawa           ###   ########.fr       */
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
		destructor(world);
	}
	return (EXIT_SUCCESS);
}

int	click_close_button(t_world *world)
{
	destructor(world);
	return (EXIT_SUCCESS);
}

static void	tlist_free_content(void *content)
{
	free (content);
	content = NULL;
}

int	destructor(t_world *world)
{
	int	status;

	status = EXIT_SUCCESS;
	ft_lstclear(&world->lights, &tlist_free_content);
	ft_lstclear(&world->shapes, &tlist_free_content);
	status = mlx_destroy_window(world->mlx_ptr, world->win_ptr);
	return (status);
}
