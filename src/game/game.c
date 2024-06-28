/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:22:02 by mgallais          #+#    #+#             */
/*   Updated: 2024/06/21 10:23:23 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	resize(int width, int height, void *params)
{
	t_data	*data;

	data = (t_data *)params;
	data->screen_size.x = width;
	data->screen_size.y = height;
	if (DEBUG)
		printf("Window | width: %d, height: %d\n", width, height);
}

void	get_texture_pixel(t_data *data)
{
	uint32_t	*texture;

	texture = malloc(sizeof(uint32_t) * TEXTURE_SIZE * TEXTURE_SIZE);
	convert_to_hex(texture, data->textures.east_texture->pixels);
	data->textures.east_pixel = texture;
	texture = malloc(sizeof(uint32_t) * TEXTURE_SIZE * TEXTURE_SIZE);
	convert_to_hex(texture, data->textures.north_texture->pixels);
	data->textures.north_pixel = texture;
	texture = malloc(sizeof(uint32_t) * TEXTURE_SIZE * TEXTURE_SIZE);
	convert_to_hex(texture, data->textures.south_texture->pixels);
	data->textures.south_pixel = texture;
	texture = malloc(sizeof(uint32_t) * TEXTURE_SIZE * TEXTURE_SIZE);
	convert_to_hex(texture, data->textures.west_texture->pixels);
	data->textures.west_pixel = texture;
}

void	start_game(t_data *data)
{
	data->mlx = mlx_init(data->screen_size.x,
			data->screen_size.y, "Cub3D", true);
	if (!data->mlx)
	{
		delete_texture(data);
		printf("Critical Error :\n\tmlx_init failed\n");
		return ;
	}
	get_texture_pixel(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, data->screen_size.x / 2,
		data->screen_size.y / 2);
	data->camera_view = mlx_new_image(data->mlx,
			data->screen_size.x, data->screen_size.y);
	data->last_frame = mlx_get_time();
	mlx_resize_hook(data->mlx, resize, data);
	mlx_loop_hook(data->mlx, events, data);
	mlx_loop(data->mlx);
	delete_texture(data);
	mlx_terminate(data->mlx);
}
