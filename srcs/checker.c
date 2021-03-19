/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabouzah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:10:10 by nabouzah          #+#    #+#             */
/*   Updated: 2019/11/23 08:06:56 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			elemnbr(char **line)
{
	int		i;

	i = 0;
	while (line && line[i])
		i++;
	return (i);
}

int			free_leak(char ***elem, char **step)
{
	int		i;
	int		err;

	i = -1;
	err = 0;
	if (step && *step)
	{
		if (!**step)
			err = -2;
		free(*step);
		*step = NULL;
	}
	if (elem && *elem)
	{
		while ((*elem)[++i])
			free((*elem)[i]);
		free(*elem);
		*elem = NULL;
	}
	return (err);
}

void		freefunc(t_map **map)
{
	t_line	*tmp;

	if (map && *map)
	{
		while ((*map)->line)
		{
			tmp = (*map)->line->next;
			free((*map)->line->pixel);
			free((*map)->line);
			(*map)->line = tmp;
		}
		free(*map);
		*map = NULL;
	}
}

int			fill_line(const int fd, t_line **line, int *width, int *height)
{
	char	*step;
	char	**elem;
	t_line	*tmp;
	int		ret;

	while ((ret = get_next_line(fd, &step)) > 0 && ++(*height))
	{
		if (!*line && (elem = ft_strsplit(step, ' ')))
		{
			*width = elemnbr(elem);
			*line = newline(elem, *width, *height);
			tmp = *line;
		}
		else
		{
			elem = split_min(step, 32, *width);
			tmp->next = newline(elem, *width, *height);
			tmp = tmp->next;
		}
		if (!tmp || elemnbr(elem) < *width || !*step)
			return (free_leak(&elem, &step));
		free_leak(&elem, &step);
	}
	free_leak(&elem, &step);
	return (ret < 0 ? ret : 1);
}

int			mapcheck(const int fd, t_map **map)
{
	int		width;
	int		height;
	t_line	*tmp;
	int		err;

	height = 0;
	width = 0;
	err = 0;
	if (!(*map = (t_map*)malloc(sizeof(t_map))) ||\
			(err = fill_line(fd, &tmp, &width, &height)) <= 0)
	{
		freefunc(map);
		return (err);
	}
	(*map)->line = tmp;
	(*map)->width = width;
	(*map)->height = height;
	return (1);
}
