/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:06:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/01 15:16:03 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PARSE_H
#define PARSE_H

#include "libft.h"
#include "t_world.h"

int	parse_controller(char const *rt_file, t_world * const world);

#endif