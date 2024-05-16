/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:23:53 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/05/16 22:30:29 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define BLOCK_SIZE 32
#define CHARACTER_SPEED 10

typedef struct {
    int x;              // x-coordinate of the character's position
    int y;              // y-coordinate of the character's position
    mlx_image_t *image; // Pointer to the character's image
    mlx_t *mlx;         // Pointer to the MLX instance
} Character;


void key_hook(mlx_key_data_t keydata, void *param)
{
    Character *character = (Character *)param; // Cast the parameter to a Character pointer

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        // Close the window if the ESC key is pressed
        mlx_close_window(character->mlx);
    }
    else if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        int new_x = character->x;
        int new_y = character->y;

        // Update character position based on key press
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

        // Ensure character stays within window boundaries
        if (new_x >= 0 && new_x <= WIDTH - character->image->width)
        {
            character->x = new_x;
        }
        if (new_y >= 0 && new_y <= HEIGHT - character->image->height)
        {
            character->y = new_y;
        }

        // Move the character to the new position
        mlx_image_to_window(character->mlx, character->image, character->x, character->y);
    }
}


int main(void)
{
    // Initialize MLX and create a window
    mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Window with Background", true);
    if (!mlx)
    {
        fprintf(stderr, "MLX initialization failed\n");
        return EXIT_FAILURE;
    }

    // List of background image paths
    const char *paths[] = {
        "0.png",
        "1.png",
        "2.png",
        "3.png",
        "4.png",
    };

    // Load the background textures
    mlx_texture_t *textures[5];
    for (int i = 0; i < 5; ++i)
    {
        textures[i] = mlx_load_png(paths[i]);
        if (!textures[i])
        {
            fprintf(stderr, "Failed to load texture: %s\n", paths[i]);
            mlx_terminate(mlx);
            return EXIT_FAILURE;
        }
    }

    // Create images from textures
    mlx_image_t *images[5];
    for (int i = 0; i < 5; ++i)
    {
        images[i] = mlx_texture_to_image(mlx, textures[i]);
        if (!images[i])
        {
            fprintf(stderr, "Failed to convert texture to image: %s\n", paths[i]);
            for (int j = 0; j <= i; ++j) {
                mlx_delete_texture(textures[j]);
            }
            mlx_terminate(mlx);
            return EXIT_FAILURE;
        }
    }
    // Load the block texture for walls
    mlx_texture_t *block_tex = mlx_load_png("block1.png");
    if (!block_tex)
    {
        fprintf(stderr, "Failed to load block texture\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Create an image from the block texture
    mlx_image_t *block_img = mlx_texture_to_image(mlx, block_tex);
    if (!block_img)
    {
        fprintf(stderr, "Failed to convert block texture to image\n");
        mlx_delete_texture(block_tex);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

	// load the main character
	mlx_texture_t *idle_tex = mlx_load_png("idle.png");
	 if (!idle_tex)
    {
        fprintf(stderr, "Failed to load idle texture\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

	mlx_image_t *idle_img = mlx_texture_to_image(mlx,idle_tex);
	  if (!idle_img)
    {
        fprintf(stderr, "Failed to convert block texture to image\n");
        mlx_delete_texture(idle_tex);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
	// load coin character
	mlx_texture_t *coin_tex = mlx_load_png("coin.png");
	 if (!coin_tex)
    {
        fprintf(stderr, "Failed to load idle texture\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

	mlx_image_t *coin_img = mlx_texture_to_image(mlx,coin_tex);
	  if (!coin_img)
    {
        fprintf(stderr, "Failed to convert block texture to image\n");
        mlx_delete_texture(coin_tex);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Render the background images to the window
    for (int i = 0; i < 5; ++i)
    {
        mlx_image_to_window(mlx, images[i], 0, i * 100);
    }

	    for (int x = 0; x < WIDTH; x += BLOCK_SIZE)
    {
        // Top wall
        mlx_image_to_window(mlx, block_img, x, 0);
        // Bottom wall
        mlx_image_to_window(mlx, block_img, x, HEIGHT - BLOCK_SIZE);
    }
    for (int y = 0; y < HEIGHT; y += BLOCK_SIZE)
    {
        // Left wall
        mlx_image_to_window(mlx, block_img, 0, y);
        // Right wall
        mlx_image_to_window(mlx, block_img, WIDTH - BLOCK_SIZE, y);
    }

    // Initialize character
    Character character;
    character.image = idle_img;
    character.mlx = mlx;  // Set the MLX instance
    character.x = (WIDTH - idle_img->width) / 2;
    character.y = HEIGHT - BLOCK_SIZE - idle_img->height;
    mlx_image_to_window(mlx, character.image, character.x, character.y);

	// Position the coin on the floor blocks
    int char_x1 = (WIDTH - coin_img->width) / 4;
    int char_y1 = HEIGHT - BLOCK_SIZE - coin_img->height;
    mlx_image_to_window(mlx, coin_img, char_x1, char_y1);

    // Set a key press callback function
    mlx_key_hook(mlx, key_hook, &character);

    // Main loop
    mlx_loop(mlx);

    // Cleanup
    for (int i = 0; i < 5; ++i)
    {
        mlx_delete_texture(textures[i]);
        mlx_delete_image(mlx, images[i]);
    }

    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}
