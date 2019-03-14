/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 18:31:04 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/14 15:16:51 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		freetab(t_fdf *env)
{
	int x;

	x = 0;
	while (x < env->size)
	{
		free(env->coord[x]);
		x++;
	}
	free(env->coord);
}

int			ft_fuckingnorme(t_fdf *data, int x, int y, int pt)
{
	if (!(data->coord[pt] = (float *)malloc(sizeof(float) * 3)))
	{
		ft_error(data);
		return (0);
	}
	data->coord[pt][0] = (float)x - 0.5 * data->x_width;
	data->coord[pt][1] = (float)y - 0.5 * data->y_height;
	return (1);
}

int			ft_coord(t_fdf *data, char **tab, int pt, char **line)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (tab[y])
	{
		line = ft_strsplit(tab[y], ' ');
		while (line[x])
		{
			ft_fuckingnorme(data, x, y, pt);
			data->coord[pt][2] = (float)ft_atoi(line[x]);
			if (data->coord[pt][2] > data->altmax)
				data->altmax = data->coord[pt][2];
			x++;
			pt++;
		}
		free(line);
		free(tab[y]); // test et je crois que ca marche
		x = 0;
		y++;
	}
	free(tab); // test et je sais pas trop si c utile
	data->coord[pt] = 0;
	return (1);
}

int			mallocdata(t_fdf *data, char **file)
{
	char	**tab;
	char	**line;
	int		pt;

	pt = 0;
	line = NULL;
	if (!(tab = ft_strsplit(*file, '\n')))
	{
		free(tab);
		return (0);
	}
	data->size = data->x_width * data->y_height;
	if (!(data->coord = (float **)malloc(sizeof(float *) * (data->size + 1))))
		return (0);
	if (!(ft_coord(data, tab, pt, line)))
	{
		ft_error(data);
		return (0);
	}
	return (1);
}

int			ft_analyse(char **file, int fd, t_fdf *data)
{
	int		a;
	char	*line;
	char	**tab;

	a = 0;
	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		tab = ft_strsplit(line, ' ');
		while (tab[a])
			a++;
		data->x_width = data->x_width == 0 ? a : data->x_width;
		free(tab);
		if (a != data->x_width || data->x_width <= 1)
			ft_error(data);
		a = 0;
		data->y_height++;
		line = ft_strjoin2(line, "\n");
		*file = ft_strjoin2(*file, line);
		free(line);
	}
	if (get_next_line(fd, &line) == -1 || data->y_height <= 1)
		ft_error(data);
	mallocdata(data, file);
	return (1);
}
