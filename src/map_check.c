/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:26:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/09 09:26:11 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	process_line(t_map *map, char *line)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (ft_strlen(line) != (size_t)map->num_columns)
	{
		free(line);
		free_map_lines(map, map->current_row);
		ft_error(-1);
	}
	map->map[map->current_row++] = line;
	count_map_elements(line, map);
}

void	realloc_map(t_map *map)
{
	map->map = (char **)ft_realloc(map->map,
			map->current_row * sizeof(char *),
			(map->current_row + 1) * sizeof(char *));
	if (!map->map)
	{
		free_map_lines(map, map->current_row);
		ft_error(-2);
	}
}

void	read_lines(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	while (line != NULL)
	{
		realloc_map(map);
		process_line(map, line);
		line = get_next_line(map->fd);
	}
}

int	all_coins_collected(t_GameData *data)
{
	int	i;

	i = 0;
	while (i < data->coin_count)
	{
		if (!data->coins[i].collected)
			return (0);
		i++;
	}
	return (1);
}

void	check_and_collect_coin(t_Character *character, t_Coin *coin)
{
	if (!coin->collected && character->x == coin->x && character->y == coin->y)
	{
		if (coin->image)
		{
			mlx_delete_image(character->mlx, coin->image);
			coin->image = NULL;
		}
		coin->collected = 1;
	}
}
