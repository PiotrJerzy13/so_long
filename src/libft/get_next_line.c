/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:10:01 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/13 10:31:45 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_and_store(int fd, int *bytes_read, char *line)
{
	char	*storage;

	if (!line)
	{
		line = ft_calloc(1, sizeof(char));
		if (!line)
			return (NULL);
	}
	storage = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!storage)
		return (free(line), NULL);
	while (*bytes_read > 0)
	{
		if (read_from_fd(fd, storage, bytes_read) == -1)
			return (free(storage), free(line), NULL);
		line = store_and_join(line, storage);
		if (!line)
			return (free(storage), NULL);
		if (ft_strchr(storage, '\n'))
			break ;
	}
	free(storage);
	return (line);
}

int	end_of_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	return (i);
}

char	*get_result(const char *line, int bytes_read)
{
	char	*result;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	result = ft_calloc(bytes_read + 2, sizeof(char));
	if (!result)
		return (NULL);
	while (line[i] != '\n' && line[i])
	{
		result[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		result[i] = '\n';
	return (result);
}

char	*allocate_new_line(char *line, int bytes_read)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!line[bytes_read])
	{
		free(line);
		return (NULL);
	}
	new_line = ft_calloc(ft_strlen(line) - bytes_read + 1, sizeof(char));
	if (!new_line)
		return (free(line), NULL);
	bytes_read++;
	while (line[bytes_read])
	{
		new_line[i] = line[bytes_read];
		i++;
		bytes_read++;
	}
	free(line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*result;
	int			bytes_read;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (NULL);
	}
	line = read_and_store(fd, &bytes_read, line);
	if (!line)
		return (NULL);
	bytes_read = end_of_line(line);
	result = get_result(line, bytes_read);
	line = allocate_new_line(line, bytes_read);
	return (result);
}
