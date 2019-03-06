/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 16:25:08 by ccommiss          #+#    #+#             */
/*   Updated: 2018/12/28 14:30:11 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    fill_pixel(char **info, int x, int y, int color)
{
    int *pixels = (int *)*info;
    
    while (y * 1500 + x <= (1500*1500))
    {
        x = 0;
        while (x < 1500)
        {
            pixels[y * 1500 + x] = color;
            x ++;
        }
        y++; 
    }
}