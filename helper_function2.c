/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:26:17 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/16 15:31:01 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	allocate_and_initialize_coins(mlx_t *mlx, t_GameData *data, t_map *map)
{
	data->coin_count = map->c_num;
	data->coins = (t_Coin *)calloc(data->coin_count, sizeof(t_Coin));
	if (!data->coins)
	{
		fprintf(stderr, "Failed to allocate memory for coins.\n");
		exit(EXIT_FAILURE);
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
