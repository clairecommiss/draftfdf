/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:26:24 by ccommiss          #+#    #+#             */
/*   Updated: 2018/12/28 17:38:23 by ccommiss         ###   ########.fr       */
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

void    fill_full(t_fdf *env, int x, int y, int color)
{
    int *pixels = (int *)env->info;
    
    while ((y * env->x_width + x) <= (env->size))
    {
    	x = 0;
    	while (x < (env->x_width))
		{
            pixels[y * env->x_width + x] = color;
            x ++;
    	}
	    y++; 
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
	//printf("ON A LU\n");
	ft_analyse(&file, fd, &env);
	printf("OK");

	printf("env X %d Y   %d ...", env.x_width, env.y_height);

    env.mlx_ptr = mlx_init();
    env.win_ptr = mlx_new_window(env.mlx_ptr, 150, 150, "fdf");
    env.img_ptr = mlx_new_image(env.mlx_ptr, env.x_width, env.y_height);
    env.info = mlx_get_data_addr(env.img_ptr, &(bpp), &(size_line), &(endian));
    fill_full(&env, 0, 0, 0xFFFFFF);
    mlx_put_image_to_window(env.mlx_ptr, env.win_ptr, env.img_ptr, 0, 0);
    // printf("INFO = %s\n", env.info);
    mlx_loop(env.mlx_ptr);
    return(0);
}
	