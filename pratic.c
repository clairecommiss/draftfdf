/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pratic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 16:06:18 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/13 12:14:26 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	base(t_fdf *env)
{
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 320, GREEN, "Moves");
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 350, WHITE,
	" <- / UP / DOWN / ->");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 480, GREEN, "Projections");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 510, WHITE, "I / P");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 560, GREEN, "Rotations");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 590, WHITE, "4 / 8");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 640, GREEN, "Reset view");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 670, WHITE, "0");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 880, GREEN, "Close");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 910, 0xFFFFFF, "Esc");
}

void	erase(t_fdf *env)
{
	int *pixels;
	int x;
	int y;

	pixels = (int *)env->info;
	x = 0;
	y = 0;
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	while (y * 2560 + x < 2560 * 1300)
	{
		pixels[(y * 2560 + x)] = 000000;
		x++;
	}
}

void	reinit(t_fdf *env)
{
	env->trans_y = 0;
	env->trans_x = 0;
	env->rot_X = 0.52;
	env->rot_Y = 0.52;
	env->rot_Z = 0;
	env->zoom = INITZOOM;
	env->alt = env->zoom;
	erase(env);
	sendpoints(env);
	base(env);
}

void	init_struct(t_fdf *env)
{
	int endian;
	int bpp;
	int sl;

	env->mlx_ptr = mlx_init();
	env->win_ptr = mlx_new_window(env->mlx_ptr, 2560, 1300, "fdf");
	env->img_ptr = mlx_new_image(env->mlx_ptr, 2560, 1300);
	env->info = mlx_get_data_addr(env->img_ptr, &(bpp), &(sl), &(endian));
	env->zoom = INITZOOM;
	env->rot_X = 0.52;
	env->rot_Z = 0;
	env->rot_Y = 0.52;
	env->trans_x = 0;
	env->trans_y = 0;
	env->pt.dx = 0;
	env->pt.dy = 0;
	env->view.iso = 1;
	env->view.para = 0;
	env->loop = 0;
	env->x_width = 0;
	env->y_height = 0;
	env->size = 0;
	env->alt = env->zoom;
	env->coord = NULL;
}

int		ft_error(t_fdf *env)// ne pas free mlx ptr
{
	int x;

	x = 0;
	if (env->img_ptr != NULL)
		mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	if (env->win_ptr != NULL)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	if (env->coord != NULL)
		freetab(env);
	ft_putstr("An error occured. Please try with a valid map. \n");
	exit(0);
}
