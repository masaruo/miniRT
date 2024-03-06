/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:51:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/06 16:44:30 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTRUCTOR_H
# define DESTRUCTOR_H

# include "t_world.h"

void	ft_destructor(t_world *world);
int		hook_keys(int key, t_world *world);
int		click_close_button(t_world *world);

#endif
