/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_world.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:40:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/01 15:43:48 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_WORLD_H
#define T_WORLD_H

# include "t_color.h"
# include "t_image.h"
# include "libft.h"

# define TITLE ("miniRT")
# define WIDTH (512)
# define HEIGHT (512)

typedef struct s_ambient
{
	double	ratio;//from 0.0 to 1.0
	t_color	color;
}	t_ambient;

typedef struct s_world
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			screen_witdh;
	int			screen_height;
	t_image		img;
	t_list		*shapes;//物体のリスト
	t_list		*cameras;//カメラリスト
	t_list		*lights;//光源リスト
	t_ambient	ambient;
}	t_world;

t_world	tworld_init(void);

#endif