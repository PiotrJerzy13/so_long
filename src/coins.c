/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coins.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:24:23 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/14 10:56:17 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_coin(mlx_t *mlx, t_Coin *coin, int x, int y)
{
	coin->image = create_image(mlx, "text/coin.png");
	if (!coin->image)
	{
		ft_printf("Failed to load coin image\n");
		exit(1);
	}
	coin->x = x;
	coin->y = y;
	coin->collected = 0;
}

void	check_and_delete_coin(t_Character *character, t_Coin *coin)
{
	if (!coin->collected && character->x == coin->x && character->y == coin->y)
	{
		if (coin->image)
		{
			mlx_delete_image(character->mlx, coin->image);
			coin->image = NULL;
		}
		coin->collected = 1;
	}
}

void	check_coin_collection(t_GameData *data)
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
		check_and_delete_coin(character, &coin[i]);
		i++;
	}
	exit_if_all(character, exit_door, data);
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

int	all_coins_collected(const t_GameData *data)
{
	int	i;

	i = 0;
	while (i < data->coin_count)
	{
		if (!data->coins[i].collected)
			return (0);
		i++;
	}
	return (1);
}