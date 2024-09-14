/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:33:53 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/14 11:11:37 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	iterate_and_populate(mlx_t *mlx, t_GameData *data, t_map *map)
{
	int	row;
	int	col;
	int	coin_index;

	row = 0;
	col = 0;
	coin_index = 0;
	while (row < map->height)
	{
		while (col < map->width)
		{
			if (map->map[row][col] == 'C')
			{
				initialize_coin(mlx, &data->coins[coin_index],
					col * BLOCK_SIZE, row * BLOCK_SIZE);
				coin_index++;
			}
			col++;
		}
		col = 0;
		row++;
	}
}
