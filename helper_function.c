/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:24:23 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/19 22:06:54 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	update_position(int key, int *new_col, int *new_row)
{
	if (key == MLX_KEY_LEFT)
		(*new_col)--;
	else if (key == MLX_KEY_RIGHT)
		(*new_col)++;
	else if (key == MLX_KEY_UP)
		(*new_row)--;
	else if (key == MLX_KEY_DOWN)
		(*new_row)++;
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

void	check_exit_reached(t_GameData *data)
{
	t_Character	*character;
	t_Exit		*exit;

	character = &data->character;
	exit = &data->exit;
	if (exit->opened && character->x < exit->x + exit->image->width
		&& character->x + character->image->width > exit->x
		&& character->y < exit->y + exit->image->height
		&& character->y + character->image->height > exit->y)
	{
		ft_printf("CONGLATURATION.\n");
		ft_printf("A WINNER IS YOU.\n");
		mlx_close_window(character->mlx);
	}
}
