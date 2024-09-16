/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:42:16 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/16 13:12:18 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (!exit->opened && all_coins_collected(data))
	{
		exit->opened = 1;
		ft_printf("Exit is open!\n");
	}
	if (exit->opened)
	{
		if (char_center_x >= (unsigned int)exit->x
			&& char_center_x <= (unsigned int)(exit->x + exit->image->width) &&
			char_center_y >= (unsigned int)exit->y &&
			char_center_y <= (unsigned int)(exit->y + exit->image->height))
		{
			mlx_close_window(character->mlx);
		}
	}
}
