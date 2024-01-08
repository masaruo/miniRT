/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_world.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:40:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/08 19:31:11 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_WORLD_H
#define T_WORLD_H

# include "t_image.h"

# define TITLE ("mogawa's miniRT")

typedef struct s_world
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		screen_witdh;
	int		screen_height;
	t_image	img;
}	t_world;

t_world	tworld_init(int in_witdh, int in_height);

#endif