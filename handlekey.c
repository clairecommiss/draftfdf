/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlekey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:57:56 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/08 16:07:13 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void move(t_fdf *env, int key)
{
	if (key == KEY_UP)
		env->trans_y -= env->zoom;
	else if (key == KEY_DOWN)
		env->trans_y += env->zoom;
	else if (key == KEY_RIGHT)
		env->trans_x += env->zoom;
	else if (key == KEY_LEFT)
		env->trans_x -= env->zoom;
	else if (key == KEY_L)
		env->loop = !env->loop;
	erase(env);
	sendpoints(env);
	base(env);
}

void zoom(t_fdf *env, int key)
{
	if (key == KEY_Z)
		env->zoom = env->zoom + 1;
	else if (key == KEY_D && env->zoom > 1)
		env->zoom = env->zoom - 1;
	else if (key == KEY_H)
		env->alt += 1;
	else if (key == KEY_L)
		env->alt -= 1;
	else if (key == KEY_4)
		env->rot_X = env->rot_X + 0.1;
	else if (key == KEY_8)
		env->rot_Z = env->rot_Z + 0.1;
	

	erase(env);
	sendpoints(env);
	base(env);

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
	base(env);
}



int		keyrepartition(int key, void *param)
{
	t_fdf *env = (t_fdf *)param;
	if (key == 53)
		closewin(env);
	if (key == KEY_Z || key == KEY_D || key == KEY_H || key == KEY_L || key == KEY_4 || key == KEY_8)
		zoom(env, key);
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN || key == KEY_L)
		move(env, key);
	if (key == KEY_I || key == KEY_P)
		view(env, key);
	if (key == KEY_0)
		reinit(env);
	return (0);
}

