/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:24:58 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/09 09:26:17 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		check_and_collect_coin(character, &coin[i]);
		i++;
	}
	exit_if_all(character, exit_door, data);
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

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_GameData	*data;
	t_Character	*character;
	int			new_col;
	int			new_row;

	data = (t_GameData *)param;
	character = &data->character;
	new_col = character->x / BLOCK_SIZE;
	new_row = character->y / BLOCK_SIZE;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(character->mlx);
	}
	else if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		update_position(keydata.key, &new_col, &new_row);
		handle_movement(data, new_col, new_row, BLOCK_SIZE);
		ft_printf("Moves: %d\n", data->move_count);
		check_coin_collection(data);
		check_exit_reached(data);
	}
}

void	handle_movement(t_GameData *data, int new_col, int new_row,
	int block_size)
{
	t_Character		*character;
	mlx_texture_t	*texture;

	character = &data->character;
	if (!can_move_to(data->map, new_col, new_row, data->exit.opened))
		return ;
	character->x = new_col * block_size;
	character->y = new_row * block_size;
	data->move_count++;
	if (character->image)
		mlx_delete_image(character->mlx, character->image);
	texture = mlx_load_png("text/idle.png");
	if (texture)
	{
		character->image = mlx_texture_to_image(character->mlx, texture);
		if (character->image)
			mlx_image_to_window(character->mlx, character->image, character->x,
				character->y);
		else
			ft_printf("Error converting texture to image\n");
		mlx_delete_texture(texture);
	}
	else
		ft_printf("Error loading character texture\n");
}
