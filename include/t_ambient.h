/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ambient.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:16:06 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 07:32:23 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_AMBIENT_H
# define T_AMBIENT_H

# include "t_color.h"

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

#endif
