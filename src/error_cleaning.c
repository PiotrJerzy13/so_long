/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:32:10 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/07 09:06:57 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	cleanup_resources(t_Resources *res, mlx_t *mlx)
{
	int	i;

	i = res->texture_count;
	while (i--)
	{
		if (res->textures[i])
		{
			mlx_delete_texture(res->textures[i]);
			res->textures[i] = NULL;
		}
	}
	free(res->textures);
	res->textures = NULL;
	i = res->image_count;
	while (i--)
	{
		if (res->images[i])
		{
			mlx_delete_image(mlx, res->images[i]);
			res->images[i] = NULL;
		}
	}
	free(res->images);
	res->images = NULL;
}

void	free_coins(t_Coin *coins, int coin_count, mlx_t *mlx)
{
	int	i;

	i = 0;
	while (i < coin_count)
	{
		if (coins[i].image)
		{
			mlx_delete_image(mlx, coins[i].image);
			coins[i].image = NULL;
		}
		i++;
	}
}
