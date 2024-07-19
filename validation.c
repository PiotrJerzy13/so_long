/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:24:58 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/19 12:01:15 by pwojnaro         ###   ########.fr       */
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
	if (map->c_num == 0)
	{
		ft_printf("Error: Collectibles are missing from the map!\n");
		exit(1);
	}
	if (map->e_num == 0)
	{
		ft_printf("Map Error: The map requires at least one exit point.\n");
		exit(1);
	}
	if (map->p_num == 0)
	{
		ft_printf("Map Error: The map requires at least one player.\n");
		exit(1);
	}
}

void	validate_map_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		validate_walls(map->map[i], map);
		i++;
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

void	validate_walls(char *line, t_map *map)
{
	if (map->current_row == 0)
	{
		validate_top_walls(line, map->num_columns, 1);
	}
	else if (map->current_row == map->height - 1)
	{
		validate_top_walls(line, map->num_columns, 0);
	}
	else
	{
		validate_side_walls(line, map->num_columns);
	}
}
