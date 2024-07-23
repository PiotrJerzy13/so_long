/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_block_gen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:18:07 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/20 13:52:36 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_image_map(t_map *map)
{
	int	r;
	int	c;

	r = 0;
	c = 0;
	map->img_map = (mlx_image_t ****) ft_calloc(map->height,
			sizeof(mlx_image_t ***));
	if (!map->img_map)
		ft_error(-2);
	while (r < map->height)
	{
		map->img_map[r] = (mlx_image_t ***) ft_calloc(map->width,
				sizeof(mlx_image_t **));
		if (!map->img_map[r])
			ft_error(-2);
		while (c < map->width)
		{
			map->img_map[r][c] = (mlx_image_t **) ft_calloc(16,
					sizeof(mlx_image_t *));
			if (!map->img_map[r][c])
				ft_error(-2);
			c++;
		}
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
			sizeof(mlx_image_t **));
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
			exit(1);
		}
		i++;
	}
	initialize_wall_map(map);
}

void	validate_args_and_load_map(int argc, char **argv, t_map *map)
{
	if (argc < 2)
	{
		ft_printf("Missing map path argument!\n");
		exit(1);
	}
	else if (argc > 2)
	{
		ft_printf("Too many arguments!\n");
		exit(1);
	}
	*map = (t_map){0};
	if (load_map(map, argv[1]) != 0)
	{
		ft_printf("Error loading the map!\n");
		exit(1);
	}
}

int	can_move_to(t_map *map, int new_col, int new_row, int exit_opened)
{
	char	target;

	if (new_row < 0 || new_row >= map->height
		|| new_col < 0 || new_col >= map->width)
		return (0);
	target = map->map[new_row][new_col];
	if (target == '1')
		return (0);
	if (target == 'E' && !exit_opened)
		return (0);
	return (1);
}
