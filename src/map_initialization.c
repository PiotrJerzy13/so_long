/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:44:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 14:44:58 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	calculate_map_dimensions(t_map *map)
{
	char	*line;
	int		fd;

	fd = 0;
	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	fd = open(map->path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Failed to access map data!\n");
		exit(1);
	}
	while (line != NULL)
	{
		if (map->width == 0)
		{
			map->width = ft_strlen(line) - 1;
		}
		map->height++;
		free(line);
	}
	close(fd);
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

void	initialize_map(t_map *map, char *line)
{
	line[ft_strlen(line) - 1] = '\0';
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
