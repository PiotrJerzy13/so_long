/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:39:29 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/16 18:04:19 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_position	find_element(char **map, char element, int height, int width)
{
	t_position	pos;
	int			row;
	int			col;

	pos.row = -1;
	pos.col = -1;
	row = 0;
	while (row < height)
	{
		col = 0;
		while (col < width)
		{
			if (map[row][col] == element)
			{
				pos.row = row;
				pos.col = col;
				return (pos);
			}
			col++;
		}
		row++;
	}
	return (pos);
}

void	load_text_to_array(t_resources *res, mlx_t *mlx)
{
	const char	*paths[] = {"text/4.png", "text/block1.png"};
	int			i;

	i = 0;
	res->texture_count = 2;
	res->image_count = 2;
	res->textures = malloc(res->texture_count * sizeof(mlx_texture_t *));
	res->images = malloc(res->image_count * sizeof(mlx_image_t *));
	if (!res->textures || !res->images)
		exit(1);
	while (i < res->texture_count)
	{
		res->textures[i] = load_texture(paths[i]);
		if (!res->textures[i])
			handle_error_cleanup(res, mlx, i, 1);
		i++;
	}
	i = 0;
	while (i < res->image_count)
	{
		res->images[i] = create_image(mlx, paths[i]);
		if (!res->images[i])
			handle_error_cleanup(res, mlx, i, 0);
		i++;
	}
}

void	initialize_single_coin(mlx_t *mlx, t_coin *coin, int x, int y)
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

void	fill_coins_on_map(mlx_t *mlx, t_game_data *data, t_map *map)
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
				initialize_single_coin(mlx, &data->coins[coin_index],
					col * BLOCK_SIZE, row * BLOCK_SIZE);
				coin_index++;
			}
			col++;
		}
		col = 0;
		row++;
	}
}

void	load_char_and_exit(mlx_t *mlx, t_game_data *data, t_map *map,
		int block_size)
{
	t_position	player_pos;
	t_position	exit_pos;

	player_pos = find_element(map->map, 'P', map->height, map->width);
	exit_pos = find_element(map->map, 'E', map->height, map->width);
	data->character.image = create_image(mlx, "text/idle.png");
	if (!data->character.image)
	{
		ft_printf("Failed to create player image\n");
		exit(1);
	}
	data->exit.image = create_image(mlx, "text/exit.png");
	if (!data->exit.image)
	{
		ft_printf("Failed to create exit image\n");
		exit(1);
	}
	data->character.mlx = mlx;
	data->character.x = player_pos.col * block_size;
	data->character.y = player_pos.row * block_size;
	data->exit.x = exit_pos.col * block_size;
	data->exit.y = exit_pos.row * block_size;
	data->exit.opened = 0;
}
