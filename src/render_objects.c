/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:51:03 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/16 17:53:56 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_block(t_map *map, mlx_t *mlx, t_resources *res)
{
	res->block_img = create_image(mlx, "text/block1.png");
	if (!res->block_img)
	{
		ft_printf("Failed to create block image\n");
		exit(1);
	}
	render_background_and_walls(mlx, res->images[0], res->block_img, map);
}

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

void	render_walls(mlx_t *mlx, mlx_image_t *block_img, const t_map *map)
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

void	render_game_objects(mlx_t *mlx, t_game_data *data)
{
	int	i;

	if (data->character.image)
	{
		mlx_image_to_window(mlx, data->character.image,
			data->character.x, data->character.y);
	}
	if (data->exit.image)
		mlx_image_to_window(mlx, data->exit.image, data->exit.x, data->exit.y);
	i = 0;
	while (i < data->coin_count)
	{
		if (!data->coins[i].collected && data->coins[i].image)
		{
			mlx_image_to_window(mlx, data->coins[i].image,
				data->coins[i].x, data->coins[i].y);
		}
		i++;
	}
}
