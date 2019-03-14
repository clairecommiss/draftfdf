/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:26:24 by ccommiss          #+#    #+#             */
/*   Updated: 2019/03/14 15:18:12 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	dispatch(t_fdf *env, int pt1, int pt2)
{
	initall(env, pt1, pt2);
	drawline(env, env->pt.y0 + env->trans_y, env->pt.x0 + env->trans_x,
	color(env, pt1, pt2));
	if (fabsf(env->pt.dx) > fabs(env->pt.dy))
		bresen1(env, pt1, pt2);
	else
		bresen2(env, pt1, pt2);
}

void	sendpoints(t_fdf *env)
{
	int pt;
	int i;

	pt = 0;
	i = 0;
	while (pt < env->size - 1)
	{
		if (i++ < env->x_width - 1)
			dispatch(env, pt, pt + 1);
		else
			i = 0;
		if (pt < env->size - env->x_width)
			dispatch(env, pt, (pt + env->x_width));
		pt++;
	}
}

int		main(int ac, char **argv)
{
	int		fd;
	t_fdf	env;
	char	*file;

	file = NULL;
	if (ac != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	init_struct(&env);
	if (!(ft_analyse(&file, fd, &env)))
		ft_error(&env);
	sendpoints(&env);
	mlx_put_image_to_window(env.mlx_ptr, env.win_ptr, env.img_ptr, 0, 0);
	mlx_hook(env.win_ptr, 2, 1 << 7, keyrepartition, &env);
	base(&env);
	mlx_loop(env.mlx_ptr);
	while (1)// test
		exit(0); // test
	return (0);
}
