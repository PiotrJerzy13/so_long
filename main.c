/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:00 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/17 11:18:27 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_t	*initialize_window(int width, int height, const char *title)
{
	mlx_t	*mlx;

	mlx = mlx_init(width, height, title, true);
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize window\n");
		exit(EXIT_FAILURE);
	}
	return (mlx);
}

void	load_resources(t_Resources *res, mlx_t *mlx)
{
	const char	*paths[] = {
		"text/4.png",
		"text/block1.png"
	};

	res->texture_count = 2;
	res->textures = malloc(res->texture_count * sizeof(mlx_texture_t *));
	res->textures[0] = load_texture(paths[0]);
	res->textures[1] = load_texture(paths[1]);
	res->image_count = 2;
	res->images = malloc(res->image_count * sizeof(mlx_image_t *));
	res->images[0] = create_image(mlx, res->textures[0]);
	res->images[1] = create_image(mlx, res->textures[1]);
}

void	setup_game(t_map *map, mlx_t *mlx, t_Resources *res)
{
	mlx_texture_t	*block_tex;

	block_tex = load_texture("text/block1.png");
	if (!block_tex)
	{
		fprintf(stderr, "Failed to load block texture\n");
		exit(EXIT_FAILURE);
	}
	res->block_img = create_image(mlx, block_tex);
	if (!res->block_img)
	{
		fprintf(stderr, "Failed to create block image\n");
		exit(EXIT_FAILURE);
	}
	render_background_and_walls(mlx, res->images[0], res->block_img, map);
	free(block_tex);
}

int	load_map(t_map *map, char *file_path)
{
	size_t	len;

	len = ft_strlen(file_path);
	if (len < 4 || strcmp(file_path + len - 4, ".ber") != 0)
	{
		fprintf(stderr, "Error: Map file must have a .ber extension\n");
		return (-1);
	}
	map->path = file_path;
	validate_file_extension(map);
	process_map(map);
	return (0);
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
		printf("MLX Error: Initialization failed!\n");
		exit(EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}
