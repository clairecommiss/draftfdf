/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pratic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 16:06:18 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/08 16:07:20 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	base(t_fdf *env)
{
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 320, 0x68C800, "Moves");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 350, 0xFFFFFF, " <- / UP / DOWN / ->");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 480, 0x68C800, "Projections");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 510, 0xFFFFFF, "I / P");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 560, 0x68C800, "Rotations");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 590, 0xFFFFFF, "4 / 8");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 640, 0x68C800, "Reset view");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 670, 0xFFFFFF, "0");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 720, 0x68C800, "Toggle HUD");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100 , 750, 0xFFFFFF, "H");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 880, 0x68C800, "Close");
    mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 910, 0xFFFFFF, "Esc");
}

void	erase(t_fdf *env)
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

void 	reinit(t_fdf *env)
{
	env->trans_y = 0;
	env->trans_x = 0;
	env->zoom = INITZOOM;
	erase(env);
	sendpoints(env);
	base(env);
}