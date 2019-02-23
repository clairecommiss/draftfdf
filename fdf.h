/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 14:30:30 by ccommiss          #+#    #+#             */
/*   Updated: 2019/02/22 23:14:58 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFF_SIZE 60

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

typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*info;
	int		x_width;
	int		y_height;
	int		size; // = largeur X hauteur pour le nb total de pts 
	int	**coord;
	int		zoom;

}				t_fdf;

//parser 
void	*ft_analyse(char **file, int fd, t_fdf *env);
t_fdf	*ft_coord(t_fdf *data, char **file);
void    fill_pixel(char **info, int x, int y, int color);
int		closewin(int key, void *param);
int 	zoom(int key, void *param);
void	sendpoints(t_fdf *env);
static void iso(int *x, int *y, int z);


#endif