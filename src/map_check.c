/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:26:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 16:33:26 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_lines(t_map *map, int max_row)
{
	int	i;

	i = 0;
	while (i < max_row)
	{
		if (map->map[i])
			free(map->map[i]);
		i++;
	}
	free(map->map);
}

void	process_line(t_map *map, char *line)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (ft_strlen(line) != (size_t)map->num_columns)
	{
		free(line);
		free_map_lines(map, map->current_row);
		ft_error(-1);
	}
	map->map[map->current_row++] = line;
	count_map_elements(line, map);
}

void	realloc_map(t_map *map)
{
	map->map = (char **)ft_realloc(map->map,
			map->current_row * sizeof(char *),
			(map->current_row + 1) * sizeof(char *));
	if (!map->map)
	{
		free_map_lines(map, map->current_row);
		ft_error(-2);
	}
}

void	read_lines(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	while (line != NULL)
	{
		realloc_map(map);
		process_line(map, line);
		line = get_next_line(map->fd);
	}
}
