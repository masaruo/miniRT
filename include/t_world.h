/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_world.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:40:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 07:39:25 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_WORLD_H
# define T_WORLD_H

# include "t_color.h"
# include "t_image.h"
# include "libft.h"
# include "t_camera.h"
# include "t_ambient.h"

# define TITLE ("miniRT")
# define WIDTH (1000)
# define HEIGHT (800)

typedef struct s_world
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			screen_witdh;
	int			screen_height;
	t_image		img;
	t_list		*shapes;
	t_list		*lights;
	t_camera	camera;
	t_ambient	ambient;
}	t_world;

t_world	tworld_init(void);

#endif
