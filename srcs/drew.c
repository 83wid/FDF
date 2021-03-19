/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drew.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabouzah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 03:50:25 by nabouzah          #+#    #+#             */
/*   Updated: 2019/11/26 08:37:17 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	drew_h(t_fdf fdf, t_drew d)
{
	int		dp_c[2];
	t_point	tmp;

	tmp = d.begin;
	d.dx = abs(d.cur.x - d.begin.x);
	d.sx = tmp.x < d.cur.x ? 1 : -1;
	d.dy = abs(d.cur.y - tmp.y);
	d.sy = tmp.y < d.cur.y ? 1 : -1;
	dp_c[0] = (d.dx > d.dy ? d.dx : -1 * d.dy) / 2;
	dp_c[1] = (d.cur.c < d.begin.c ? d.cur.c : d.begin.c);
	while (tmp.x != d.cur.x || tmp.y != d.cur.y)
	{
		mlx_pixel_put(fdf.init, fdf.win, tmp.x + d.x0, tmp.y + d.y0, dp_c[1]);
		if (dp_c[0] >= -d.dx && tmp.x != d.cur.x)
		{
			dp_c[0] -= d.dy;
			tmp.x += d.sx;
		}
		if (dp_c[0] < d.dy && tmp.y != d.cur.y)
		{
			dp_c[0] += d.dx;
			tmp.y += d.sy;
		}
	}
}

void	drew_v(t_fdf fdf, t_drew d)
{
	int dp;
	int	c;

	d.dx = abs(d.next.x - d.begin.x);
	d.sx = d.begin.x < d.next.x ? 1 : -1;
	d.dy = abs(d.next.y - d.begin.y);
	d.sy = d.begin.y < d.next.y ? 1 : -1;
	dp = (d.dx > d.dy ? d.dx : -1 * d.dy) / 2;
	c = (d.next.c < d.begin.c ? d.next.c : d.begin.c);
	while (d.begin.y != d.next.y || d.begin.x != d.next.x)
	{
		mlx_pixel_put(fdf.init, fdf.win, d.begin.x + d.x0, d.begin.y + d.y0, c);
		if (dp >= -d.dy && d.begin.y != d.next.y)
		{
			dp -= d.dx;
			d.begin.y += d.sy;
		}
		if (dp <= d.dx && d.begin.x != d.next.x)
		{
			dp += d.dy;
			d.begin.x += d.sx;
		}
	}
}

void	fill_point(t_drew *d, t_line *line, t_fdf fdf, int i)
{
	if (i == 0)
	{
		d->begin.x = line->pixel[i].x;
		d->begin.y = (line->pixel[i].y) * fdf.dist;
		d->begin.z = set_alt(line->pixel[i].z, fdf);
		d->begin.c = line->pixel[i].color + fdf.color;
		(fdf.iso ? iso(&d->begin.x, &d->begin.y, d->begin.z) : 1);
	}
	if (i < d->w - 1)
	{
		d->cur.x = line->pixel[i + 1].x * fdf.dist;
		d->cur.y = line->pixel[i + 1].y * fdf.dist;
		d->cur.z = set_alt(line->pixel[i + 1].z, fdf);
		d->cur.c = line->pixel[i + 1].color + fdf.color;
		(fdf.iso ? iso(&d->cur.x, &d->cur.y, d->cur.z) : 1);
	}
	if (line->next)
	{
		d->next.x = line->next->pixel[i].x * fdf.dist;
		d->next.y = line->next->pixel[i].y * fdf.dist;
		d->next.z = set_alt(line->next->pixel[i].z, fdf);
		d->next.c = line->next->pixel[i].color + fdf.color;
		(fdf.iso ? iso(&d->next.x, &d->next.y, d->next.z) : 1);
	}
}

void	menu(t_fdf fdf)
{
	int	i;

	i = -1;
	while (++i < 251)
	{
		mlx_pixel_put(fdf.init, fdf.win, i, fdf.win_h - 210, 0xFF);
		mlx_pixel_put(fdf.init, fdf.win, i, fdf.win_h - 250, 0xFF);
	}
	i = fdf.win_h - 250;
	while (++i < fdf.win_h)
		mlx_pixel_put(fdf.init, fdf.win, 250, i, 0xFF);
	mlx_string_put(fdf.init, fdf.win, 100, fdf.win_h - 240, 0x00FF00, "MENU:");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_h - 190,\
			0x00FF00, "ISO PROJECTION: I");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_h - 160,\
			0x00FF00, "PARALLEL PROJECTION: P");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_h - 130,\
			0x00FF00, "MOVE with ARROWS");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_h - 100,\
			0x00FF00, "ZOOM : + / -");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_h - 70,\
			0x00FF00, "ALTITUDE H / L");
	mlx_string_put(fdf.init, fdf.win, 20, fdf.win_h - 40,\
			0x00FF00, "COLORS: W ^/ S !^/ R -");
}

void	drew_map(t_fdf fdf, t_map *map)
{
	int		i;
	t_drew	d;

	begin_point(&d.x0, &d.y0, fdf);
	d.w = map->width;
	d.tmp = map->line;
	while (d.tmp)
	{
		i = -1;
		while (++i < map->width)
		{
			fill_point(&d, d.tmp, fdf, i);
			drew_h(fdf, d);
			if (d.tmp->next)
				drew_v(fdf, d);
			d.begin = d.cur;
		}
		d.tmp = d.tmp->next;
	}
	menu(fdf);
}
