/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabouzah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 22:05:39 by nabouzah          #+#    #+#             */
/*   Updated: 2019/11/14 05:23:45 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int				in_base(char c)
{
	char	*lo_base;
	char	*up_base;
	int		i;

	i = 0;
	lo_base = "0123456789abcdef";
	up_base = "0123456789ABCDEF";
	if (c >= 'A' && c <= 'F')
		while (up_base[i] && up_base[i] != c)
			i++;
	else if (c >= 'a' && c <= 'f')
		while (lo_base[i] && lo_base[i] != c)
			i++;
	else if (c >= '0' && c <= '9')
		while (lo_base[i] && lo_base[i] != c)
			i++;
	return (i);
}

int				my_atoi_base(char *s)
{
	int		i;
	int		res;
	int		n;

	i = 0;
	res = 0;
	while (s[i] != ',' && s[i])
		i++;
	if (s[i] && s[i + 1] && s[i + 1] == '0' && s[i + 2] == 'x')
		i += 3;
	while (s[i])
	{
		if ((n = in_base(s[i])) || s[i] == '0')
			res = res * 16 + n;
		else if (s[i] >= '0' && s[i] <= '9')
			res = res * 16 + (s[i] + 48);
		else
			return (0);
		i++;
	}
	return (res);
}

static size_t	wordscount(char const *s, char c)
{
	size_t words;
	size_t i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				i++;
				words++;
			}
		if (s[i])
			i++;
	}
	return (words);
}

static size_t	wordlen(char const *s, size_t i, char c)
{
	size_t len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

char			**split_min(char const *s, char c, int min)
{
	size_t	i;
	size_t	word;
	size_t	chars;
	char	**fresh;

	i = 0;
	if (!(s && (fresh = malloc((wordscount(s, c) + 1) * sizeof(char *)))))
		return (0);
	word = 0;
	while (s[i] && word < (size_t)min)
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			if (!(fresh[word] = malloc((wordlen(s, i, c) + 1) * sizeof(char))))
				return (0);
			chars = 0;
			while (s[i] != c && s[i])
				fresh[word][chars++] = s[i++];
			fresh[word++][chars] = '\0';
		}
	}
	fresh[word] = 0;
	return (fresh);
}
