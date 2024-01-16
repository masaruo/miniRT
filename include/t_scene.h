/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:06:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/16 11:13:00 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SCENE_H
#define T_SCENE_H

#include "libft.h"
#include "t_color.h"

typedef struct s_scene
{
	t_list	*shapes;
	t_list	*cameras;
	t_list	*lights;
	t_color	ambient;
}	t_scene;

#endif