/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:32:22 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/13 18:13:36 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_img_array(mlx_image_t ***img, const t_map *map)
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

	i = 0;
	if (map->fd != 0)
		close(map->fd);
	if (map->map != NULL)
	{
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

void	free_map_lines(t_map *map, int max_row)
{
	int	i;

	i = 0;
	while (i < max_row)
	{
		if (map->map[i])
			free(map->map[i]);
		i++;
	}
	free(map->map);
}

void	free_image_map(t_map *map, int max_r, int max_c)
{
	int	r;
	int	c;
	int	column_limit;

	r = 0;
	while (r < max_r)
	{
		if (map->img_map[r])
		{
			if (r == max_r - 1)
				column_limit = max_c;
			else
				column_limit = map->width;
			c = 0;
			while (c < column_limit)
			{
				if (map->img_map[r][c])
					free(map->img_map[r][c]);
				c++;
			}
			free(map->img_map[r]);
		}
		r++;
	}
	free(map->img_map);
}
