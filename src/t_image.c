/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_image.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:29:09 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/08 12:06:16 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_image.h"
#include "mlx.h"

t_image	timage_init(void *mlx_ptr, int width, int height)
{
	t_image	img;

	img.img_ptr = mlx_new_image(mlx_ptr, width, height);
	//todo error
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	//todo error
	return (img);
}

void	my_mlx_pixcel_put(t_image const *img, int x, int y, int color)
{
	char	*pixcel;
	int		offset;

	// todo input error handle
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	pixcel = img->addr + offset;
	*(unsigned int*)pixcel = color;
}
