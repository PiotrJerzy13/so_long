/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:00 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/20 13:51:02 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	setup_game(t_map *map, mlx_t *mlx, t_Resources *res)
{
	mlx_texture_t	*block_tex;

	block_tex = load_texture("text/block1.png");
	if (!block_tex)
	{
		ft_printf("Failed to load block texture\n");
		exit(1);
	}
	res->block_img = create_image(mlx, block_tex);
	if (!res->block_img)
	{
		ft_printf("Failed to create block image\n");
		exit(1);
	}
	render_background_and_walls(mlx, res->images[0], res->block_img, map);
	free(block_tex);
}

void	flood_fill(int row, int col, t_map_data *map_data)
{
	if (row < 0 || col < 0 || row >= map_data->height || col >= map_data->width)
		return ;
	if (map_data->map[row][col] == '1' || map_data->map[row][col] == 'F')
		return ;
	if (map_data->map[row][col] == 'C')
		map_data->reachable_coins++;
	if (map_data->map[row][col] == 'E')
		map_data->exit_reachable = 1;
	map_data->map[row][col] = 'F';
	flood_fill(row - 1, col, map_data);
	flood_fill(row + 1, col, map_data);
	flood_fill(row, col - 1, map_data);
	flood_fill(row, col + 1, map_data);
}

void	count_coins(t_map_data *map_data)
{
	int	row;
	int	col;

	row = 0;
	map_data->total_coins = 0;
	while (row < map_data->height)
	{
		col = 0;
		while (col < map_data->width)
		{
			if (map_data->map[row][col] == 'C')
				map_data->total_coins++;
			col++;
		}
		row++;
	}
}

void	setup_and_validate_game(mlx_t *mlx, t_map *map,
	t_Resources *res, t_GameData *data)
{
	t_map_data	map_data;

	setup_game(map, mlx, res);
	*data = initialize_game_data(mlx, map, res);
	init_char_and_exit(mlx, data, map, BLOCK_SIZE);
	map_data.map = map->map;
	map_data.height = map->height;
	map_data.width = map->width;
	map_flood_fill(&map_data);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_Resources	res;
	mlx_t		*mlx;
	t_GameData	data;

	validate_args_and_load_map(argc, argv, &map);
	mlx = initialize_window(FIXED_WINDOW_WIDTH, FIXED_WINDOW_HEIGHT, "Window");
	if (!mlx)
		ft_error(6);
	load_resources(&res, mlx);
	setup_and_validate_game(mlx, &map, &res, &data);
	iterate_and_populate(mlx, &data, &map);
	render_game_objects(mlx, &data);
	mlx_key_hook(mlx, key_hook, &data);
	mlx_loop(mlx);
	cleanup(mlx, &res);
	free(res.textures);
	free(res.images);
	return (0);
}
