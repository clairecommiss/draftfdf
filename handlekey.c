/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlekey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:57:56 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/06 18:03:29 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void base(t_fdf *env)
{
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	// mlx_string_put(env->mlx_ptr, env->win_ptr, 10, 10, 0xFFFFFF, "ROTATE : 4 / 8");
	// mlx_string_put(env->mlx_ptr, env->win_ptr, 10, 40, 0xFFFFFF, "ZOOM - UNZOOM : Z / D");
	// mlx_string_put(env->mlx_ptr, env->win_ptr, 10, 60, 0xFFFFFF, "MOVE : RI -> / LE <- / UP ↑ / DOW ↓");


	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 320, 0x68C800, "Moves");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 350, 0xFFFFFF, " <- / UP / DOWN / ->");
    // mlx_string_put(env->mlx_ptr, env->win_ptr, 1830 + 500, 400, 0x68C800, "Height");
    // mlx_string_put(env->mlx_ptr, env->win_ptr, 1785 + 500, 430, 0xFFFFFF, "Pg_up / Pg_down");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 480, 0x68C800, "Projections");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 510, 0xFFFFFF, "I / P");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 560, 0x68C800, "Rotations");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 590, 0xFFFFFF, "4 / 8");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 640, 0x68C800, "Reset view");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 670, 0xFFFFFF, "0");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 720, 0x68C800, "Toggle HUD");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 750, 0xFFFFFF, "H");
    // mlx_string_put(env->mlx_ptr, env->win_ptr, 1820 + 500, 800, 0x68C800, "Colorset");
    // mlx_string_put(env->mlx_ptr, env->win_ptr, 1815 + 500, 830, 0xFFFFFF, "Z / X / C");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 880, 0x68C800, "Close");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 910, 0xFFFFFF, "Esc");

}


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
	if (key == KEY_UP)
		env->trans_y -= env->zoom;
	else if (key == KEY_DOWN)
		env->trans_y += env->zoom;
	else if (key == KEY_RIGHT)
		env->trans_x += env->zoom;
	else if (key == KEY_LEFT)
		env->trans_x -= env->zoom;
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

void 	reinit(t_fdf *env)
{
	env->trans_y = 0;
	env->trans_x = 0;
	env->zoom = INITZOOM;
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
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
		move(env, key);
	if (key == KEY_I || key == KEY_P)
		view(env, key);
	if (key == KEY_0)
		reinit(env);
	return (0);
}

