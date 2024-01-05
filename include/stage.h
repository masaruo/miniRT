/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stage.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:40:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/05 15:41:37 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STAGE_H
#define STAGE_H

typedef struct s_stage
{
	void	*mlx;
	void	*win;
	int		screen_witdh;
	int		screen_height;
}	t_stage;

#endif