/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlekey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:57:56 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/01 15:40:17 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int move(int key, void *param)
{
	t_fdf *env = (t_fdf *)param;
	int *pixels = (int *)env->info;
	int x = 0;
	int y = 0;
	int pt = 0;

if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
{
	if (key == KEY_UP)
	{
	//	printf("SIZE = %d \n", env->size);
		while (pt < env->size)
		{
		//	printf("POINT %d --------------: BEFORE X = %f && Y = %f\n", pt, env->coord[pt][0], env->coord[pt][1]);
			env->coord[pt][0] -= 1;
		//	printf ("TEST 1 %d ------------ : NEW X = %f\n", pt, env->coord[pt][0]); 
			env->coord[pt][1] -= 1;
			//printf ("TEST 2 %d ------------ : NEW Y = %f\n", pt, env->coord[pt][1]); 
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
	//printf ("Z ENCLENCHE : ZOOM = %d\n", env->zoom);
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	while (y * 2560 + x < 2500 * 2500)
	{
		pixels[(y * 2560 + x)] = 000000;
		x++;
	}
	sendpoints(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	}
	return (0);
}


int zoom(int key, void *param)
{
	t_fdf *env = (t_fdf *)param;
	int *pixels = (int *)env->info;
	int x = 0;
	int y = 0;

if (key == KEY_Z || key == KEY_D)
{
	if (key == KEY_Z)
		env->zoom = env->zoom + 1;
	else if (key == KEY_D)
		env->zoom = env->zoom - 1;
	//printf ("Z ENCLENCHE : ZOOM = %d\n", env->zoom);
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	while (y * 2560 + x < 2500 * 2500)
	{
		pixels[(y * 2560 + x)] = 000000;
		x++;
	}
		sendpoints(env);
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	}
	return (0);
}






int		closewin(int key, void *param)
{
	t_fdf *envtot = (t_fdf *)param;
	if (key == 53)
	{
		mlx_destroy_window(envtot->mlx_ptr, envtot->win_ptr);
		exit(0);
	}
	return(0);
}