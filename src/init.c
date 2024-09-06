/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:36:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 13:51:54 by pwojnaro         ###   ########.fr       */
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

void	free_textures(mlx_texture_t **textures, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (textures[i])
			mlx_delete_texture(textures[i]);
		i++;
	}
}

void	free_images(mlx_t *mlx, mlx_image_t **images, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (images[i])
			mlx_delete_image(mlx, images[i]);
		i++;
	}
}

void	handle_error_cleanup(t_Resources *res, mlx_t *mlx, int count,
	int is_texture)
{
	int	j;

	j = 0;
	if (is_texture)
	{
		while (j < count)
			mlx_delete_texture(res->textures[j++]);
		free(res->textures);
	}
	else
	{
		while (j < count)
			mlx_delete_image(mlx, res->images[j++]);
		free(res->images);
		free_textures(res->textures, res->texture_count);
		free(res->textures);
	}
	exit(1);
}

void	load_resources(t_Resources *res, mlx_t *mlx)
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
