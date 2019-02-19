/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:26:24 by ccommiss          #+#    #+#             */
/*   Updated: 2019/02/17 19:18:17 by ccommiss         ###   ########.fr       */
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

// void ligne(t_fdf *env) {
//   int dx; //coef dire de x entre deux pts
//   int dy; //coef dir de y entre 2pts
//   int i;
//   int xinc;
//   int yinc;
//   int x ;
//   int y ;
//   int cumul;
//   int pt = 0;

// int *pixels = (int *)env->info;

// while (pt <= env->size){
// 	x = env->coord[pt][0];
// 	y = env->coord[pt][1];
//   	dx = env->coord[pt + 1][0]- env->coord[pt][0];
//   	dy = env->coord[pt + 1][1]- env->coord[pt][1];
// 	  pt++;
//   	xinc = ( dx > 0 ) ? 1 : -1 ;
//   	yinc = ( dy > 0 ) ? 1 : -1 ;
//   	dx = abs(dx) ;
//   	dy = abs(dy) ;
//   	pixels[x] = 0xff6666;
//   	if ( dx > dy ) {
//     cumul = dx / 2 ;
//     for ( i = 1 ; i <= dx ; i++ ) {
//       x += xinc ;
//       cumul += dy ;
//       if ( cumul >= dx ) {
//         cumul -= dx ;
//         y += yinc ; }
//       pixels[x] = 0xff6666; } }
//     else {
//     cumul = dy / 2 ;
//     for ( i = 1 ; i <= dy ; i++ ) {
//       y += yinc ;
//       cumul += dx ;
//       if ( cumul >= dy ) {
//         cumul -= dy ;
//         x += xinc ; }
//       pixels[x] = 0xff6666; }
// 	   }
// }

//}


void    fill_full(t_fdf *env, int x, int y, int color)
{
    int *pixels = (int *)env->info;
		
    
    while ((y * env->x_width + x) < env->size)
    {
    	x = 0;
			printf("BIZARRE??\n");
			while (x < env->x_width)
			{
				printf("POSITION = %d\n", y * env->x_width + x);
				printf("ON EST LA??\n");
				if (env->coord[y * env->x_width + x][2] == 0)
				{
					printf("EUH?\n");
					pixels[(y*10 * env->x_width + x) * 10] = 0xff6666;
			//		printf("DATA COORD ICI %f %f %f\n", env->coord[y * env->x_width + x][0], env->coord[y * env->x_width + x][1], env->coord[y * env->x_width + x][2]);
				}
				else 
				{
					pixels[(y*10 * env->x_width + x) * 10] = color;
				}
				printf("EUH?\n");
				printf("X = %d\n", x);
				printf("Y = %d\n", y);
				x++;
				}
		y ++;
		printf("SEGFAULT??\n");
    }
}

int		closewin(int key, void *param)
{
	t_fdf *envtot = (t_fdf *)param;
	if (key == 53)
	{
		//mlx_destroy_image
		printf("COUCOU\n");
		//mlx_clear_window(param.mlx_ptr, param.win_ptr);
		mlx_destroy_window(envtot->mlx_ptr, envtot->win_ptr);
		exit(0);
	}
	return(0);

}

int		main(int ac,char **argv)
{
	int fd;
	t_fdf env;
	char *file = NULL;
	int endian;
	int bpp;
    int size_line;
	int i = 0;

	if (ac != 2)
		return (-1); //a gerer later les exceptions et tutti quanti babe 
	fd = open(argv[1], O_RDONLY);
	//printf("ON A LU\n");
	ft_analyse(&file, fd, &env);
	printf("OK\n");

	printf("env X %d Y %d SIZE %d...\n", env.x_width, env.y_height, env.size);
	while (i++ < 208)
		printf("DATA COORD %f %f %f\n", env.coord[i][0], env.coord[i][1], env.coord[i][2]);

    env.mlx_ptr = mlx_init();
  	env.win_ptr = mlx_new_window(env.mlx_ptr, (env.x_width * 20), (env.y_height * 20), "fdf");
  	env.img_ptr = mlx_new_image(env.mlx_ptr, (env.x_width * 10), (env.y_height * 10 ));
    env.info = mlx_get_data_addr(env.img_ptr, &(bpp), &(size_line), &(endian));
	// printf("ENV %s\n", env.info);
    fill_full(&env, 0, 0, 0xFFFFFF);
//	ligne(&env);
	mlx_put_image_to_window(env.mlx_ptr, env.win_ptr, env.img_ptr, 0, 0);
	mlx_key_hook(env.win_ptr, closewin, &env);
    // printf("INFO = %s\n", env.info);
    mlx_loop(env.mlx_ptr);

    return(0);
}
	