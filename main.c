/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:26:24 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/08 19:59:25 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*read_it(int fd)
{
	char *final = NULL;
	char stock[BUFF_SIZE + 1];
	int i;

	while ((i = read(fd, stock, BUFF_SIZE)) > 0)
	{
		stock[i] = '\0';
		final = ft_strjoin2(final, stock);
	}
	return (final);
}

void	drawline(t_fdf *env, int y, int x, int color)
{
	int *pixels = (int *)env->info;
	
	if (env->loop == 0 && x >= 0 && x < 2560 && y >= 0 && y < 1300)
	{
		if (env->pt.z0 && env->pt.z1 != 0)
			pixels[(y * 2560 + x)] = color;
		else 
			pixels[(y * 2560 + x)] = 0xff6666;
	}
	else if (env->loop == 1 && y * 2560 + x < (2560 * 1300) && (y * 2560 + x) >= 0)
	{
		if (env->pt.z0 && env->pt.z1 != 0)
			pixels[(y * 2560 + x)] = color;
		else 
			pixels[(y * 2560 + x)] = 0xff6666;
	}
}

void 	mod_X(t_fdf *env, float x0, float x1)
{
	env->pt.x0 = x0 * env->zoom;
	env->pt.x1 = x1 * env->zoom;
}

void 	mod_Y(t_fdf *env, float y0, float y1)
{
	env->pt.y0 = y0 * env->zoom;
	env->pt.y1 = y1 * env->zoom;
}

void 	mod_Z(t_fdf *env, float z0, float z1)
{
	env->pt.z0 = z0 * env->alt;
	env->pt.z1 = z1 * env->alt;
}

void initall(t_fdf *env, int pt1, int pt2)
{
	
	mod_X(env, env->coord[pt1][0], env->coord[pt2][0]);
	mod_Y(env, env->coord[pt1][1], env->coord[pt2][1]);
	mod_Z(env, env->coord[pt1][2], env->coord[pt2][2]);
	handleviews(env);
	//printf ("PT x0 = %f, x1 = %f, y0 = %f, y1 = %f, z0 = %f, z1 = %f", env->pt.x0, 
	// env->pt.x1, env->pt.y0, env->pt.y1, env->pt.z0, env->pt.z1);
	env->pt.dx = env->pt.x1 - env->pt.x0;
	//printf ("PT DX LA HAUT = %f \n", env->pt.dx);
	env->pt.dy = env->pt.y1 - env->pt.y0;
}

void bresen1(t_fdf *env, int pt1, int pt2, int color) 
{
	int i;
	int xinc, yinc;
	int cumul;
	initall(env, pt1, pt2); // initialisation de env.dy et env.dy la haut 
	xinc = ( env->pt.dx > 0 ) ? 1 : -1 ;
	yinc = ( env->pt.dy > 0 ) ? 1 : -1 ;
	env->pt.dx = fabsf(env->pt.dx) ;
  	env->pt.dy = fabsf(env->pt.dy) ;
	//printf("PT %d TO PT %d from br1// NEW ONE DX -- %f  && DY -- %f : \n", pt1, pt2, env->pt.dx, env->pt.dy);
	drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, color);
	if (env->pt.dx > env->pt.dy)
	{
		cumul = env->pt.dx / 2 ;
	for ( i = 1 ; i <= env->pt.dx ; i++ )
	{
		env->pt.x0 += xinc ;
		cumul += env->pt.dy ;
		if ( cumul >= env->pt.dx )
		{
			cumul -= env->pt.dx;
			env->pt.y0 += yinc ; 
		}
		drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, color);
	}
	}
	else 
		bresen2(env, color);
}

void bresen2(t_fdf *env, int color) 
{
	int i;
	int xinc, yinc;
	int cumul;

	env->pt.dx = env->pt.x1 - env->pt.x0;
	env->pt.dy = env->pt.y1 - env->pt.y0;
	xinc = ( env->pt.dx > 0 ) ? 1 : -1 ;
	yinc = ( env->pt.dy > 0 ) ? 1 : -1 ;
	env->pt.dx = fabsf(env->pt.dx);
  	env->pt.dy = fabsf(env->pt.dy);
	drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, color);
 	cumul = env->pt.dy / 2 ;
	for ( i = 1 ; i <= env->pt.dy; i++ ) 
 	{
		env->pt.y0 += yinc ;
		cumul += env->pt.dx ;
		if ( cumul >= env->pt.dy) 
		{
			cumul -= env->pt.dy;
			env->pt.x0 += xinc; 
		}
		drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, color);
	}
}

void sendpoints(t_fdf *env)
{
	int pt = 0;
	int i = 0;

	while (pt < env->size - 1)
	{
		if (i++ < env->x_width - 1)
			bresen1(env, pt, pt+1, 0xFFFFFF);
		else
			i = 0;
		if (pt < env->size - env->x_width )
			bresen1(env, pt, (pt+env->x_width), 0xFFFFFF);
		pt++;
	}
}

int		main(int ac, char **argv)
{
	int fd;
	t_fdf env;
	char *file = NULL;

	if (ac != 2)
		return (-1); //a gerer later les exceptions et tutti quanti babe 
	fd = open(argv[1], O_RDONLY);
	init_struct(&env);
	if (!(ft_analyse(&file, fd, &env)))
	{
		ft_putstr("NTM WRONG FILE \n");
		ft_error(&env);
	}
	sendpoints(&env);
	mlx_put_image_to_window(env.mlx_ptr, env.win_ptr, env.img_ptr, 0, 0);
	mlx_hook(env.win_ptr, 2, 1<<7, keyrepartition, &env);
	mlx_string_put(env.mlx_ptr, env.win_ptr, 500,500, 0xFFFFFF, "CECI EST UN TESSSSSSSSSST");
	mlx_loop(env.mlx_ptr);

	return(0);
} 
