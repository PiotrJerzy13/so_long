/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:33:53 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 11:39:11 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	process_map(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	if (!line)
	{
		ft_printf("Error: The map data is empty!\n");
		exit(1);
	}
	line[ft_strlen(line) - 1] = '\0';
	map->num_columns = ft_strlen(line);
	map->current_row = 0;
	map->map = (char **)ft_calloc(1, sizeof(char *));
	if (!map->map)
	{
		free(line);
		ft_printf("Error: Memory allocation failed!\n");
		exit(1);
	}
	map->map[map->current_row++] = line;
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

	i = 0;
	while (i < res->texture_count)
	{
		if (res->textures[i] != NULL)
		{
			mlx_delete_texture(res->textures[i]);
			res->textures[i] = NULL;
		}
		i++;
	}
	free(res->textures);
	res->textures = NULL;
	i = 0;
	while (i < res->image_count)
	{
		if (res->images[i] != NULL)
		{
			mlx_delete_image(mlx, res->images[i]);
			res->images[i] = NULL;
		}
		i++;
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

void	check_exit_reached(t_GameData *data)
{
	t_Character		*character;
	t_Exit			*exit;
	unsigned int	char_center_x;
	unsigned int	char_center_y;

	character = &data->character;
	exit = &data->exit;
	char_center_x = (unsigned int)(character->x + character->image->width / 2);
	char_center_y = (unsigned int)(character->y + character->image->height / 2);
	if (exit->opened)
	{
		if (char_center_x >= (unsigned int)exit->x
			&& char_center_x <= (unsigned int)(exit->x + exit->image->width) &&
			char_center_y >= (unsigned int)exit->y &&
			char_center_y <= (unsigned int)(exit->y + exit->image->height))
		{
			ft_printf("CONGLATURATION.\n");
			ft_printf("A WINNER IS YOU.\n");
			mlx_close_window(character->mlx);
		}
	}
}
