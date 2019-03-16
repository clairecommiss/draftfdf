/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelcolor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:46:24 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/16 15:20:12 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	drawline(t_fdf *env, int y, int x, int color)
{
	int *pixels;

	pixels = (int *)env->info;
	if (x >= 0 && x < 2560 && y >= 0 && y < 1300)
		pixels[(y * 2560 + x)] = color;
}

int		color(t_fdf *env, int pt, int pt2)
{
	float alt;

	alt = env->altmax;
	if (alt > 1000)
	{
		ft_putstr("Sky is the limit, bro.\n");
		ft_error(env);
	}
	if (env->coord[pt][2] > 0.4 * alt && env->coord[pt2][2] > 0.4 * alt)
		return (RED);
	else if (env->coord[pt][2] > 0.3 * alt && env->coord[pt2][2] > 0.3 * alt)
		return (ORANGE);
	else if (env->coord[pt][2] > 0.2 * alt && env->coord[pt2][2] > 0.2 * alt)
		return (YELLOW);
	else if (env->coord[pt][2] > 0.1 * alt && env->coord[pt2][2] > 0.1 * alt)
		return (GREYEL);
	else if (env->coord[pt][2] > 0.05 * alt && env->coord[pt2][2] > 0.05 * alt)
		return (YELGRE);
	else if (env->coord[pt][2] > 0 && env->coord[pt2][2] > 0)
		return (GREEN);
	else if (env->coord[pt][2] == 0.0 && env->coord[pt2][2] == 0.0)
		return (WHITE);
	else
		return (BLU);
}
