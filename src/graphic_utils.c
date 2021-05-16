/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 01:04:32 by user42            #+#    #+#             */
/*   Updated: 2021/05/16 03:33:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	add_shade(double shade, int color)
{
	if (0 > shade)
		return (color);
	if (shade >= 1)
		return (0);
	((unsigned char *)&color)[0] *= (1.0 - shade);
	((unsigned char *)&color)[1] *= (1.0 - shade);
	((unsigned char *)&color)[2] *= (1.0 - shade);
	return (color);
}

int		rgb(unsigned char r, unsigned char g,
					unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= img->width || y <= 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}