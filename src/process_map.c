/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:33:53 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 13:12:08 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	cleanup_resources(t_Resources *res, mlx_t *mlx)
{
	int	i;

	i = res->texture_count;
	while (i--)
	{
		if (res->textures[i])
		{
			mlx_delete_texture(res->textures[i]);
			res->textures[i] = NULL;
		}
	}
	free(res->textures);
	res->textures = NULL;
	i = res->image_count;
	while (i--)
	{
		if (res->images[i])
		{
			mlx_delete_image(mlx, res->images[i]);
			res->images[i] = NULL;
		}
	}
	free(res->images);
	res->images = NULL;
}

void	close_window_and_cleanup(mlx_t *mlx, t_Resources *res, t_map *map)
{
	cleanup_resources(res, mlx);
	free_background_map(map);
	mlx_terminate(mlx);
}
