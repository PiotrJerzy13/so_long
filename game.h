/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:37:00 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/05/18 19:37:00 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include <MLX42/MLX42.h>

#define WIDTH 800
#define HEIGHT 600
#define BLOCK_SIZE 32
#define CHARACTER_SPEED 10

typedef struct {
    int x;
    int y;
    mlx_image_t *image;
    int opened;
} Exit;

typedef struct {
    int x;
    int y;
    mlx_image_t *image;
    mlx_t *mlx;
} Character;

typedef struct {
    int x;
    int y;
    mlx_image_t *image;
    int collected;
} Coin;

typedef struct {
    Character character;
    Coin coin;
    Exit exit;
} GameData;

// init.c
mlx_t* initialize_window(int width, int height, const char *title);
mlx_texture_t* load_texture(const char *path);
mlx_image_t* create_image(mlx_t *mlx, mlx_texture_t *texture);
GameData initialize_game_data(mlx_t *mlx);

// render.c
void render_background_and_walls(mlx_t *mlx, mlx_image_t *background_images[], mlx_image_t *block_img);
void render_game_objects(mlx_t *mlx, GameData *data);

// game.c
void key_hook(mlx_key_data_t keydata, void *param);

// cleanup.c
void cleanup(mlx_t *mlx, mlx_texture_t *textures[], int texture_count, mlx_image_t *images[], int image_count);

#endif // GAME_H
