/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 18:31:04 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/08 16:01:43 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_coord(t_fdf *data, char **file)
{
	int		x;
	int		y;
	char	**tab;
	char	**line;
	int		pt;

	x = 0;
	y = 0;
	pt = 0;
	tab = ft_strsplit(*file, '\n');
	while (tab[y])
	{
		line = ft_strsplit(tab[y], ' ');
		while (line[x])
		{
			if (!(data->coord[pt] = (float *)malloc(sizeof(float) * 3)))
				return (0);
			data->coord[pt][0] = (float)x - 0.5 * data->x_width;
			data->coord[pt][1] = (float)y - 0.5 * data->y_height;
			data->coord[pt][2] = (float)ft_atoi(line[x]);
			pt++;
			x++;
		}
		x = 0;
		y++;
	}
	data->coord[pt] = 0;
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
		if (a == 0)
		{
			tab = ft_strsplit(line, ' ');
			while (tab[a])
				a++;
			data->x_width = a;
			free(tab);
		}
		data->y_height++;
		*file = ft_strjoin2(*file, line);
		*file = ft_strjoin2(*file, "\n");
	}
	data->size = data->x_width * data->y_height;
	if (!(data->coord = (float **)malloc(sizeof(float *) * (data->size + 1))))
		return (0);
	ft_coord(data, file);
	return (1);
}
