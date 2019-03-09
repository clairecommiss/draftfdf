/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 14:30:30 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/09 19:47:26 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFF_SIZE 10000

# define ROT30 (30 * 3.14 / 180)
# define INITZOOM 30
# define GREEN 0x68C800
# define WHITE 0xFFFFFF

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


typedef	struct s_br
{	
	float dx;
	float dy;
	float x0;
	float x1;
	float y0;
	float y1;
	float z0;
	float z1;
}				t_br;



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
	double rot_X;
	double rot_Y;
	double rot_Z;
	double trans_y;
	double trans_x;
	t_view  view;
	t_br 	pt;
	int loop;

}				t_fdf;

//parser 
int		ft_analyse(char **file, int fd, t_fdf *env);
int		ft_coord(t_fdf *data, char **file);
int		closewin(t_fdf *env);
void 	zoom(t_fdf *env, int key);
void	sendpoints(t_fdf *env);
void 	iso(float *x, float *y, float *z, t_fdf *env);
void 	para(float *x, float *y, float z, t_fdf *env);
void	handleviews(t_fdf *env);
void   	bresen2(t_fdf *env, int pt, int pt2);
void 	reinit(t_fdf *env);
void	erase(t_fdf *env);
void	base(t_fdf *env);
int		ft_error(t_fdf *env);
int		keyrepartition(int key, void *param);
void 	freetab(t_fdf *env);

void rot_Y(float *x, float *y, float *z, t_fdf *env);
void iso(float *x, float *y, float *z, t_fdf *env);

void	init_struct(t_fdf *env);

#endif