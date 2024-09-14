/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:42:16 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/13 18:11:46 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_exit_reached(t_GameData *data)
{
	t_Character		*character;
	const t_Exit	*exit;
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
