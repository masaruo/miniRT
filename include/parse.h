/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:06:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 14:08:07 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PARSE_H
# define PARSE_H

# include "t_world.h"
# include "t_shape.h"
# include "t_light.h"

void	parse_main(char const *file, t_world *const world);
t_light	*_get_a_light(char **lines);
t_shape	*_get_a_sphere(char **lines);
t_shape	*_get_a_plain(char **lines);
t_shape	*_get_a_cylinder(char **lines);

#endif
