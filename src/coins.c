/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coins.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:24:23 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/11/05 18:32:32 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_and_delete_coin(t_character *character, t_coin *coin)
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

void	check_coin_collection(t_game_data *data)
{
	t_character	*character;
	t_coin		*coin;
	int			i;

	character = &data->character;
	coin = data->coins;
	i = 0;
	while (i < data->coin_count)
	{
		check_and_delete_coin(character, &coin[i]);
		i++;
	}
	check_exit_reached(data);
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

int	all_coins_collected(const t_game_data *data)
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
