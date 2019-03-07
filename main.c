/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:26:24 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/07 16:25:51 by ccommiss         ###   ########.fr       */
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
	
	if (y >= 0 && y <= 2560 && x >= 0 && x <= 2560 && (y * 2560 + x) < (2560 * 1300))
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

void bresen1(t_fdf *env, int pt1, int pt2, int color) 
{
	int i;
	int xinc, yinc;
	int cumul;
	float dx;
	float dy;

	mod_X(env, env->coord[pt1][0], env->coord[pt2][0]);
	mod_Y(env, env->coord[pt1][1], env->coord[pt2][1]);
	mod_Z(env, env->coord[pt1][2], env->coord[pt2][2]);
	handleviews(env);
	dx = env->pt.x1 - env->pt.x0;
	dy = env->pt.y1 - env->pt.y0;
	xinc = ( dx > 0 ) ? 1 : -1 ;
	yinc = ( dy > 0 ) ? 1 : -1 ;
	dx = fabsf(dx) ;
  	dy = fabsf(dy) ;
	drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, color);
	if ( dx > dy )
	{
	cumul = dx / 2 ;
	for ( i = 1 ; i <= dx ; i++ ) 
	{
		env->pt.x0 += xinc ;
		cumul += dy ;
		if ( cumul >= dx ) 
		{
			cumul -= dx ;
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
	float dx;
	float dy;

	dx = env->pt.x1 - env->pt.x0;
	dy = env->pt.y1 - env->pt.y0;
	xinc = ( dx > 0 ) ? 1 : -1 ;
	yinc = ( dy > 0 ) ? 1 : -1 ;
	dx = fabsf(dx) ;
  	dy = fabsf(dy) ;
	drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, color);
 	cumul = dy / 2 ;
	for ( i = 1 ; i <= dy; i++ ) 
 	{
		env->pt.y0 += yinc ;
		cumul += dx ;
		if ( cumul >= dy ) 
		{
			cumul -= dy;
			env->pt.x0 += xinc; 
		}
		if (env->pt.z0 && env->pt.z1 != 0)
			drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x, color);
		else
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


int		main(int ac,char **argv)
{
	int fd;
	t_fdf env;
	char *file = NULL;
	int endian;
	int bpp;
	int size_line;

	if (ac != 2)
		return (-1); //a gerer later les exceptions et tutti quanti babe 
	fd = open(argv[1], O_RDONLY);
	env.zoom = INITZOOM;
	env.rot_X = 0.52;
	env.rot_Z = 0.52;
	env.trans_x = 0;
	env.trans_y = 0;
	ft_analyse(&file, fd, &env);
	printf("HOLA KE TAL\n");

	env.mlx_ptr = mlx_init();
	env.win_ptr = mlx_new_window(env.mlx_ptr, 2560, 1300, "fdf");
	printf("HOLA KE TAL 2\n");
	env.img_ptr = mlx_new_image(env.mlx_ptr, 2560, 1300);
	printf("HOLA KE TAL 3\n");
	env.info = mlx_get_data_addr(env.img_ptr, &(bpp), &(size_line), &(endian));

	printf("1\n");
	sendpoints(&env);
	printf("2\n");
	mlx_put_image_to_window(env.mlx_ptr, env.win_ptr, env.img_ptr, 0, 0);
	printf("13\n");
	
	mlx_hook(env.win_ptr, 2, 1<<7, keyrepartition, &env);
	printf("14\n");
	printf("15\n");
	// printf("INFO = %s\n", env.info);
	mlx_string_put(env.mlx_ptr, env.win_ptr, 500,500, 0xFFFFFF, "CECI EST UN TESSSSSSSSSST");
	mlx_loop(env.mlx_ptr);

	return(0);
} 
