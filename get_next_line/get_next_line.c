/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:14:09 by fabou-za          #+#    #+#             */
/*   Updated: 2022/03/28 17:40:12 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_null(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		ptr = NULL;
	}
}

static char	*ft_joinline(int nl_position, char **buffer)
{
	char	*res;
	char	*tmp;

	tmp = NULL;
	if (nl_position <= 0)
	{
		if (**buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		res = *buffer;
		*buffer = NULL;
		return (res);
	}
	tmp = ft_substr(*buffer, nl_position, BUFFER_SIZE);
	if (!tmp)
		return (NULL);
	res = *buffer;
	res[nl_position] = 0;
	*buffer = tmp;
	return (res);
}

static char	*single_line(int fd, char **buffer, char *read_return)
{
	ssize_t	bytes_read;
	char	*tmp;
	char	*nl;

	nl = ft_strchr(*buffer, '\n');
	tmp = NULL;
	bytes_read = 0;
	while (nl == NULL)
	{
		bytes_read = read(fd, read_return, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (ft_joinline(bytes_read, buffer));
		read_return[bytes_read] = 0;
		tmp = ft_strjoin(*buffer, read_return);
		if (!tmp)
			return (NULL);
		free_null(buffer);
		*buffer = tmp;
		nl = ft_strchr(*buffer, '\n');
	}
	return (ft_joinline(nl - *buffer + 1, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*read_return;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_return = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (read_return == NULL)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (NULL);
	}
	res = single_line(fd, &buffer, read_return);
	free_null(&read_return);
	return (res);
}
