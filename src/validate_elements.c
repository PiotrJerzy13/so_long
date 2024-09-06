/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:32:17 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 14:42:42 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_elements(t_map *map)
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

void	validate_top_walls(char *line, int num_columns, int is_top)
{
	int	index;

	index = 0;
	while (index < num_columns)
	{
		if (line[index] != '1')
		{
			if (is_top)
			{
				ft_printf("Error: The top wall of the map is incomplete!\n");
			}
			else
			{
				ft_printf("Map Error: The bottom wall is incomplete!\n");
			}
			exit(1);
		}
		index++;
	}
}

void	validate_side_walls(char *line, int num_columns)
{
	if (line[0] != '1' || line[num_columns - 1] != '1')
	{
		ft_printf("Error: The side walls of the map are incomplete!\n");
		exit(1);
	}
}

void	validate_map_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		validate_side_walls(map->map[i], map->width);
		i++;
	}
}

void	validate_walls(t_map *map)
{
	int	i;

	i = 0;
	validate_top_walls(map->map[0], map->width, 1);
	validate_top_walls(map->map[map->height - 1], map->width, 0);
	while (i < map->height - 1)
	{
		validate_side_walls(map->map[i], map->width);
		i++;
	}
}
