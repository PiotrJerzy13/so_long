/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coins_initialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:24:23 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/08 10:26:58 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	has_valid_extension(const char *path, const char *extension)
{
	int			path_len;
	int			ext_len;
	const char	*path_ext;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(extension);
	if (path_len < ext_len)
		return (0);
	path_ext = path + path_len - ext_len;
	while (*extension)
	{
		if (*path_ext != *extension)
			return (0);
		path_ext++;
		extension++;
	}
	return (1);
}

int	load_map(t_map *map, char *file_path)
{
	int			row;
	t_Position	player_pos;

	row = 0;
	map->path = file_path;
	validate_file_extension(map);
	process_map(map);
	while (row < map->height)
	{
		row++;
	}
	player_pos = find_element(map->map, 'P', map->height, map->width);
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

void	exit_if_all(t_Character *character, t_Exit *exit_door, t_GameData *data)
{
	mlx_texture_t	*texture;

	if (all_coins_collected(data))
	{
		if (exit_door->image)
		{
			mlx_delete_image(character->mlx, exit_door->image);
			exit_door->image = NULL;
		}
		texture = mlx_load_png("text/exit_open.png");
		if (!texture)
		{
			ft_printf("Error loading exit texture\n");
			return ;
		}
		exit_door->image = mlx_texture_to_image(character->mlx, texture);
		mlx_delete_texture(texture);
		mlx_image_to_window(character->mlx,
			exit_door->image, exit_door->x, exit_door->y);
		exit_door->opened = 1;
		ft_printf("Exit is open!\n");
	}
}

void	validate_file_extension(t_map *map)
{
	if (!has_valid_extension(map->path, ".ber"))
	{
		ft_printf("Error: The map file must end with *.ber!\n");
		exit(1);
	}
	map->fd = open(map->path, O_RDONLY);
}
