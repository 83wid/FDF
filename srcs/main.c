/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabouzah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:56:54 by nabouzah          #+#    #+#             */
/*   Updated: 2019/11/26 14:12:44 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		unvalid(int error_code, char *s, t_fdf *fdf)
{
	if (fdf)
		freefunc(&fdf->map);
	if (error_code == 0)
		ft_putendl("FOUND WRONG LINE LENGTH. EXITING.");
	else if (error_code == 1)
	{
		ft_putstr("NO FILE ");
		ft_putendl(s);
	}
	else if (error_code == -1)
	{
		ft_putstr("READ ERROR ");
		ft_putstr(s);
		ft_putendl(" ISNT A FILE OR DOESNT EXIST");
	}
	else
		ft_putendl("NO DATA FOUND");
	exit(-1);
}

int		usage(void)
{
	ft_putendl("Usage : ./fdf <filename>");
	return (0);
}

int		main(int c, char **v)
{
	int		fd;
	t_fdf	fdf;
	int		err;
	char	*s;

	if (c != 2)
		return (usage());
	s = ft_strrchr(v[1], '/');
	s = s ? ++s : v[1];
	init_key(&fdf.key);
	if ((fd = open(v[1], O_RDONLY)) < 0)
		unvalid(1, s, NULL);
	if ((err = mapcheck(fd, &fdf.map)) <= 0)
		unvalid(err, s, &fdf);
	project(&fdf, fdf.map, s);
	exit(0);
}
