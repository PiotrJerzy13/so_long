/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:45 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/16 14:07:24 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup(mlx_t *mlx, t_Resources *res)
{
	int	i;

	i = 0;
	while (i < res->texture_count)
	{
		mlx_delete_texture(res->textures[i]);
		i++;
	}
	i = 0;
	while (i < res->image_count)
	{
		mlx_delete_image(mlx, res->images[i]);
		i++;
	}
	mlx_terminate(mlx);
}

void	validate_elements(t_map *map)
{
	if (map->current_row < 3 || map->num_columns < 3)
	{
		printf("Map Error: The map is too small!\n");
		exit(EXIT_FAILURE);
	}
	if (map->c_num == 0)
	{
		printf("Map Error: Collectibles are missing from the map!\n");
		exit(EXIT_FAILURE);
	}
	if (map->e_num == 0)
	{
		printf("Map Error: The map requires at least one exit point.\n");
		exit(EXIT_FAILURE);
	}
	if (map->p_num == 0)
	{
		printf("Map Error: The map requires at least one player.\n");
		exit(EXIT_FAILURE);
	}
}

void	validate_map_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		validate_walls(map->map[i], map);
		i++;
	}
}

void	validate_file_extension(t_map *map)
{
	if (!has_valid_extension(map->path, ".ber"))
	{
		printf("The map file name must end with *.ber!\n");
		exit(EXIT_FAILURE);
	}
	map->fd = open(map->path, O_RDONLY);
	if (map->fd < 0)
	{
		printf("Map Error: The map data is missing!\n");
		exit(EXIT_FAILURE);
	}
	else if (map->fd == 0)
	{
		printf("Map Error: The map is empty!\n");
		exit(EXIT_FAILURE);
	}
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
