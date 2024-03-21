/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:56:18 by mogawa            #+#    #+#             */
/*   Updated: 2024/03/20 11:39:40 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H

# include <stddef.h>

void	ft_perror_exit(int status, char const *msg);
double	ft_xatod(char const *const str_num);
double	ft_ranged_xatod(char const *const str_num, double min, double max);
void	check_num_childs_valid(char **splitted, size_t num_childs);
char	**ft_xsplit(char const *s, char c, size_t num_childs);

#endif
