/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:26:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/19 11:33:05 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map_lines(t_map *map)
{
	char	*line;

	map->map = (char **)ft_calloc(1, sizeof(char *));
	if (!map->map)
		ft_error(-2, map);
	line = get_next_line(map->fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) != map->num_columns)
		{
			free(line);
			ft_error(-1, map);
		}
		map->map = (char **)ft_realloc(map->map,
				(map->current_row) * sizeof(char *),
				(map->current_row + 1) * sizeof(char *));
		if (!map->map)
			ft_error(-2, map);
		map->map[map->current_row++] = line;
		count_map_elements(line, map);
		line = get_next_line(map->fd);
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
			exit(1);
		}
		map->map = (char **)ft_realloc(map->map,
				(map->current_row) * sizeof(char *),
				(map->current_row + 1) * sizeof(char *));
		if (!map->map)
		{
			ft_printf("Error: Memory allocation failed!\n");
			exit(1);
		}
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
		exit(1);
	}
	line[ft_strlen(line) - 1] = '\0';
	map->num_columns = ft_strlen(line);
	map->current_row = 0;
	map->map = (char **)ft_calloc(1, sizeof(char *));
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

void	check_map_borders(t_map *game_map)
{
	int	col;

	col = 0;
	while (col < game_map->width)
	{
		if (game_map->map[0][col] != '1')
		{
			ft_printf("Error: The top wall of the map is incomplete!\n");
			exit(1);
			break ;
		}
		col++;
	}
}
