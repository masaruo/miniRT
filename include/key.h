/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:36:59 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/13 13:09:10 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# include "t_world.h"

int		hook_keys(int key, t_world *world);
void	paint_each_xy_pixcel(t_world *world);
int		render_next_frame(t_world *world);

#endif
