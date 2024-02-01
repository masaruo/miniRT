/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_material.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:42:59 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/01 14:37:16 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MATERIAL_H
#define T_MATERIAL_H

#include "t_color.h"

// マテリアル構造体
typedef struct s_material
{
	t_color	color;
	t_color	ambient;//! 定数になるはずだから、いらないかも
	t_color	diffuse;
	t_color	specular;
	double	shininess;
}	t_material;

#endif