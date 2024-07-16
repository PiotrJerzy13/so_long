/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:35:21 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/16 14:23:16 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		printf("CONGLATURATION.\n");
		printf("A WINNER IS YOU.\n");
		mlx_close_window(character->mlx);
	}
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

void	handle_movement(t_GameData *data, int new_col,
		int new_row, int block_size)
{
	t_Character		*character;
	t_Exit			*exit;
	mlx_texture_t	*texture;

	character = &data->character;
	exit = &data->exit;
	if (can_move_to(data->map, new_col, new_row, exit->opened))
	{
		character->x = new_col * block_size;
		character->y = new_row * block_size;
		data->move_count++;
		if (character->image)
		{
			mlx_delete_image(character->mlx, character->image);
		}
		texture = mlx_load_png("text/idle.png");
		character->image = mlx_texture_to_image(character->mlx, texture);
		if (character->image)
		{
			mlx_image_to_window(character->mlx,
				character->image, character->x, character->y);
		}
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
		printf("Moves: %d\n", data->move_count);
		check_coin_collection(data, BLOCK_SIZE);
		check_exit_reached(data);
	}
}
