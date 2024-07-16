
#ifndef SO_LONG_H
#define SO_LONG_H

#include <MLX42/MLX42.h>
# include <stdlib.h>
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

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
