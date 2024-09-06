/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:33:53 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 16:19:45 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	validate_map_walls(map);
	initialize_image_map(map);
	initialize_background_map(map);
}

void	count_coins(t_map_data *map_data)
{
	int	row;
	int	col;

	row = 0;
	map_data->total_coins = 0;
	while (row < map_data->height)
	{
		col = 0;
		while (col < map_data->width)
		{
			if (map_data->map[row][col] == 'C')
				map_data->total_coins++;
			col++;
		}
		row++;
	}
}

void	perform_flood_fill(t_map_data *map_data)
{
	int	row;
	int	col;

	row = 0;
	map_data->reachable_coins = 0;
	map_data->exit_reachable = 0;
	while (row < map_data->height)
	{
		col = 0;
		while (col < map_data->width)
		{
			if (map_data->map[row][col] == 'P')
			{
				flood_fill(row, col, map_data);
				return ;
			}
			col++;
		}
		row++;
	}
}

void	map_flood_fill(t_map_data *map_data)
{
	count_coins(map_data);
	perform_flood_fill(map_data);
	if (!(map_data->reachable_coins == map_data->total_coins
			&& map_data->exit_reachable))
	{
		ft_printf("Map is invalid.\n");
		exit(1);
	}
}

void	flood_fill(int row, int col, t_map_data *map_data)
{
	if (row < 0 || col < 0 || row >= map_data->height || col >= map_data->width)
		return ;
	if (map_data->map[row][col] == '1' || map_data->map[row][col] == 'F')
		return ;
	if (map_data->map[row][col] == 'C')
		map_data->reachable_coins++;
	if (map_data->map[row][col] == 'E')
		map_data->exit_reachable = 1;
	map_data->map[row][col] = 'F';
	flood_fill(row - 1, col, map_data);
	flood_fill(row + 1, col, map_data);
	flood_fill(row, col - 1, map_data);
	flood_fill(row, col + 1, map_data);
}
