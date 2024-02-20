/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:51:48 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/20 10:44:01 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destructor.h"
#include "stddef.h"
#include "libft.h"
#include "mlx.h"

//! minilibx close

//! t_list close
static void	tlist_free_content(void *content)
{
	free (content);
	content = NULL;
}

int	destructor(t_world *world)
{
	int	status;

	ft_lstclear(&world->lights, &tlist_free_content);
	ft_lstclear(&world->shapes, &tlist_free_content);
	status = mlx_destroy_window(world->mlx_ptr, world->win_ptr);
#ifdef LEAK
#include <stdlib.h>
system("leaks -q miniRT");
#endif
	exit(EXIT_SUCCESS);
}
