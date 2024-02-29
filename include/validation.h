/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:18:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/02/29 13:17:28 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "stdint.h"
# define F_SHAPE (1)
# define F_CAMERA (2)
# define F_LIGHT (4)
# define F_AMBIENT (8)
# define F_ERROR (128)
# define FIRST_STR (0)

int		get_validated_fd(char const *filename);
void	check_flag_error(int flag_type, uint8_t *flag);
void	flag_check(uint8_t flg);

#endif
