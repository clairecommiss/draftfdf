/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:26:24 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/02 18:37:46 by ccommiss         ###   ########.fr       */
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
//	printf("tRYNING TO DRAW : %d %d ----- VALUE ON MAP : %d \n", x, y, (y * 2560 + x));
	if (y >= 0 && y <= 2560 && x >= 0 && x <= 2560 && (y * 2560 + x) <= 2560*2560/2)
		pixels[(y * 2560 + x)] = color;
//printf ("ET C LE FAIL\n");
}

void colonne(t_fdf *env, int pt1, int pt2, int color) 
{
	float x0;  
	float y0;
	float y1;
	float x1;
	int i;
	int xinc, yinc;
	int cumul;

	x0 = env->zoom * env->coord[pt1][0];
	y0 = env->zoom * env->coord[pt1][1];
	x1 = env->zoom * env->coord[pt2][0];
	y1 = env->zoom * env->coord[pt2][1] ;
	
//	printf (" BEFORE ISO : FROM PT %d : x= %f, y=%f -> TO PT %d, x=%f, y=%f\n", pt1, x0, y0, (pt2), x1, y1);
if (env->view.iso == 1){
	iso (&x0, &y0, env->coord[pt1][2] * env->alt, env);
	iso (&x1, &y1, env->coord[pt2][2] * env->alt, env);
}
else if (env->view.para == 1){
	rot (&x0, &y0, env->coord[pt1][2] * env->alt, env);
	rot (&x1, &y1, env->coord[pt2][2] * env->alt, env);
}


	//	printf ("ENV ZOOM %f\n", env->zoom);
	//printf (" AFTER ISO : FROM PT %d : x= %f, y=%f -> TO PT %d, x=%f, y=%f\n", pt1, x0, y0, (pt2), x1, y1);
	float dx = x1 - x0;
	float dy = y1 - y0;
	xinc = ( dx > 0 ) ? 1 : -1 ;
	yinc = ( dy > 0 ) ? 1 : -1 ;
	dx = fabsf(dx) ;
  	dy = fabsf(dy) ;
	drawline(env, y0, x0, color);
	if ( dx > dy ) 
	{
	
		cumul = dx / 2 ;
		for ( i = 1 ; i <= dx ; i++ ) 
		{
			x0 += xinc ;
			cumul += dy ;
			if ( cumul >= dx ) 
			{
				cumul -= dx ;
				y0 += yinc ; 
			}
			if (env->coord[pt1][2] && env->coord[pt2][2] != 0)
				drawline(env, y0, x0, 0xff6666);
			else
				drawline(env, y0, x0, color);
		} 
	}
	else 
	{
		cumul = dy / 2 ;
		for ( i = 1 ; i <= dy; i++ ) 
		{
			y0 += yinc ;
			cumul += dx ;
			if ( cumul >= dy ) 
			{
				cumul -= dy;
				x0 += xinc; 
			}
			if (env->coord[pt1][2] != 0)
				drawline(env, y0, x0, 0xff6666);
			else
				drawline(env, y0, x0, color);
		}
	}
}

void sendpoints(t_fdf *env)
{
	int pt = 0;
	int i = 0;

	while (pt < env->size - 1)
	{
		//printf("----------------------- ENTERING NEW POINT : %d -----------------------------\n", pt);
		//printf("drawing LINE from pt  %d\n", pt);
		if (i++ < env->x_width - 1)
			colonne(env, pt, pt+1, 0xFFFFFF);
		else
			i = 0;
		if (pt < env->size - env->x_width )
			colonne(env, pt, (pt+env->x_width), 0xFFFFFF);
		pt++;
	}
}

 void iso(float *x, float *y, float z, t_fdf *env)
{
	float previous_x;
	float previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(ROT30) + 2560/2;
	*y = -z + (previous_x + previous_y) * sin(env->rot) + 1300/2; 
}

void 	rot(float *x, float *y, float z, t_fdf *env)
{
	float previous_x;
	float previous_y;
	float a = 1;
	(void)z;
	(void)env;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x *cos(a) - previous_y *sin(a) - z + 2560/2;
	*y = previous_x *sin(a) + previous_y*cos(a) + 1300/2;
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
	env.rot = 0.52;
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
	mlx_key_hook(env.win_ptr, keyrepartition, &env);
	printf("14\n");
	printf("15\n");
	// printf("INFO = %s\n", env.info);
	mlx_loop(env.mlx_ptr);
	return(0);
} 
