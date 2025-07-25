/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:46:35 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 16:47:03 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 文字ｃがASCIIなら１を返し、それ以外は０を返す
int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (1);
	else
		return (0);
}
