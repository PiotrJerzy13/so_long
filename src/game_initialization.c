/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:36:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 14:52:16 by pwojnaro         ###   ########.fr       */
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

mlx_image_t	*create_image(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = load_texture(path);
	if (!texture)
	{
		ft_printf("Failed to load texture: %s\n", path);
		exit(1);
	}
	image = mlx_texture_to_image(mlx, texture);
	if (!image)
	{
		ft_printf("Failed to convert texture to image\n");
		mlx_delete_texture(texture);
		exit(1);
	}
	mlx_delete_texture(texture);
	return (image);
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

t_GameData	initialize_game_data(mlx_t *mlx, t_map *map, t_Resources *res)
{
	t_GameData	data;
	int			block_size;

	data.mlx = mlx;
	data.map = map;
	data.res = res;
	data.move_count = 0;
	block_size = BLOCK_SIZE;
	init_char_and_exit(mlx, &data, map, block_size);
	allocate_and_initialize_coins(&data, map);
	iterate_and_populate(mlx, &data, map);
	return (data);
}
