/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:36:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/19 21:56:12 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_t	*initialize_window(int width, int height, const char *title)
{
	mlx_t	*mlx;

	mlx = mlx_init(width, height, title, true);
	if (!mlx)
	{
		ft_printf("Failed to initialize window\n");
		exit(1);
	}
	return (mlx);
}

mlx_texture_t	*load_texture(const char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_printf("Failed to load texture: %s\n", path);
		exit(1);
	}
	return (texture);
}

mlx_image_t	*create_image(mlx_t *mlx, mlx_texture_t *texture)
{
	mlx_image_t	*image;

	image = mlx_texture_to_image(mlx, texture);
	if (!image)
	{
		ft_printf("Failed to convert texture to image\n");
		exit(1);
	}
	return (image);
}

void	init_char_and_exit(mlx_t *mlx, t_GameData *data,
		t_map *map, int block_size)
{
	t_Position	player_pos;
	t_Position	exit_pos;

	player_pos = find_element(map->map, 'P', map->height, map->width);
	exit_pos = find_element(map->map, 'E', map->height, map->width);
	data->character.image = create_image(mlx, load_texture("text/idle.png"));
	if (!data->character.image)
	{
		ft_printf("Failed to load character image\n");
		exit(1);
	}
	data->exit.image = create_image(mlx, load_texture("text/exit_open.png"));
	if (!data->exit.image)
	{
		ft_printf("Failed to load exit image\n");
		exit(1);
	}
	data->character.mlx = mlx;
	data->character.x = player_pos.col * block_size;
	data->character.y = player_pos.row * block_size;
	data->exit.x = exit_pos.col * block_size;
	data->exit.y = exit_pos.row * block_size;
	data->exit.opened = 0;
}

void	load_resources(t_Resources *res, mlx_t *mlx)
{
	const char	*paths[] = {
		"text/4.png",
		"text/block1.png"
	};

	res->texture_count = 2;
	res->textures = malloc(res->texture_count * sizeof(mlx_texture_t *));
	res->textures[0] = load_texture(paths[0]);
	res->textures[1] = load_texture(paths[1]);
	res->image_count = 2;
	res->images = malloc(res->image_count * sizeof(mlx_image_t *));
	res->images[0] = create_image(mlx, res->textures[0]);
	res->images[1] = create_image(mlx, res->textures[1]);
}
