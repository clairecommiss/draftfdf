/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 12:19:14 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/13 16:38:47 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int		color(t_fdf *env, int pt, int pt2)
{
	if (env->coord[pt][2] > 0 && env->coord[pt2][2] > 0)
		return (0xff6666);
	else if (env->coord[pt][2] == 0)
		return (WHITE);
	else 
		return (0xADD8E6);
}

void	initall(t_fdf *env, int pt1, int pt2)
{
	mod_all(env, pt1, pt2);
	handleviews(env);
	env->pt.dx = env->pt.x1 - env->pt.x0;
	env->pt.dy = env->pt.y1 - env->pt.y0;
}

void	drawline(t_fdf *env, int y, int x, int color)
{
	int *pixels;

	pixels = (int *)env->info;
	if (x >= 0 && x < 2560 && y >= 0 && y < 1300)
		pixels[(y * 2560 + x)] = color;
}

void	mod_all(t_fdf *env, int pt1, int pt2)
{
	env->pt.x0 = env->coord[pt1][0] * env->zoom;
	env->pt.x1 = env->coord[pt2][0] * env->zoom;
	env->pt.y0 = env->coord[pt1][1] * env->zoom;
	env->pt.y1 = env->coord[pt2][1] * env->zoom;
	env->pt.z0 = env->coord[pt1][2] * env->alt;
	env->pt.z1 = env->coord[pt2][2] * env->alt;
}

void	bresen1(t_fdf *env, int pt1, int pt2)
{
	int i;
	int xinc;
	int yinc;
	int cumul;

	i = 0;
	xinc = (env->pt.dx > 0) ? 1 : -1;
	yinc = (env->pt.dy > 0) ? 1 : -1;
	env->pt.dx = fabsf(env->pt.dx);
	env->pt.dy = fabsf(env->pt.dy);
	cumul = env->pt.dx / 2;
	while (i++ <= env->pt.dx)
	{
		env->pt.x0 += xinc;
		cumul += env->pt.dy;
		if (cumul >= env->pt.dx)
		{
			cumul -= env->pt.dx;
			env->pt.y0 += yinc;
		}
		drawline(env, env->pt.y0 + env->trans_y,
		env->pt.x0 + env->trans_x, color(env, pt1, pt2));
	}
}

void	bresen2(t_fdf *env, int pt1, int pt2)
{
	int i;
	int xinc;
	int yinc;
	int cumul;

	i = 0;
	xinc = (env->pt.dx > 0) ? 1 : -1;
	yinc = (env->pt.dy > 0) ? 1 : -1;
	env->pt.dx = fabsf(env->pt.dx);
	env->pt.dy = fabsf(env->pt.dy);
	cumul = env->pt.dy / 2;
	while (i++ <= env->pt.dy)
	{
		env->pt.y0 += yinc;
		cumul += env->pt.dx;
		if (cumul >= env->pt.dy)
		{
			cumul -= env->pt.dy;
			env->pt.x0 += xinc;
		}
		drawline(env, env->pt.y0 + env->trans_y,
			env->pt.x0 + env->trans_x, color(env, pt1, pt2));
	}
}
