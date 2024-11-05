/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:44:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/11/05 17:56:20 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_map(t_map *map, char *line)
{
	if (line != NULL && ft_strlen(line) > 0)
	{
		line[ft_strlen(line) - 1] = '\0';
	}
	map->num_columns = ft_strlen(line);
	map->current_row = 0;
	map->map = (char **)ft_calloc(1, sizeof(char *));
	if (!map->map)
	{
		free(line);
		ft_error(-2);
	}
	map->map[map->current_row++] = line;
}

void	process_map(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	if (!line)
		ft_error(-1);
	initialize_map(map, line);
	count_map_elements(line, map);
	read_lines(map);
	close(map->fd);
	validate_elements(map);
	map->height = map->current_row;
	map->width = map->num_columns;
	validate_walls(map);
	initialize_image_map(map);
	initialize_background_map(map);
}

int	load_map(t_map *map, char *file_path)
{
	map->path = file_path;
	validate_file_extension(map);
	process_map(map);
	return (0);
}
