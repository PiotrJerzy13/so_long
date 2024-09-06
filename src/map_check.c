/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:26:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 11:34:46 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->current_row)
	{
		if (map->map[i])
			free(map->map[i]);
		i++;
	}
	free(map->map);
}

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

void	add_line_to_map(char *line, t_map *map)
{
	char	**new_map;

	new_map = (char **)ft_realloc(map->map,
			(map->current_row) * sizeof(char *),
			(map->current_row + 1) * sizeof(char *));
	if (!new_map)
	{
		free(line);
		ft_error(-2);
	}
	map->map = new_map;
	map->map[map->current_row++] = line;
	count_map_elements(line, map);
}

void	read_lines(t_map *map)
{
	char	*line;
	size_t	line_length;

	line = get_next_line(map->fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		line_length = ft_strlen(line);
		if (line_length != (size_t)map->num_columns)
		{
			free(line);
			free_map_lines(map, map->current_row);
		}
		map->map = (char **)ft_realloc(map->map,
				(map->current_row) * sizeof(char *),
				(map->current_row + 1) * sizeof(char *));
		if (!map->map)
		{
			free(line);
			free_map_lines(map, map->current_row);
			ft_error(2);
		}
		map->map[map->current_row++] = line;
		count_map_elements(line, map);
		line = get_next_line(map->fd);
	}
}

void	count_map_elements(char *line, t_map *map)
{
	while (*line)
	{
		if (*line == 'C')
			map->coin_n++;
		else if (*line == 'P')
		{
			map->player_n++;
			if (map->player_n > 1)
				ft_error(-3);
		}
		else if (*line == 'E')
		{
			map->exit_n++;
			if (map->exit_n > 1)
				ft_error(-4);
		}
		else if (*line == '1')
			map->wall_n++;
		else if (*line == '0')
			;
		else
			ft_error(-5);
		line++;
	}
}
