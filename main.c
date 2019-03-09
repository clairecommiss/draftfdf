/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:26:24 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/09 20:11:46 by ccommiss         ###   ########.fr       */
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

void	drawline(t_fdf *env, int y, int x, int pt, int pt2)
{
	int *pixels = (int *)env->info;
	
	if (x >= 0 && x < 2560 && y >= 0 && y < 1300)
	{
		if (env->coord[pt][2] > 0 && env->coord[pt2][2] > 0)
			pixels[(y * 2560 + x)] = 0xff6666;
		else if (env->coord[pt][2] == 0)
			pixels[(y * 2560 + x)] = WHITE;
		else 
			pixels[(y * 2560 + x)] = 0xADD8E6;
	}
}

void 	mod_all(t_fdf *env, int pt1, int pt2)
{
	env->pt.x0 = env->coord[pt1][0] * env->zoom;
	env->pt.x1 = env->coord[pt2][0] * env->zoom;
	env->pt.y0 = env->coord[pt1][1] * env->zoom;
	env->pt.y1 = env->coord[pt2][1] * env->zoom;
	env->pt.z0 = env->coord[pt1][2] *  env->alt;
	env->pt.z1 = env->coord[pt2][2] *  env->alt;
}

void initall(t_fdf *env, int pt1, int pt2)
{
	
	mod_all(env, pt1, pt2);
	handleviews(env);
	env->pt.dx = env->pt.x1 - env->pt.x0;
	env->pt.dy = env->pt.y1 - env->pt.y0;
}

void bresen1(t_fdf *env, int pt1, int pt2) 
{
	int i;
	int xinc, yinc;
	int cumul;
	i = 0;
	initall(env, pt1, pt2); // initialisation de env.dy et env.dy la haut 
	xinc = ( env->pt.dx > 0 ) ? 1 : -1 ;
	yinc = ( env->pt.dy > 0 ) ? 1 : -1 ;
	env->pt.dx = fabsf(env->pt.dx) ;
  	env->pt.dy = fabsf(env->pt.dy) ;
	//printf("PT %d TO PT %d from br1// NEW ONE DX -- %f  && DY -- %f : \n", pt1, pt2, env->pt.dx, env->pt.dy);
	drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, pt1, pt2);
	if (env->pt.dx > env->pt.dy)
	{
		cumul = env->pt.dx / 2 ;
	while (i++ <= env->pt.dx)
	{
		env->pt.x0 += xinc ;
		cumul += env->pt.dy ;
		if ( cumul >= env->pt.dx )
		{
			cumul -= env->pt.dx;
			env->pt.y0 += yinc ; 
		}
		drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, pt1, pt2);
	}
	}
	else 
		bresen2(env, pt1, pt2);
}

void bresen2(t_fdf *env, int pt1, int pt2) 
{
	int i;
	int xinc, yinc;
	int cumul;
	i = 0;

	env->pt.dx = env->pt.x1 - env->pt.x0;
	env->pt.dy = env->pt.y1 - env->pt.y0;
	xinc = ( env->pt.dx > 0 ) ? 1 : -1 ;
	yinc = ( env->pt.dy > 0 ) ? 1 : -1 ;
	env->pt.dx = fabsf(env->pt.dx);
  	env->pt.dy = fabsf(env->pt.dy);
	drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, pt1, pt2);
 	cumul = env->pt.dy / 2 ;
	while (i++ <= env->pt.dy)
 	{
		env->pt.y0 += yinc ;
		cumul += env->pt.dx ;
		if ( cumul >= env->pt.dy) 
		{
			cumul -= env->pt.dy;
			env->pt.x0 += xinc; 
		}
		drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, pt1, pt2);
	}
}

void sendpoints(t_fdf *env)
{
	int pt = 0;
	int i = 0;

	while (pt < env->size - 1)
	{
		if (i++ < env->x_width - 1)
			bresen1(env, pt, pt+1);
		else
			i = 0;
		if (pt < env->size - env->x_width )
			bresen1(env, pt, (pt+env->x_width));
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
		ft_error(&env);
	sendpoints(&env);
	mlx_put_image_to_window(env.mlx_ptr, env.win_ptr, env.img_ptr, 0, 0);
	mlx_hook(env.win_ptr, 2, 1<<7, keyrepartition, &env);
	base(&env);
	mlx_loop(env.mlx_ptr);

	return(0);
} 
