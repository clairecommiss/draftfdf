/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 18:31:04 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/02 18:58:12 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h" 



t_fdf	*ft_coord(t_fdf *data, char **file)
{
	int i;
	int x;
	int y;
	char **tab;
	char **line;
	int count; 

	i = 0;
	x = 0;
	y = 0;
	count = 0;
	tab = ft_strsplit(*file, '\n');
	while (tab[y])
	{
		printf("TAB I %s\n", tab[y]);
		line = ft_strsplit(tab[y], ' ');
		while (line[x])
		{
			printf("LINE A %s\n", line[x]);
			data->coord[count] = (float *)malloc(sizeof(float) * 3);
			data->coord[count][0] = (float)x;
			data->coord[count][1] = (float)y;
			data->coord[count][2] = (float)ft_atoi(line[x]);
			printf("DATA COORD de COUNT %d ---- X = %d ; Y = %d ; Z = %f \n", count, x, y, data->coord[count][2]);
			count++;
			x++;
		}
		x = 0;
		y++;
	}
	data->coord[count] = 0;
	return (data);
}

int	ft_analyse(char **file, int fd, t_fdf *data)
{
	int a;
	char *line = NULL;
	char **tab;

	data->x_width = 0;
	data->y_height = 0;
	data->size = 0;
	data->alt = data->zoom;
	a = 0;
	while(get_next_line(fd, &line) == 1)
	{
		if (a == 0)
		{	
			tab = ft_strsplit(line, ' ');
			while(tab[a])
			{
			//	printf("TAB A %s", tab[a]);
				a++;
			}
			data->x_width = a;
			free(tab);
		}
		data->y_height++;
	//	printf("TEST %d\n", data->y_height);
		*file = ft_strjoin2(*file, line);	
		*file = ft_strjoin2(*file, "\n"); 
	}
	data->size = data->x_width * data->y_height;
	//printf("WIDTH = %d & HEIGHT = %d && SIZE = %d\n", data->x_width, data->y_height, data->size);
	if (!(data->coord = (float **)malloc(sizeof(float *) * (data->size + 4))))
	 	return (0);
	data = ft_coord(data, file);
//	printf("HEY BITCHES \n\n");
	return (1);
}
