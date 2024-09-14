/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:44:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/14 11:17:19 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_map(t_map *map, char *line)
{
	if (line != NULL && ft_strlen(line) > 0)
	{
		line[ft_strlen(line) - 1] = '\0';
	}
	map->num_columns = ft_strlen(line);
	map->current_row = 0;
	map->map = (char **)ft_calloc(1, sizeof(char *));
	if (!map->map)
	{
		free(line);
		ft_error(-2);
	}
	map->map[map->current_row++] = line;
}

void	process_map(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	if (!line)
		ft_error(-1);
	initialize_map(map, line);
	count_map_elements(line, map);
	read_lines(map);
	close(map->fd);
	validate_elements(map);
	map->height = map->current_row;
	map->width = map->num_columns;
	validate_walls(map);
	validate_map_walls(map);
	initialize_image_map(map);
	initialize_background_map(map);
}

void	init_char_and_exit(mlx_t *mlx, t_GameData *data, t_map *map,
		int block_size)
{
	t_Position	player_pos;
	t_Position	exit_pos;

	player_pos = find_element(map->map, 'P', map->height, map->width);
	exit_pos = find_element(map->map, 'E', map->height, map->width);
	data->character.image = create_image(mlx, "text/idle.png");
	if (!data->character.image)
	{
		ft_printf("Failed to create player image\n");
		exit(1);
	}
	data->exit.image = create_image(mlx, "text/exit_open.png");
	if (!data->exit.image)
	{
		ft_printf("Failed to create exit image\n");
		exit(1);
	}
	data->character.mlx = mlx;
	data->character.x = player_pos.col * block_size;
	data->character.y = player_pos.row * block_size;
	data->exit.x = exit_pos.col * block_size;
	data->exit.y = exit_pos.row * block_size;
	data->exit.opened = 0;
}

int	load_map(t_map *map, char *file_path)
{
	int			row;

	row = 0;
	map->path = file_path;
	validate_file_extension(map);
	process_map(map);
	while (row < map->height)
	{
		row++;
	}
	return (0);
}

void	allocate_and_initialize_coins(t_GameData *data, t_map *map)
{
	data->coin_count = map->coin_n;
	data->coins = (t_Coin *)ft_calloc(data->coin_count, sizeof(t_Coin));
	if (!data->coins)
	{
		ft_printf("Failed to allocate memory for coins.\n");
		exit(1);
	}
}
