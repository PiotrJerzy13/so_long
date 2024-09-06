/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_block_gen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:18:07 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 12:26:56 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	initialize_image_map(t_map *map)
{
	int	r;
	int	c;

	r = 0;
	map->img_map = (mlx_image_t ****) ft_calloc(map->height,
			sizeof(mlx_image_t ***));
	if (!map->img_map)
		ft_error(-2);
	while (r < map->height)
	{
		map->img_map[r] = (mlx_image_t ***) ft_calloc(map->width,
				sizeof(mlx_image_t **));
		if (!map->img_map[r])
		{
			free_image_map(map, r, 0);
			ft_error(-2);
		}
		c = 0;
		while (c < map->width)
		{
			map->img_map[r][c] = (mlx_image_t **) ft_calloc(16,
					sizeof(mlx_image_t *));
			if (!map->img_map[r][c])
			{
				free_image_map(map, r + 1, c);
				ft_error(-2);
			}
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
			free_background_map(map);
			exit(1);
		}
		i++;
	}
	initialize_wall_map(map);
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
