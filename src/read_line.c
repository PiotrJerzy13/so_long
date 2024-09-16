/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:26:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/16 15:41:35 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
