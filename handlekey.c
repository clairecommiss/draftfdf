/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlekey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:57:56 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/02 17:29:42 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void erase(t_fdf *env)
{
	int *pixels = (int *)env->info;
	int x = 0;
	int y = 0;

	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	while (y * 2560 + x < 2500 * 2500)
	{
		pixels[(y * 2560 + x)] = 000000;
		x++;
	}
}


void move(t_fdf *env, int key)
{
	int pt = 0;

	if (key == KEY_UP)
	{
		while (pt < env->size)
		{
			env->coord[pt][0] -= 1;
			env->coord[pt][1] -= 1;
			pt++;
		}
	}
	else if (key == KEY_DOWN)
	{
		while (pt < env->size)
		{
			env->coord[pt][0] += 1;
			env->coord[pt][1] += 1;
			pt++;
		}
	}
	else if (key == KEY_RIGHT)
	{
		while (pt < env->size)
		{
			env->coord[pt][0] += 1;
			env->coord[pt][1] -= 1;
			pt++;
		}
	}
	else if (key == KEY_LEFT)
	{
		while (pt < env->size)
		{
			env->coord[pt][0] -= 1;
			env->coord[pt][1] += 1;
			pt++;
		}
	}
	erase(env);
	sendpoints(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
}

void zoom(t_fdf *env, int key)
{
	if (key == KEY_Z)
		env->zoom = env->zoom + 1;
	else if (key == KEY_D)
		env->zoom = env->zoom - 1;
	else if (key == KEY_H)
		env->alt += 1;
	else if (key == KEY_L)
		env->alt -= 1;
	else if (key == KEY_R)
		env->rot = env->rot + 0.1;
	erase(env);
	sendpoints(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
}

int		closewin(t_fdf *env)
{
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	exit(0);
}

void view(t_fdf *env, int key)
{
	if (key == KEY_I)
	{
		env->view.iso = 1;
		env->view.para= 0;
	}
	if (key == KEY_P)
	{
		env->view.iso = 0;
		env->view.para = 1;
	}
	erase(env);
	sendpoints(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
}

void 	reinit(t_fdf *env)
{
	int pt;
	int diff_x;
	int diff_y;
	int i;

	pt = 0;
	i = 0;
	diff_x = env->coord[0][0];
	diff_y = env->coord[0][1];
	while (i < abs(diff_x))
	{	
		while (pt != env->size)
		{
			diff_x > 0 ? env->coord[pt][0]-- : env->coord[pt][0]++;
			pt ++;
		}
		i++;
		pt = 0;
	}
	i = 0;
	while (i < abs(diff_y))
	{	
		while (pt != env->size)
		{
			diff_y > 0 ? env->coord[pt][1]-- : env->coord[pt][1]++;
			pt++;
		}
		i++;
		pt = 0;
	}
	env->zoom = INITZOOM;
	erase(env);
	sendpoints(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);	
}

int		keyrepartition(int key, void *param)
{
	t_fdf *env = (t_fdf *)param;
	if (key == 53)
		closewin(env);
	if (key == KEY_Z || key == KEY_D || key == KEY_H || key == KEY_L || key == KEY_R)
		zoom(env, key);
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
		move(env, key);
	if (key == KEY_I || key == KEY_P)
		view(env, key);
	if (key == KEY_0)
		reinit(env);
	return (0);
}

