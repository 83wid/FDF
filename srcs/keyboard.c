/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabouzah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 05:43:44 by nabouzah          #+#    #+#             */
/*   Updated: 2019/11/26 14:42:38 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_key(t_crl *key)
{
	key->r = 0;
	key->l = 0;
	key->d = 0;
	key->up = 0;
	key->alt_up = 2;
	key->alt_down = 1;
}

void	total_exit(t_fdf *fdf)
{
	freefunc(&fdf->map);
	mlx_clear_window(fdf->init, fdf->win);
	mlx_destroy_window(fdf->init, fdf->win);
	exit(-1);
}

int		set_alt(int z, t_fdf fdf)
{
	if (z)
		return (z * (fdf.key.alt_up - fdf.key.alt_down));
	else
		return (z);
}

int		ft_close(t_fdf *fdf)
{
	total_exit(fdf);
	return (0);
}

int		key_press(int code, t_fdf *fdf)
{
	if (code == 53)
		total_exit(fdf);
	fdf->key.up += (code == 126 ? 10 : 0);
	fdf->key.d += (code == 125 ? 10 : 0);
	fdf->key.l += (code == 123 ? 10 : 0);
	fdf->key.r += (code == 124 ? 10 : 0);
	fdf->dist -= code == 78 && fdf->dist > 2 ? 2 : 0;
	fdf->dist += code == 69 && fdf->dist < 500 ? 2 : 0;
	if (code == 34)
		fdf->iso = 1;
	if (code == 35)
		fdf->iso = 0;
	fdf->color += (code == 13 ? 20 : 0);
	fdf->color += (code == 1 ? -20 : 0);
	fdf->color = (code == 15 ? 0 : fdf->color);
	fdf->key.alt_up += (code == 4 ? 1 : 0);
	fdf->key.alt_down += (code == 37 ? 1 : 0);
	mlx_clear_window(fdf->init, fdf->win);
	drew_map(*fdf, fdf->map);
	return (1);
}
