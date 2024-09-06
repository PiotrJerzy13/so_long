/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:27:40 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 16:28:56 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_if_all(t_Character *character, t_Exit *exit_door, t_GameData *data)
{
	mlx_texture_t	*texture;

	if (all_coins_collected(data))
	{
		if (exit_door->image)
		{
			mlx_delete_image(character->mlx, exit_door->image);
			exit_door->image = NULL;
		}
		texture = mlx_load_png("text/exit_open.png");
		if (!texture)
		{
			ft_printf("Error loading exit texture\n");
			return ;
		}
		exit_door->image = mlx_texture_to_image(character->mlx, texture);
		mlx_delete_texture(texture);
		mlx_image_to_window(character->mlx,
			exit_door->image, exit_door->x, exit_door->y);
		exit_door->opened = 1;
		ft_printf("Exit is open!\n");
	}
}

int	can_move_to(t_map *map, int new_col, int new_row, int exit_opened)
{
	char	target;

	if (new_row < 0 || new_row >= map->height
		|| new_col < 0 || new_col >= map->width)
		return (0);
	target = map->map[new_row][new_col];
	if (target == '1')
		return (0);
	if (target == 'E' && !exit_opened)
		return (0);
	return (1);
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

int	all_coins_collected(t_GameData *data)
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
