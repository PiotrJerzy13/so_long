/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:00 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:54 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_leaks(void)
{
	system("leaks so_long");
}

t_GameData	initialize_game_data(mlx_t *mlx, t_map *map, t_Resources *res)
{
	t_GameData	data;
	int			block_size;

	data.mlx = mlx;
	data.map = map;
	data.res = res;
	data.move_count = 0;
	block_size = BLOCK_SIZE;
	load_char_and_exit(mlx, &data, map, block_size);
	allocate_memory_coins(&data, map);
	fill_coins_on_map(mlx, &data, map);
	return (data);
}

void	setup_game(t_map *map, mlx_t *mlx, t_Resources *res)
{
	res->block_img = create_image(mlx, "text/block1.png");
	if (!res->block_img)
	{
		ft_printf("Failed to create block image\n");
		exit(1);
	}
	render_background_and_walls(mlx, res->images[0], res->block_img, map);
}

void	setup_and_validate_game(mlx_t *mlx, t_map *map,
	t_Resources *res, t_GameData *data)
{
	t_map_data	map_data;

	setup_game(map, mlx, res);
	*data = initialize_game_data(mlx, map, res);
	load_char_and_exit(mlx, data, map, BLOCK_SIZE);
	map_data.map = map->map;
	map_data.height = map->height;
	map_data.width = map->width;
	start_flood_fill(&map_data);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_Resources	res;
	mlx_t		*mlx;
	t_GameData	data;

	atexit(check_leaks);
	validate_args_and_load_map(argc, argv, &map);
	mlx = initialize_window(FIXED_WINDOW_WIDTH, FIXED_WINDOW_HEIGHT, "Window");
	if (!mlx)
		ft_error(6);
	load_text_to_array(&res, mlx);
	setup_and_validate_game(mlx, &map, &res, &data);
	fill_coins_on_map(mlx, &data, &map);
	render_game_objects(mlx, &data);
	mlx_key_hook(mlx, key_hook, &data);
	mlx_loop(mlx);
	free_coins(data.coins, data.coin_count, mlx);
	cleanup_resources(&res, mlx);
	ft_clean(&map);
	return (0);
}
