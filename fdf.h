/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 14:30:30 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/02 17:57:53 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFF_SIZE 60

# define ROT30 (30 * 3.14 / 180)
# define INITZOOM 30

# include "mlx.h"
# include "events.h" 
# include "./libft/includes/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>

int		get_next_line(const int fd, char **line);


typedef struct s_view
{
	int 	iso;
	int		para;

}			t_view;


typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*info;
	int		x_width;
	int		y_height;
	int		size; // = largeur X hauteur pour le nb total de pts 
	float	**coord;
	int		zoom;
	int		alt;
	double rot;
	t_view  view; 

}				t_fdf;

//parser 
int	ft_analyse(char **file, int fd, t_fdf *env);
t_fdf	*ft_coord(t_fdf *data, char **file);
void    fill_pixel(char **info, int x, int y, int color);
int		closewin(t_fdf *env);
void 	zoom(t_fdf *env, int key);
void	sendpoints(t_fdf *env);
 void iso(float *x, float *y, float z, t_fdf *env);
 void 	rot(float *x, float *y, float z, t_fdf *env);

int		keyrepartition(int key, void *param);

#endif