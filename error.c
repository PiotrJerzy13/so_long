/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:37:09 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/18 23:19:20 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(int code, t_map *map)
{
	if (code == -1)
	{
		ft_printf("Error: The map is not rectangular!\n");
	}
	else if (code == -2)
	{
		ft_printf("Error: Memory allocation failed!\n");
	}
	exit(1);
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
