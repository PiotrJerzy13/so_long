/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_block_gen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:18:07 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/16 20:48:13 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_image_map(t_map *map)
{
	int	r;
	int	c;

	r = 0;
	c = 0;
	map->img_map = (mlx_image_t ****) calloc(map->height,
			sizeof(mlx_image_t ***));
	if (!map->img_map)
		ft_error(-12, map);
	while (r < map->height)
	{
		map->img_map[r] = (mlx_image_t ***) calloc(map->width,
				sizeof(mlx_image_t **));
		if (!map->img_map[r])
			ft_error(-12, map);
		while (c < map->width)
		{
			map->img_map[r][c] = (mlx_image_t **) calloc(16,
					sizeof(mlx_image_t *));
			if (!map->img_map[r][c])
				ft_error(-12, map);
			c++;
		}
		r++;
	}
}

void	initialize_wall_map(t_map *map)
{
	int	i;

	i = 0;
	map->wall_map = (mlx_image_t ***) calloc(map->height,
			sizeof(mlx_image_t **));
	if (!map->wall_map)
	{
		printf("Memory allocation did not work!\n");
		exit(EXIT_FAILURE);
	}
	while (i < map->height)
	{
		map->wall_map[i] = (mlx_image_t **) calloc(map->width,
				sizeof(mlx_image_t *));
		if (!map->wall_map[i])
		{
			printf("Memory allocation did not work!\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	initialize_background_map(t_map *map)
{
	int	i;

	i = 0;
	map->background_map = (mlx_image_t ***) calloc(map->height,
			sizeof(mlx_image_t **));
	if (!map->background_map)
	{
		printf("Memory allocation did not work!\n");
		exit(EXIT_FAILURE);
	}
	while (i < map->height)
	{
		map->background_map[i] = (mlx_image_t **) calloc(map->width,
				sizeof(mlx_image_t *));
		if (!map->background_map[i])
		{
			printf("Memory allocation did not work!\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	initialize_wall_map(map);
}

void	validate_args_and_load_map(int argc, char **argv, t_map *map)
{
	if (argc < 2)
	{
		printf("Missing map path argument !\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		printf("Too many arguments !\n");
		exit(EXIT_FAILURE);
	}
	*map = (t_map){0};
	if (load_map(map, argv[1]) != 0)
	{
		printf("The map file name must end with *.ber!\n");
		exit(EXIT_FAILURE);
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
