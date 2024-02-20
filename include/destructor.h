/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:51:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/20 11:13:36 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTRUCTOR_H
#define DESTRUCTOR_H

#include "t_world.h"

int	destructor(t_world *world);
int	deal_key(int key, t_world *world);
int	click_close_button(t_world *world);

#endif
