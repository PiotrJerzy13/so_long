/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:42:16 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 16:33:59 by pwojnaro         ###   ########.fr       */
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
		ft_printf("Error loading the map!\n");
		exit(1);
	}
}

void	count_map_elements(char *line, t_map *map)
{
	while (*line)
	{
		if (*line == 'C')
			map->coin_n++;
		else if (*line == 'P')
		{
			map->player_n++;
			if (map->player_n > 1)
				ft_error(-3);
		}
		else if (*line == 'E')
		{
			map->exit_n++;
			if (map->exit_n > 1)
				ft_error(-4);
		}
		else if (*line == '1')
			map->wall_n++;
		else if (*line == '0')
			;
		else
			ft_error(-5);
		line++;
	}
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
