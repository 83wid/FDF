/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabouzah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:53:38 by nabouzah          #+#    #+#             */
/*   Updated: 2019/11/23 08:18:23 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_pixel	*fill_pixel(char **line, int width, int height)
{
	int		i;
	t_pixel	*pixel;
	int		color;

	i = 0;
	if (!(pixel = (t_pixel *)malloc(sizeof(t_pixel) * width)))
		return (NULL);
	while (line[i] && i < width)
	{
		pixel[i].y = height - 1;
		pixel[i].x = i;
		pixel[i].z = ft_atoi(line[i]);
		color = my_atoi_base(line[i]);
		pixel[i].color = (!color ? 0xFFFFFF : color);
		pixel[i].color = (!color && pixel[i].z ?\
				0xFFFFF / abs(pixel[i].z) + 200 : pixel[i].color);
		i++;
	}
	return (pixel);
}

t_line	*newline(char **line, int width, int height)
{
	t_line	*new;

	if (!(new = (t_line *)malloc(sizeof(t_line))) ||\
			!(new->pixel = fill_pixel(line, width, height)))
		return (NULL);
	new->next = NULL;
	return (new);
}
