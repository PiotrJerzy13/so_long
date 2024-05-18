/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:00 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/05/18 19:34:14 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    mlx_t *mlx = initialize_window(WIDTH, HEIGHT, "Window with Background");

    const char *paths[] = {
        "0.png",
        "1.png",
        "2.png",
        "3.png",
        "4.png",
    };

    mlx_texture_t *textures[5];
    for (int i = 0; i < 5; ++i)
    {
        textures[i] = load_texture(paths[i]);
    }

    mlx_image_t *images[5];
    for (int i = 0; i < 5; ++i)
    {
        images[i] = create_image(mlx, textures[i]);
    }

    mlx_texture_t *block_tex = load_texture("block1.png");
    mlx_image_t *block_img = create_image(mlx, block_tex);

    render_background_and_walls(mlx, images, block_img);

    GameData data = initialize_game_data(mlx);
    render_game_objects(mlx, &data);

    mlx_key_hook(mlx, key_hook, &data);

    mlx_loop(mlx);

    cleanup(mlx, textures, 5, images, 5);

    return EXIT_SUCCESS;
}
