/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:27:05 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/16 17:50:26 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include "libft/libft.h"

# define BLOCK_SIZE 32
# define FIXED_WINDOW_WIDTH 800
# define FIXED_WINDOW_HEIGHT 600

// Structures
typedef struct s_exit
{
	int			x;
	int			y;
	mlx_image_t	*image;
	int			opened;
}	t_exit;

typedef struct s_character
{
	int			x;
	int			y;
	mlx_image_t	*image;
	mlx_t		*mlx;
}	t_character;

typedef struct s_coin
{
	int			x;
	int			y;
	mlx_image_t	*image;
	int			collected;
}	t_coin;

typedef struct s_resources
{
	mlx_texture_t	**textures;
	int				texture_count;
	mlx_image_t		**images;
	int				image_count;
	mlx_image_t		*block_img;
}	t_resources;

typedef struct s_gamedata
{
	int				move_count;
	t_character		character;
	t_coin			*coins;
	t_exit			exit;
	struct s_map	*map;
	int				coin_count;
	mlx_t			*mlx;
	t_resources		*res;
}	t_game_data;

typedef struct s_position
{
	int	row;
	int	col;
}	t_position;

typedef struct s_map
{
	mlx_t				*mlx;
	mlx_image_t			***background_map;
	mlx_image_t			***wall_map;
	mlx_image_t			***img_map;
	char				*path;
	int					fd;
	int					player_n;
	int					exit_n;
	int					coin_n;
	int					wall_n;
	int					width;
	int					height;
	char				**map;
	int					current_row;
	int					num_columns;
}						t_map;

typedef struct s_map_data
{
	char	**map;
	int		height;
	int		width;
	int		reachable_coins;
	int		exit_reachable;
	int		total_coins;
}	t_map_data;

// Initialization functions
mlx_t			*initialize_window(int width, int height, const char *title);
mlx_texture_t	*load_texture(const char *path);
mlx_image_t		*create_image(mlx_t *mlx, const char *path);
void			load_text_to_array(t_resources *res, mlx_t *mlx);

// Map processing and validation
void			count_map_elements(char *line, t_map *map);
void			validate_elements(const t_map *map);
void			validate_file_extension(t_map *map);
void			validate_walls(t_map *map);
void			validate_args_and_load_map(int argc, char **argv, t_map *map);
int				load_map(t_map *map, char *file_path);
void			create_block(t_map *map, mlx_t *mlx, t_resources *res);

// Rendering functions
void			render_background_and_walls(mlx_t *mlx,
					mlx_image_t *background_img,
					mlx_image_t *block_img, t_map *map);
void			render_game_objects(mlx_t *mlx, t_game_data *data);

// Event handling and movement
void			key_hook(mlx_key_data_t keydata, void *param);

// Coin and exit handling
void			check_coin_collection(t_game_data *data);
void			check_exit_reached(t_game_data *data);
int				all_coins_collected(const t_game_data *data);

// Flood fill and map validation
void			start_flood_fill(t_map_data *map_data);
void			count_coins(t_map_data *map_data);
t_position		find_element(char **map, char element, int height, int width);

// Image and block generation
void			initialize_image_map(t_map *map);
void			initialize_background_map(t_map *map);
void			load_char_and_exit(mlx_t *mlx, t_game_data *data,
					t_map *map, int block_size);
void			fill_coins_on_map(mlx_t *mlx, t_game_data *data, t_map *map);

// Error handling and cleanup
void			ft_error(int code);
void			handle_error_cleanup(t_resources *res, mlx_t *mlx,
					int count, int is_texture);
void			cleanup_resources(t_resources *res, mlx_t *mlx);
void			ft_clean(t_map *map);
void			free_background_map(t_map *map);
void			free_coins(t_coin *coins, int coin_count, mlx_t *mlx);
void			free_image_map(t_map *map, int max_r, int max_c);
void			free_map_lines(t_map *map, int max_row);
void			read_lines(t_map *map);
void			free_map_resources(t_map *map);
void			free_img_grid(t_map *map);
void			allocate_memory_coins(t_game_data *data, t_map *map);
void			check_path(t_map_data *map_data);

#endif
