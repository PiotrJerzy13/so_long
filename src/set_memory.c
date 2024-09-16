/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:18:07 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/16 16:48:50 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_memory_coins(t_GameData *data, t_map *map)
{
	data->coin_count = map->coin_n;
	data->coins = (t_Coin *)ft_calloc(data->coin_count, sizeof(t_Coin));
	if (!data->coins)
	{
		ft_printf("Failed to allocate memory for coins.\n");
		exit(1);
	}
}

void	allocate_image_map_row(mlx_image_t **row, int width, t_map *map, int r)
{
	int	c;

	c = 0;
	while (c < width)
	{
		row[c] = (mlx_image_t *)ft_calloc(1, sizeof(mlx_image_t *));
		if (!row[c])
		{
			free_image_map(map, r + 1, c);
			ft_error(-2);
		}
		c++;
	}
}

void	initialize_image_map(t_map *map)
{
	int	r;

	r = 0;
	map->img_map = (mlx_image_t ***)ft_calloc(map->height,
			sizeof(mlx_image_t **));
	if (!map->img_map)
		ft_error(-2);
	while (r < map->height)
	{
		map->img_map[r] = (mlx_image_t **)ft_calloc(map->width,
				sizeof(mlx_image_t **));
		if (!map->img_map[r])
		{
			free_image_map(map, r, 0);
			ft_error(-2);
		}
		allocate_image_map_row(map->img_map[r], map->width, map, r);
		r++;
	}
}

void	initialize_wall_map(t_map *map)
{
	int	i;

	i = 0;
	map->wall_map = (mlx_image_t ***) ft_calloc(map->height,
			sizeof(mlx_image_t **));
	if (!map->wall_map)
	{
		ft_printf("Memory allocation did not work!\n");
		exit(1);
	}
	while (i < map->height)
	{
		map->wall_map[i] = (mlx_image_t **) ft_calloc(map->width,
				sizeof(mlx_image_t *));
		if (!map->wall_map[i])
		{
			ft_printf("Memory allocation did not work!\n");
			exit(1);
		}
		i++;
	}
}

void	initialize_background_map(t_map *map)
{
	int	i;

	i = 0;
	map->background_map = (mlx_image_t ***) ft_calloc(map->height,
			sizeof(mlx_image_t *));
	if (!map->background_map)
	{
		ft_printf("Memory allocation did not work!\n");
		exit(1);
	}
	while (i < map->height)
	{
		map->background_map[i] = (mlx_image_t **) ft_calloc(map->width,
				sizeof(mlx_image_t *));
		if (!map->background_map[i])
		{
			ft_printf("Memory allocation did not work!\n");
			free_background_map(map);
			exit(1);
		}
		i++;
	}
	initialize_wall_map(map);
}
