/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:06:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/21 14:00:43 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PARSE_H
#define PARSE_H

#include "libft.h"
#include "t_world.h"

#define F_SHAPE (1)
#define F_CAMERA (2)
#define F_LIGHT (4)
#define F_AMBIENT (8)
#define F_ERROR (128)

int	parse_main(char const *rt_file, t_world * const world);

#endif
