/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:40:36 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 14:45:22 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	free_background_map(t_map *map)
{
	int	i;

	if (!map->background_map)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->background_map[i])
		{
			free(map->background_map[i]);
			map->background_map[i] = NULL;
		}
		i++;
	}
	free(map->background_map);
	map->background_map = NULL;
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
