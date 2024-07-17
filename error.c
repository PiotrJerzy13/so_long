/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:37:09 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/17 11:59:07 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(int code, t_map *map)
{
	if (code == -12)
	{
		printf("Memory allocation did not work!\n");
	}
	exit(EXIT_FAILURE);
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
				printf("Map Error: The top wall of the map is incomplete!\n");
			}
			else
			{
				printf("Map Error: The bottom wall is incomplete!\n");
			}
			exit(EXIT_FAILURE);
		}
		index++;
	}
}

void	validate_side_walls(char *line, int num_columns)
{
	if (line[0] != '1' || line[num_columns - 1] != '1')
	{
		printf("Map Error: The side walls of the map are incomplete!\n");
		exit(EXIT_FAILURE);
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
