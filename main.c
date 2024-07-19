/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:00 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/19 12:07:45 by pwojnaro         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_map		map;
	t_Resources	res;
	mlx_t		*mlx;
	t_GameData	data;

	validate_args_and_load_map(argc, argv, &map);
	mlx = initialize_window(FIXED_WINDOW_WIDTH, FIXED_WINDOW_HEIGHT, "Window");
	if (!mlx)
	{
		ft_printf("Error: Initialization failed!\n");
		exit(1);
	}
	load_resources(&res, mlx);
	setup_game(&map, mlx, &res);
	data = initialize_game_data(mlx, &map, &res);
	init_char_and_exit(mlx, &data, &map, BLOCK_SIZE);
	iterate_and_populate(mlx, &data, &map);
	render_game_objects(mlx, &data);
	mlx_key_hook(mlx, key_hook, &data);
	mlx_loop(mlx);
	cleanup(mlx, &res);
	free(res.textures);
	free(res.images);
	return (0);
}
