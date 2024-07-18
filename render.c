/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:51:03 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/18 22:15:35 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_background(mlx_t *mlx, mlx_image_t *background_img)
{
	int	x;
	int	y;

	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			mlx_image_to_window(mlx, background_img, x, y);
			x += background_img->width;
		}
		y += background_img->height;
	}
}

void	render_walls(mlx_t *mlx, mlx_image_t *block_img, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == '1')
			{
				mlx_image_to_window(mlx, block_img, x * block_img->width,
					y * block_img->height);
			}
			x++;
		}
		y++;
	}
}

void	render_background_and_walls(mlx_t *mlx, mlx_image_t *background_img,
	mlx_image_t *block_img, t_map *map)
{
	render_background(mlx, background_img);
	render_walls(mlx, block_img, map);
}

void	render_game_objects(mlx_t *mlx, t_GameData *data)
{
	int	i;

	mlx_image_to_window(mlx, data->character.image,
		data->character.x, data->character.y);
	mlx_image_to_window(mlx, data->exit.image, data->exit.x, data->exit.y);
	i = 0;
	while (i < data->coin_count)
	{
		if (!data->coins[i].collected)
		{
			mlx_image_to_window(mlx, data->coins[i].image,
				data->coins[i].x, data->coins[i].y);
		}
		i++;
	}
}

void	calculate_map_dimensions(t_map *map)
{
	char	*line;
	int		fd;

	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	fd = open(map->path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Failed to access map data!\n");
		exit(1);
	}
	while (line != NULL)
	{
		if (map->width == 0)
		{
			map->width = ft_strlen(line) - 1;
		}
		map->height++;
		free(line);
	}
	close(fd);
}
