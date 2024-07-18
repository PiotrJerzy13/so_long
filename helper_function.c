/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:24:23 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/18 22:18:16 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_if_all(t_Character *character, t_Exit *exit_door, t_GameData *data)
{
	if (all_coins_collected(data))
	{
		mlx_delete_image(character->mlx, exit_door->image);
		exit_door->image = mlx_texture_to_image(character->mlx,
				mlx_load_png("text/exit_open.png"));
		mlx_image_to_window(character->mlx,
			exit_door->image, exit_door->x, exit_door->y);
		exit_door->opened = 1;
	}
}

void	check_and_collect_coin(t_Character *character, t_Coin *coin)
{
	if (!coin->collected && character->x == coin->x && character->y == coin->y)
	{
		mlx_delete_image(character->mlx, coin->image);
		coin->collected = 1;
	}
}

void	check_coin_collection(t_GameData *data, int block_size)
{
	t_Character	*character;
	t_Coin		*coin;
	t_Exit		*exit_door;
	int			i;

	character = &data->character;
	coin = data->coins;
	exit_door = &data->exit;
	i = 0;
	while (i < data->coin_count)
	{
		check_and_collect_coin(character, &coin[i]);
		i++;
	}
	exit_if_all(character, exit_door, data);
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

void	initialize_coin(mlx_t *mlx, t_Coin *coin, int x, int y)
{
	coin->image = create_image(mlx, load_texture("text/coin.png"));
	if (!coin->image)
	{
		ft_printf("Failed to load coin image\n");
		exit(1);
	}
	coin->x = x;
	coin->y = y;
	coin->collected = 0;
}
