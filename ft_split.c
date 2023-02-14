/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 00:47:03 by ssadiki           #+#    #+#             */
/*   Updated: 2023/01/27 16:16:11 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_free(char **a)
{
	size_t	i;

	i = 0;
	while (a[i])
	{
		free(a[i++]);
	}
	free(a);
}

static int	ft_size(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count + 1);
}

static char	**ft_splitstr(char **a, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tmp = i;
			while (s[i] != c && s[i])
				i++;
			a[j] = malloc(i - tmp + 1);
			if (!a)
				return (NULL);
			ft_strlcpy(a[j++], s + tmp, i - tmp + 1);
		}
		else
			i++;
	}
	a[j] = NULL;
	return (a);
}

char	**ft_split(char const *s, char c)
{
	char	**a;
//	size_t	i;

//	i = 0;
	if (!s)
		return (NULL);
	a = malloc(sizeof(char *) * ft_size(s, c));
	if (!a)
		return (NULL);
	a = ft_splitstr(a, s, c);
	if (!a)
		ft_free(a);
	return (a);
}
