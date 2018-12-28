/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:57:53 by ccommiss          #+#    #+#             */
/*   Updated: 2018/12/23 19:22:00 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>




void    fill_full(t_fdf *env, int x, int y, int color)
{
    int *pixels = (int *)env->info;
    
    while ((y * env->x_width + x) <= (env->x_width * env->y_height))
    {
        x = 0;
        while (x < env->x_width)
        {
            pixels[y * env->x_width + x] = color;
            x ++;
        }
        y++; 
    }
}

int     main()
{
    t_fdf env;

    int endian;
    int bpp;
    int size_line;

    env.x_width = 1500;
    env.y_height  = 1500;
    env.mlx_ptr = mlx_init();
    env.win_ptr = mlx_new_window(env.mlx_ptr, env.x_width, env.y_height, "fdf");
    env.img_ptr = mlx_new_image(env.mlx_ptr, env.x_width, env.y_height);
    env.info = mlx_get_data_addr(env.img_ptr, &(bpp), &(size_line), &(endian));
    fill_full(&env, 0, 0, 0xFFFFFF);
    mlx_put_image_to_window(env.mlx_ptr, env.win_ptr, env.img_ptr, 0, 0);
    printf("BPP = %d\n  SL = %d\n endian = %d\n", bpp, size_line, endian);
    printf("INFO = %s\n", env.info);
    mlx_loop(env.mlx_ptr);
    return(0);
}