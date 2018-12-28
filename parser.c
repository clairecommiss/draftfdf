/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 18:31:04 by ccommiss          #+#    #+#             */
/*   Updated: 2018/12/28 17:44:48 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h" 

void	ft_coord(t_fdf *data, char **file)
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
			//data->coord[count][2] = ft_atoi(*file[i]);
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
}

void	*ft_analyse(char **file, int fd, t_fdf *data)
{

	int a;
	char *line = NULL;

	printf("file = %s\n", *file);
	data->x_width = 0;
	data->y_height = 0;
	data->size = 0;
	a = 0;
	while(get_next_line(fd, &line) == 1)
	{
		if (a == 0)
		{	
			printf("line = %s\n", line);
			data->x_width = ft_countchr(line, ' ');
			a++;
		}
		data->y_height = data->y_height + ft_countchr(line, '\n');
		printf("TEST %d\n", data->y_height);
		*file = ft_strjoin2(*file, line);	
		*file = ft_strjoin2(*file, "\n"); 
	}
	data->size = data->x_width * data->y_height;
	printf("WIDTH = %d & HEIGHT = %d && SIZE = %d\n", data->x_width, data->y_height, data->size);

	printf("AYAYAYAY\n");
	printf("file = \n%s\n", *file);

	if (!(data->coord = (float **)malloc(sizeof(float *) * (data->size))))
	 	return (0);
	printf("ON A MALLOC AVEC SUCCES OU PEUT ETRE PAS\n");
	ft_coord(data, file);
	return ("WESH\n");
}
		
