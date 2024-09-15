/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:39:39 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/15 12:45:24 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_args_and_load_map(int argc, char **argv, t_map *map)
{
	if (argc < 2)
	{
		ft_printf("Missing map path argument!\n");
		exit(1);
	}
	else if (argc > 2)
	{
		ft_printf("Too many arguments!\n");
		exit(1);
	}
	*map = (t_map){0};
	if (load_map(map, argv[1]) != 0)
	{
		exit(1);
	}
}

void	ft_error(int code)
{
	if (code == -1)
	{
		ft_printf("Error: The map is not rectangular!\n");
	}
	else if (code == -2)
	{
		ft_printf("Error: Memory allocation failed!\n");
	}
	else if (code == -3)
	{
		ft_printf("Error: More than one player 'P' found in the map!\n");
	}
	else if (code == -4)
	{
		ft_printf("Error: More than one exit 'E' found in the map!\n");
	}
	else if (code == -5)
	{
		ft_printf(" Unknown Symbol found in the map!\n");
	}
	else if (code == -6)
	{
		ft_printf("Error: Initialization failed!\n");
	}
	exit(1);
}

void	validate_elements(const t_map *map)
{
	if (map->current_row < 3 || map->num_columns < 3)
	{
		ft_printf("Error: The map is too small!\n");
		exit(1);
	}
	if (map->coin_n == 0)
	{
		ft_printf("Error: Collectibles are missing from the map!\n");
		exit(1);
	}
	if (map->exit_n == 0)
	{
		ft_printf("Map Error: The map requires at least one exit point.\n");
		exit(1);
	}
	if (map->player_n == 0)
	{
		ft_printf("Map Error: The map requires at least one player.\n");
		exit(1);
	}
}

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

void	validate_file_extension(t_map *map)
{
	if (!has_valid_extension(map->path, ".ber"))
	{
		ft_printf("Error: The map file must end with *.ber!\n");
		exit(1);
	}
	map->fd = open(map->path, O_RDONLY);
}
