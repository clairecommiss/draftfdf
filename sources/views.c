/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   views.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:42:21 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/14 14:43:47 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	iso(float *x, float *y, float *z, t_fdf *env)
{
	float previous_x;
	float previous_y;
	float previous_z;

	previous_y = *y;
	previous_z = *z;
	previous_x = *x;
	*y = cos(env->rot_X) * previous_y - sin(env->rot_X) * previous_z;
	*z = sin(env->rot_X) * previous_y + cos(env->rot_X) * previous_z;
	previous_z = *z;
	previous_y = *y;
	previous_x = *x;
	*x = previous_x * cos(env->rot_Y) + previous_z * sin(env->rot_Y);
	*y = previous_y;
	*z = -1 * previous_x * sin(env->rot_Y) + previous_z * cos(env->rot_Y);
	previous_z = *z;
	previous_y = *y;
	previous_x = *x;
	*x = cos(env->rot_Z) * previous_x - sin(env->rot_Z) * previous_y + 2560 / 2;
	*y = sin(env->rot_Z) * previous_x + cos(env->rot_Z) * previous_y + 1300 / 2;
	*z = previous_z;
}

void	para(float *x, float *y, float z)
{
	float previous_x;
	float previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x - previous_y - z + 2560 / 2;
	*y = previous_x + previous_y + 1300 / 2;
}

void	handleviews(t_fdf *env)
{
	if (env->view.iso == 1)
	{
		iso(&env->pt.x0, &env->pt.y0, &env->pt.z0, env);
		iso(&env->pt.x1, &env->pt.y1, &env->pt.z1, env);
	}
	else if (env->view.para == 1)
	{
		para(&env->pt.x0, &env->pt.y0, env->pt.z0);
		para(&env->pt.x1, &env->pt.y1, env->pt.z1);
	}
}
