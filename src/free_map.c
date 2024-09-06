/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:32:22 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 14:51:33 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_img_array(mlx_image_t ***img, t_map *map)
{
	int	i;

	if (img == NULL)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (img[i] != NULL)
		{
			free(img[i]);
			img[i] = NULL;
		}
		i++;
	}
	free(img);
	img = NULL;
}

void	free_map_resources(t_map *map)
{
	int	i;

	if (map->fd != 0)
		close(map->fd);
	if (map->map != NULL)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->map[i] != NULL)
			{
				free(map->map[i]);
				map->map[i] = NULL;
			}
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
	free_img_array(map->background_map, map);
	free_img_array(map->wall_map, map);
}

void	free_img_grid(t_map *map)
{
	int	i;
	int	j;

	if (map->img_map == NULL)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->img_map[i] != NULL)
		{
			j = 0;
			while (j < map->width)
			{
				if (map->img_map[i][j] != NULL)
					free(map->img_map[i][j]);
				j++;
			}
			free(map->img_map[i]);
			map->img_map[i] = NULL;
		}
		i++;
	}
	free(map->img_map);
	map->img_map = NULL;
}

void	mlx_clean(t_map *map)
{
	if (map->mlx == NULL)
		return ;
	if (map->mlx->window != NULL)
	{
		mlx_close_window(map->mlx);
		map->mlx->window = NULL;
	}
	mlx_terminate(map->mlx);
	map->mlx = NULL;
}

void	ft_clean(t_map *map)
{
	if (map != NULL)
	{
		free_map_resources(map);
		free_img_grid(map);
		mlx_clean(map);
	}
	exit(0);
}
