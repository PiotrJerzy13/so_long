/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:35:21 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/16 14:16:39 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void key_hook(mlx_key_data_t keydata, void *param)
{
    GameData *data = (GameData *)param;
    Character *character = &data->character;
    Coin *coin = &data->coin;
    Exit *exit = &data->exit;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window(character->mlx);
    }
    else if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        int new_x = character->x;
        int new_y = character->y;

        switch (keydata.key)
        {
            case MLX_KEY_LEFT:
                new_x -= CHARACTER_SPEED;
                break;
            case MLX_KEY_RIGHT:
                new_x += CHARACTER_SPEED;
                break;
            case MLX_KEY_UP:
                new_y -= CHARACTER_SPEED;
                break;
            case MLX_KEY_DOWN:
                new_y += CHARACTER_SPEED;
                break;
            default:
                break;
        }

        if (new_x >= BLOCK_SIZE && new_x <= WIDTH - character->image->width - BLOCK_SIZE &&
            new_y >= BLOCK_SIZE && new_y <= HEIGHT - character->image->height - BLOCK_SIZE)
        {
            mlx_delete_image(character->mlx, character->image);
            character->x = new_x;
            character->y = new_y;
            character->image = mlx_texture_to_image(character->mlx, mlx_load_png("idle.png"));
            mlx_image_to_window(character->mlx, character->image, character->x, character->y);

            if (!coin->collected &&
                character->x < coin->x + coin->image->width &&
                character->x + character->image->width > coin->x &&
                character->y < coin->y + coin->image->height &&
                character->y + character->image->height > coin->y)
            {
                mlx_delete_image(character->mlx, coin->image);
                coin->collected = 1;

                mlx_delete_image(character->mlx, exit->image);
                exit->image = mlx_texture_to_image(character->mlx, mlx_load_png("exit_open.png"));
                mlx_image_to_window(character->mlx, exit->image, exit->x, exit->y);
                exit->opened = 1;
            }

            if (exit->opened &&
                character->x < exit->x + exit->image->width &&
                character->x + character->image->width > exit->x &&
                character->y < exit->y + exit->image->height &&
                character->y + character->image->height > exit->y)
            {
                printf("CONGLATURATION.\n");
                printf("A WINNER IS YOU.\n");
                mlx_close_window(character->mlx);
            }
        }
    }
}
