/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:36:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/05/18 20:03:46 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h>
#include <stdio.h>

mlx_t* initialize_window(int width, int height, const char *title)
{
    mlx_t *mlx = mlx_init(width, height, title, true);
    if (!mlx)
    {
        fprintf(stderr, "MLX initialization failed\n");
        exit(EXIT_FAILURE);
    }
    return mlx;
}

mlx_texture_t* load_texture(const char *path)
{
    mlx_texture_t *texture = mlx_load_png(path);
    if (!texture)
    {
        fprintf(stderr, "Failed to load texture: %s\n", path);
        exit(EXIT_FAILURE);
    }
    return texture;
}

mlx_image_t* create_image(mlx_t *mlx, mlx_texture_t *texture)
{
    mlx_image_t *image = mlx_texture_to_image(mlx, texture);
    if (!image)
    {
        fprintf(stderr, "Failed to convert texture to image\n");
        exit(EXIT_FAILURE);
    }
    return image;
}

GameData initialize_game_data(mlx_t *mlx)
{
    GameData data;

    mlx_texture_t *idle_tex = load_texture("idle.png");
    mlx_texture_t *coin_tex = load_texture("coin.png");
    mlx_texture_t *exit_tex = load_texture("exit_open.png");

    data.character.image = create_image(mlx, idle_tex);
    data.coin.image = create_image(mlx, coin_tex);
    data.exit.image = create_image(mlx, exit_tex);

    data.character.mlx = mlx;
    data.character.x = (WIDTH - data.character.image->width) / 2;
    data.character.y = HEIGHT - BLOCK_SIZE - data.character.image->height;
    data.coin.x = (WIDTH - data.coin.image->width) / 4;
    data.coin.y = HEIGHT - BLOCK_SIZE - data.coin.image->height;
    data.coin.collected = 0;
    data.exit.x = (WIDTH - data.exit.image->width) / 2;
    data.exit.y = BLOCK_SIZE;
    data.exit.opened = 0;

    return data;
}
