/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabouzah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:46:57 by nabouzah          #+#    #+#             */
/*   Updated: 2019/11/26 08:36:36 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	begin_point(int *x, int *y, t_fdf fdf)
{
	int	prex;
	int	prey;

	prex = fdf.map->width * fdf.dist / 2;
	prey = fdf.map->height * fdf.dist / 2;
	*x = fdf.win_w / 2 - prex + fdf.key.r - fdf.key.l;
	*y = fdf.win_h / 2 - prey - fdf.key.up + fdf.key.d;
	if (fdf.iso)
	{
		if (prex == prey)
			*x += fdf.map->width * fdf.dist / 2;
		else if (prex > prey)
			*x += prex * 2 / 3;
		else
			*x += prex * 5 / 4;
	}
}

int		scale_win(int *width, int *height)
{
	int		d;
	int		fact;

	d = 4;
	fact = 3;
	while (fact && d == 4)
	{
		d = 40;
		while (d > 4 && (*width * d * fact > (int)MAX_WIDTH ||\
					*height * d * fact > (int)MAX_HEIGHT))
			d--;
		fact--;
	}
	*width <= 6 ? *width *= 2 : 1;
	*height <= 4 ? *height *= 2 : 1;
	*width *= d * fact;
	*height *= d * fact;
	if (!fact)
	{
		*width = MAX_WIDTH;
		*height = MAX_HEIGHT;
	}
	return ((!fact ? 3 : d));
}

void	fdf_init(t_fdf *fdf, t_map *map, char *title)
{
	int	win_width;
	int	win_height;
	int	d;
	int	fact;

	fdf->init = mlx_init();
	fact = 3;
	win_width = map->width;
	win_height = map->height;
	d = scale_win(&win_width, &win_height);
	fdf->dist = d;
	fdf->win_w = win_width;
	fdf->win_h = win_height;
	fdf->win = mlx_new_window((*fdf).init, fdf->win_w, fdf->win_h, title);
}

void	project(t_fdf *fdf, t_map *map, char *title)
{
	char	*tmp;

	tmp = ft_strjoin("FDF: ", title);
	fdf_init(fdf, map, tmp);
	drew_map(*fdf, map);
	ft_strdel(&tmp);
	fdf->color = 0;
	mlx_hook((*fdf).win, 2, 0, &key_press, fdf);
	mlx_hook((*fdf).win, 17, 0, &ft_close, fdf);
	mlx_loop((*fdf).init);
}
