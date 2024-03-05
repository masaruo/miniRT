/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:42:53 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/02 07:42:13 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOW_H
# define SHADOW_H

# include "t_light.h"
# include "t_intersect.h"

t_ray	get_shadow_ray(t_intersect const *intersect, t_light const *light);

#endif
