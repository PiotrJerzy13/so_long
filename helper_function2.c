/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:26:17 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/19 12:01:05 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_and_initialize_coins(mlx_t *mlx, t_GameData *data, t_map *map)
{
	data->coin_count = map->c_num;
	data->coins = (t_Coin *)ft_calloc(data->coin_count, sizeof(t_Coin));
	if (!data->coins)
	{
		ft_printf("Failed to allocate memory for coins.\n");
		exit(1);
	}
}

t_GameData	initialize_game_data(mlx_t *mlx, t_map *map, t_Resources *res)
{
	t_GameData	data;
	int			block_size;

	data.mlx = mlx;
	data.map = map;
	data.res = res;
	data.move_count = 0;
	if (mlx->width / map->width > 0)
	{
		block_size = mlx->width / map->width;
	}
	else
	{
		block_size = BLOCK_SIZE;
	}
	init_char_and_exit(mlx, &data, map, block_size);
	allocate_and_initialize_coins(mlx, &data, map);
	iterate_and_populate(mlx, &data, map);
	return (data);
}

void	flood_fill(int row, int col, t_map_data *map_data)
{
	if (map_data->map[row][col] != '1' && map_data->map[row][col] != 'F')
	{
		map_data->map[row][col] = 'F';
		if (row > 0)
			flood_fill(row - 1, col, map_data);
		if (row < map_data->height - 1)
			flood_fill(row + 1, col, map_data);
		if (col > 0)
			flood_fill(row, col - 1, map_data);
		if (col < map_data->width - 1)
			flood_fill(row, col + 1, map_data);
	}
}

void	map_flood_fill(t_map_data *map_data)
{
	int	row;
	int	col;

	row = 0;
	while (row < map_data-> height)
	{
		col = 0;
		while (col < map_data->width)
		{
			if (map_data->map[row][col] == 'P')
			{
				flood_fill(row, col, map_data);
			}
			col++;
		}
		row++;
	}
}

void	validate_file_extension(t_map *map)
{
	if (!has_valid_extension(map->path, ".ber"))
	{
		ft_printf("Error: The map file must end with *.ber!\n");
		exit(1);
	}
	map->fd = open(map->path, O_RDONLY);
	if (map->fd < 0)
	{
		ft_printf("Error: The map data is missing!\n");
		exit(1);
	}
	else if (map->fd == 0)
	{
		ft_printf("Error: The map is empty!\n");
		exit(1);
	}
}
