/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:56:18 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/19 21:22:30 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
#define WRAPPER_H

# include <stdlib.h>

void	ft_perror_exit(int status, char const *msg);
double	ft_xatod(char const * const str_num);
double	ft_ranged_xatod(char const * const str_num, size_t min, size_t max);
char**	ft_xsplit(char const *s, char c, size_t num_childs);

#endif
