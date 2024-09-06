/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:32:10 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/06 14:50:14 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	has_valid_extension(const char *path, const char *extension)
{
	int			path_len;
	int			ext_len;
	const char	*path_ext;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(extension);
	if (path_len < ext_len)
		return (0);
	path_ext = path + path_len - ext_len;
	while (*extension)
	{
		if (*path_ext != *extension)
			return (0);
		path_ext++;
		extension++;
	}
	return (1);
}

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

void	cleanup(mlx_t *mlx, t_Resources *res)
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
	if (mlx)
		mlx_terminate(mlx);
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

void	close_window_and_cleanup(mlx_t *mlx, t_Resources *res, t_map *map)
{
	cleanup_resources(res, mlx);
	free_background_map(map);
	mlx_terminate(mlx);
}
