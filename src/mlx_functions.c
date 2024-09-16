/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:36:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/16 14:12:44 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_t	*initialize_window(int width, int height, const char *title)
{
	mlx_t	*mlx;

	mlx = mlx_init(width, height, title, true);
	if (!mlx)
	{
		ft_printf("Failed to initialize window\n");
		exit(1);
	}
	return (mlx);
}

mlx_texture_t	*load_texture(const char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_printf("Failed to load texture: %s\n", path);
		exit(1);
	}
	return (texture);
}

mlx_image_t	*create_image(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = load_texture(path);
	image = mlx_texture_to_image(mlx, texture);
	if (!image)
	{
		ft_printf("Failed to convert texture to image\n");
		mlx_delete_texture(texture);
		exit(1);
	}
	mlx_delete_texture(texture);
	return (image);
}
