/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabouzah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:22:19 by nabouzah          #+#    #+#             */
/*   Updated: 2019/11/26 14:42:58 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include "mlx.h"
# include <math.h>

# define MAX_WIDTH 3200
# define MAX_HEIGHT 1755

typedef struct	s_crl
{
	int		r;
	int		l;
	int		d;
	int		up;
	int		alt_up;
	int		alt_down;
}				t_crl;

typedef struct	s_point
{
	int		x;
	int		y;
	int		z;
	int		c;
}				t_point;

typedef	struct	s_pixel
{
	int		y;
	int		x;
	int		z;
	int		color;
}				t_pixel;

typedef struct	s_line
{
	t_pixel			*pixel;
	struct s_line	*next;
}				t_line;

typedef	struct	s_drew
{
	int		x0;
	int		y0;
	int		w;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	t_point	begin;
	t_point	cur;
	t_point	next;
	t_line	*tmp;
}				t_drew;

typedef struct	s_map
{
	int				width;
	int				height;
	t_line			*line;
}				t_map;

typedef struct	s_fdf
{
	t_map	*map;
	void	*init;
	void	*win;
	int		win_w;
	int		win_h;
	int		dist;
	t_crl	key;
	t_drew	d;
	int		iso;
	int		r;
	int		color;
}				t_fdf;

void			freefunc(t_map **map);

int				mapcheck(const int fd, t_map **map);
int				ft_validate(int fd);

t_line			*newline(char **line, int width, int height);
char			**split_min(char const *s, char c, int min);
int				my_atoi_base(char *s);

void			iso(int *x, int *y, int z);

void			project(t_fdf *fdf, t_map *map, char *title);
void			drew_map(t_fdf fdf, t_map *map);
void			begin_point(int *x, int *y, t_fdf fdf);
void			init_key(t_crl *key);
int				set_alt(int z, t_fdf fdf);
int				key_press(int keycode, t_fdf *fdf);
int				ft_close(t_fdf *fdf);
#endif
