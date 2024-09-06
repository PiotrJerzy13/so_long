/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coins_initialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:24:23 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 16:12:18 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_coins(t_Coin *coins, int coin_count, mlx_t *mlx)
{
	int	i;

	i = 0;
	while (i < coin_count)
	{
		if (coins[i].image)
		{
			mlx_delete_image(mlx, coins[i].image);
			coins[i].image = NULL;
		}
		i++;
	}
}

int	load_map(t_map *map, char *file_path)
{
	int			row;
	t_Position	player_pos;

	row = 0;
	map->path = file_path;
	validate_file_extension(map);
	process_map(map);
	while (row < map->height)
	{
		row++;
	}
	player_pos = find_element(map->map, 'P', map->height, map->width);
	if (player_pos.row == -1 || player_pos.col == -1)
	{
		ft_printf("Error: Player 'P' not found in the loaded map\n");
		exit(1);
	}
	return (0);
}

void	allocate_and_initialize_coins(t_GameData *data, t_map *map)
{
	data->coin_count = map->coin_n;
	data->coins = (t_Coin *)ft_calloc(data->coin_count, sizeof(t_Coin));
	if (!data->coins)
	{
		ft_printf("Failed to allocate memory for coins.\n");
		exit(1);
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
