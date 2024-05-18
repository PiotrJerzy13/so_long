/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:35:50 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/05/18 19:35:57 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void render_background_and_walls(mlx_t *mlx, mlx_image_t *background_images[], mlx_image_t *block_img)
{
    for (int i = 0; i < 5; ++i)
    {
        mlx_image_to_window(mlx, background_images[i], 0, i * 100);
    }

    for (int x = 0; x < WIDTH; x += BLOCK_SIZE)
    {
        mlx_image_to_window(mlx, block_img, x, 0);
        mlx_image_to_window(mlx, block_img, x, HEIGHT - BLOCK_SIZE);
    }
    for (int y = 0; y < HEIGHT; y += BLOCK_SIZE)
    {
        mlx_image_to_window(mlx, block_img, 0, y);
        mlx_image_to_window(mlx, block_img, WIDTH - BLOCK_SIZE, y);
    }
}

void render_game_objects(mlx_t *mlx, GameData *data)
{
    mlx_image_to_window(mlx, data->character.image, data->character.x, data->character.y);
    mlx_image_to_window(mlx, data->coin.image, data->coin.x, data->coin.y);
    mlx_image_to_window(mlx, data->exit.image, data->exit.x, data->exit.y);
}
