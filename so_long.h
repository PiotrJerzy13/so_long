/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:27:05 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/18 22:15:21 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"

# define BLOCK_SIZE 32
# define FIXED_WINDOW_WIDTH 800
# define FIXED_WINDOW_HEIGHT 600

typedef struct s_exit
{
	int			x;
	int			y;
	mlx_image_t	*image;
	int			opened;
}	t_Exit;

typedef struct s_character
{
	int			x;
	int			y;
	mlx_image_t	*image;
	mlx_t		*mlx;
}	t_Character;

typedef struct s_coin
{
	int			x;
	int			y;
	mlx_image_t	*image;
	int			collected;
}	t_Coin;

typedef struct s_resources
{
	mlx_texture_t	**textures;
	int				texture_count;
	mlx_image_t		**images;
	int				image_count;
	mlx_image_t		*block_img;
}	t_Resources;

typedef struct s_gamedata
{
	int				move_count;
	t_Character		character;
	t_Coin			*coins;
	t_Exit			exit;
	struct s_map	*map;
	int				coin_count;
	mlx_t			*mlx;
	t_Resources		*res;
}	t_GameData;

typedef struct s_position
{
	int	row;
	int	col;
}	t_Position;

typedef struct s_map
{
	mlx_t				*mlx;
	mlx_image_t			***background_map;
	mlx_image_t			***wall_map;
	mlx_image_t			****img_map;
	char				*path;
	int					fd;
	int					p_num;
	int					e_num;
	int					c_num;
	int					w_num;
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

}	t_map_data;

// init.c
mlx_t			*initialize_window(int width, int height, const char *title);
mlx_texture_t	*load_texture(const char *path);
mlx_image_t		*create_image(mlx_t *mlx, mlx_texture_t *texture);

// render.c
void			render_background_and_walls(mlx_t *mlx,
					mlx_image_t *background_img,
					mlx_image_t *block_img, t_map *map);

void			render_game_objects(mlx_t *mlx, t_GameData *data);
void			calculate_map_dimensions(t_map *map);

// game.c
void			key_hook(mlx_key_data_t keydata, void *param);

// cleanup.c
void			cleanup(mlx_t *mlx, t_Resources *res);
void			count_map_elements(char *line, t_map *map);
void			validate_elements(t_map *map);
void			validate_map_walls(t_map *map);

// error.c
void			ft_error(int code, t_map *map);

// image_block_gen.c
void			initialize_image_map(t_map *map);
void			initialize_background_map(t_map *map);

// map.c
int				can_move_to(t_map *map, int col, int row, int exit_opened);

// map_check.c
void			validate_file_extension(t_map *map);
void			process_map(t_map *map);
void			validate_walls(char *line, t_map *map);

int				all_coins_collected(t_GameData *data);
t_Position		find_element(char **map, char element, int height, int width);
int				has_valid_extension(const char *path, const char *extension);
int				all_coins_collected(t_GameData *data);
void			initialize_coin(mlx_t *mlx, t_Coin *coin, int x, int y);
void			iterate_and_populate(mlx_t *mlx, t_GameData *data, t_map *map);
void			init_char_and_exit(mlx_t *mlx,
					t_GameData *data, t_map *map, int block_size);
t_GameData		initialize_game_data(mlx_t *mlx, t_map *map, t_Resources *res);
void			check_coin_collection(t_GameData *data, int block_size);
void			validate_args_and_load_map(int argc, char **argv, t_map *map);
int				load_map(t_map *map, char *file_path);

#endif 
