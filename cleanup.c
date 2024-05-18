/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:34:45 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/05/18 19:34:55 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void cleanup(mlx_t *mlx, mlx_texture_t *textures[], int texture_count, mlx_image_t *images[], int image_count)
{
    for (int i = 0; i < texture_count; ++i)
    {
        mlx_delete_texture(textures[i]);
    }
    for (int i = 0; i < image_count; ++i)
    {
        mlx_delete_image(mlx, images[i]);
    }
    mlx_terminate(mlx);
}
