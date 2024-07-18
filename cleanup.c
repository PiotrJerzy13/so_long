/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:45 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/18 23:40:28 by pwojnaro         ###   ########.fr       */
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
		ft_printf("Error: The map is too small!\n");
		exit(1);
	}
	if (map->c_num == 0)
	{
		ft_printf("Error: Collectibles are missing from the map!\n");
		exit(1);
	}
	if (map->e_num == 0)
	{
		ft_printf("Map Error: The map requires at least one exit point.\n");
		exit(1);
	}
	if (map->p_num == 0)
	{
		ft_printf("Map Error: The map requires at least one player.\n");
		exit(1);
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
		ft_printf("Error: The map file must end with *.ber!\n");
		exit(1);
	}
	map->fd = open(map->path, O_RDONLY);
	if (map->fd < 0)
	{
		ft_printf("Error: The map data is missing!\n");
		exit(1);
	}
	else if (map->fd == 0)
	{
		ft_printf("Error: The map is empty!\n");
		exit(1);
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
