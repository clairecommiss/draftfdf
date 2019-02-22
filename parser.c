/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 18:31:04 by ccommiss          #+#    #+#             */
/*   Updated: 2019/02/22 19:45:43 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h" 

t_fdf	*ft_coord(t_fdf *data, char **file)
{
	int i;
	int x;
	int y;
	int count; 

	i = 0;
	x = 0;
	y = 0;
	count = 0;
	printf("EUH SALUT \n");
	while(file[0][i])
	{
		if(ft_isdigit(file[0][i]) == 1 && (file[0][i + 1] == ' ' || file[0][i + 1] == '\n'))
		{
			data->coord[count] = (float *)malloc(sizeof(float) * 3);
			data->coord[count][0] = x;
			data->coord[count][1] = y;
			if (ft_isdigit(file[0][i - 1]) == 1)
				data->coord[count][2] = ft_atoi(&file[0][i - 1]);
			else
				data->coord[count][2] = 0;
			
			printf("X-Y-Z VAUT : pt %d [%d - %d - %f] \n", count, x, y, data->coord[count][2]);
			printf ("DATA %f", data->coord[count][0] );
			x++;
			count++;
		}
		if (file[0][i] == '\n')
		{	
			y++;
			x = 0;
		}
		i++;
	}
	data->coord[count] = 0;
	return (data);
}

void	*ft_analyse(char **file, int fd, t_fdf *data)
{

	int a;
	char *line = NULL;
	char **tab;

	data->x_width = 0;
	data->y_height = 0;
	data->size = 0;
	a = 0;
	while(get_next_line(fd, &line) == 1)
	{
		if (a == 0)
		{	
			tab = ft_strsplit(line, ' ');
			while(tab[a])
			{
				printf("TAB A %s", tab[a]);
				a++;
			}
			data->x_width = a;
			free(tab);
		}
		data->y_height++;
		printf("TEST %d\n", data->y_height);
		*file = ft_strjoin2(*file, line);	
		*file = ft_strjoin2(*file, "\n"); 
	}
	data->size = data->x_width * data->y_height;
	printf("WIDTH = %d & HEIGHT = %d && SIZE = %d\n", data->x_width, data->y_height, data->size);

	if (!(data->coord = (float **)malloc(sizeof(float *) * (data->size))))
	 	return (0);
	printf("ON A MALLOC AVEC SUCCES OU PEUT ETRE PAS\n");
	data = ft_coord(data, file);
	return ("WESH\n");
}
