/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:44:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/08 10:21:47 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_char_and_exit(mlx_t *mlx, t_GameData *data, t_map *map,
		int block_size)
{
	t_Position	player_pos;
	t_Position	exit_pos;

	player_pos = find_element(map->map, 'P', map->height, map->width);
	exit_pos = find_element(map->map, 'E', map->height, map->width);
	data->character.image = create_image(mlx, "text/idle.png");
	if (!data->character.image)
	{
		ft_printf("Failed to create player image\n");
		exit(1);
	}
	data->exit.image = create_image(mlx, "text/exit_open.png");
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

void	initialize_map(t_map *map, char *line)
{
	line[ft_strlen(line) - 1] = '\0';
	map->num_columns = ft_strlen(line);
	map->current_row = 0;
	map->map = (char **)ft_calloc(1, sizeof(char *));
	if (!map->map)
	{
		free(line);
		ft_error(-2);
	}
	map->map[map->current_row++] = line;
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

t_Position	find_element(char **map, char element, int height, int width)
{
	t_Position	pos;
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
