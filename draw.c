/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 17:23:12 by ccommiss          #+#    #+#             */
/*   Updated: 2018/12/28 19:19:45 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			draw(t_fdf *data, unsigned char color)
{
	int count = 0;
	int dx;
	int dy;
	int m;

	while(data->coord[count + 1][3])
	{
		dx = data->coord[count + 1][0] - data->coord[count][0];
		dy = data->coord[count + 1][1] - data->coord[count][1];
		m = dy/dx;
		while (data->coord[count][0] )
		{	
			((int *)data->info)[(data->coord[count][1]) * data->x_width + data->coord[count][0]] = color;
            data->coord[count][0]++
		}



	}

}