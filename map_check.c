/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:26:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/18 18:41:49 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	has_valid_extension(const char *path, const char *extension)
{
	int			path_len;
	int			ext_len;
	const char	*path_ext;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(extension);
	if (path_len < ext_len)
		return (0);
	path_ext = path + path_len - ext_len;
	while (*extension)
	{
		if (*path_ext != *extension)
			return (0);
		path_ext++;
		extension++;
	}
	return (1);
}

void	read_map_lines(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	map->map = (char **)calloc(1, sizeof(char *));
	map->current_row = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) != map->num_columns)
		{
			ft_printf("Error: The map is not rectangular!\n");
			free(line);
			exit(EXIT_FAILURE);
		}
		map->map = (char **)realloc(map->map,
				(map->current_row + 1) * sizeof(char *));
		map->map[map->current_row++] = line;
		count_map_elements(line, map);
	}
	free(line);
}

void	count_map_elements(char *line, t_map *map)
{
	while (*line)
	{
		if (*line == 'C')
			map->c_num++;
		else if (*line == 'P')
			map->p_num++;
		else if (*line == 'E')
			map->e_num++;
		else if (*line == '1')
			map->w_num++;
		line++;
	}
}

void	read_lines(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) != map->num_columns)
		{
			ft_printf("Error: The map is not rectangular!\n");
			free(line);
			exit(EXIT_FAILURE);
		}
		map->map = (char **)realloc(map->map,
				(map->current_row + 1) * sizeof(char *));
		map->map[map->current_row++] = line;
		count_map_elements(line, map);
		line = get_next_line(map->fd);
	}
}

void	process_map(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	if (!line)
	{
		ft_printf("Error: The map data is empty!\n");
		exit(EXIT_FAILURE);
	}
	line[ft_strlen(line) - 1] = '\0';
	map->num_columns = ft_strlen(line);
	map->current_row = 0;
	map->map = (char **)calloc(1, sizeof(char *));
	map->map[map->current_row++] = line;
	count_map_elements(line, map);
	read_lines(map);
	close(map->fd);
	validate_elements(map);
	map->height = map->current_row;
	map->width = map->num_columns;
	validate_map_walls(map);
	initialize_image_map(map);
	initialize_background_map(map);
}
