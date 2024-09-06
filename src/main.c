/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:00 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 14:30:47 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_leaks(void)
{
	system("leaks so_long");
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

	atexit(check_leaks);
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
	free_coins(data.coins, data.coin_count, mlx);
	cleanup_resources(&res, mlx);
	ft_clean(&map);
	return (0);
}
