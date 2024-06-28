/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:44:25 by vsoltys           #+#    #+#             */
/*   Updated: 2024/06/20 11:34:17 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*###########################################################################*/
/*                                  Defines                                  */
/*###########################################################################*/
// Program settings define
# ifdef DEBUG
#  define DEBUG 1
# else
#  define DEBUG 0
# endif

# ifdef BONUS
#  define BONUS 1
# else
#  define BONUS 0
# endif

// Cub3D defines
# define NORTH   1
# define SOUTH   2
# define WEST    3
# define EAST    4

# define PLAYER_SPEED 0.05f
# define RAY_SPEED 0.05f
# define PLAYER_ROTATION_SPEED 2.0f
# define FOV 90.0f
# define TEXTURE_SIZE 64
# define MAX_DISTANCE 250.0f
# define FPS 60

// Custom defines
# define WHITESPACES "\t\n\v\f\r "
# define M_PI 3.14159265358979323846

/*###########################################################################*/
/*                                 Includes                                  */
/*###########################################################################*/
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/DailyLib/dailylib.h"
# include "../lib/libft/libft.h"
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

/*###########################################################################*/
/*                                Structures                                 */
/*###########################################################################*/

// map data
typedef struct s_map
{
	char		**map;
	int			fd;
	char		*map_path;
	t_2int		map_size;
	char		player_start;
	t_2int		start_pos;
}	t_map;

typedef struct s_textures
{
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	t_3RGB			floor_color;
	t_3RGB			ceiling_color;
	uint32_t		*north_pixel;
	uint32_t		*south_pixel;
	uint32_t		*west_pixel;
	uint32_t		*east_pixel;
}	t_textures;

typedef struct s_texture_path
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
}	t_texture_path;

// Used for raycaster, 
// use defines for wall_type,
// texture_pos is in percent
typedef struct s_raywall
{
	float	distance;
	short	wall_type;
	short	texture_pos;
}	t_raywall;

// Main Structure
typedef struct s_data
{
	mlx_t			*mlx;
	t_map			map;
	t_textures		textures;
	t_texture_path	texture_path;
	t_2float		player_pos;
	t_2int			screen_size;
	float			player_dir;
	mlx_image_t		*camera_view;
	double			last_frame;
}	t_data;

/*###########################################################################*/
/*                                 Fonctions                                 */
/*###########################################################################*/

void		parsing(t_data *data, int argc, char **argv);
int			tcheck_max_rgb_value(t_data *data, char *temp, char *str);
void		printf_debug(t_data *data);
void		read_lenght(t_data *data);
void		table_to_map(t_data *data);
void		load_png(t_data *data);
void		delete_texture(t_data *data);
void		free_data(t_data *data);
void		exit_msg(t_data *data, char *msg, int status);
void		tcheck_file(t_data *data);
bool		is_wall(t_data *data, t_2float pos, bool is_player);
void		start_game(t_data *data);
void		events(void *data);
double		deg_to_rad(double deg);
int			move_forward(t_data *data);
int			move_backward(t_data *data);
int			move_left(t_data *data);
int			move_right(t_data *data);
void		find_map_size_and_player_pos(t_data *data);
void		new_raycast(t_data *data);
void		extract_value_condition(t_data *data);
int			extract_value(t_data *data);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
float		round_deg(float angle);
short		check_wall_type(t_2float ray, float angle);
short		check_texture_pos(t_2float ray, t_raywall raywall);
void		printf_wall_type(short wall_type);
uint8_t		*texture_pixel(t_data *data, t_raywall *rays);
void		convert_to_hex(uint32_t *texture_map, uint8_t *pixels);
void		background(t_data *data);
void		minimap(t_data *data);
uint32_t	apply_fog(uint32_t color, float fog_factor);
void		extract_value_2_2(t_data *data, char *str);
char		*extract_texture_path(char *str);
t_3RGB		extract_rgb(t_data *data, char *str, t_3RGB return_value);
void		exit_extract_rgb(t_data *data, char *str, char *error_msg);
#endif
