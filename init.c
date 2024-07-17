/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:36:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/16 18:16:42 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_texture_t	*load_texture(const char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		fprintf(stderr, "Failed to load texture: %s\n", path);
		exit(EXIT_FAILURE);
	}
	return (texture);
}

mlx_image_t	*create_image(mlx_t *mlx, mlx_texture_t *texture)
{
	mlx_image_t	*image;

	image = mlx_texture_to_image(mlx, texture);
	if (!image)
	{
		fprintf(stderr, "Failed to convert texture to image\n");
		exit(EXIT_FAILURE);
	}
	return (image);
}

void	init_char_and_exit(mlx_t *mlx,
	t_GameData *data, t_map *map, int block_size)
{
	t_Position	player_pos;
	t_Position	exit_pos;

	player_pos = find_element(map->map, 'P', map->height, map->width);
	exit_pos = find_element(map->map, 'E', map->height, map->width);
	data->character.image = create_image(mlx, load_texture("text/idle.png"));
	if (!data->character.image)
	{
		fprintf(stderr, "Failed to load character image\n");
		exit(EXIT_FAILURE);
	}
	data->exit.image = create_image(mlx, load_texture("text/exit_open.png"));
	if (!data->exit.image)
	{
		fprintf(stderr, "Failed to load exit image\n");
		exit(EXIT_FAILURE);
	}
	data->character.mlx = mlx;
	data->character.x = player_pos.col * BLOCK_SIZE;
	data->character.y = player_pos.row * BLOCK_SIZE;
	data->exit.x = exit_pos.col * BLOCK_SIZE;
	data->exit.y = exit_pos.row * BLOCK_SIZE;
	data->exit.opened = 0;
}
