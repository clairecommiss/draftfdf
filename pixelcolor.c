/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelcolor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:46:24 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/13 16:46:51 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	drawline(t_fdf *env, int y, int x, int color)
{
	int *pixels;

	pixels = (int *)env->info;
	if (x >= 0 && x < 2560 && y >= 0 && y < 1300)
		pixels[(y * 2560 + x)] = color;
}

int		color(t_fdf *env, int pt, int pt2)
{
	if (env->coord[pt][2] > 0 && env->coord[pt2][2] > 0)
		return (0xff6666);
	else if (env->coord[pt][2] == 0)
		return (WHITE);
	else
		return (0xADD8E6);
}