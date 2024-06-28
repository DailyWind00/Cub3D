/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:55:39 by mgallais          #+#    #+#             */
/*   Updated: 2024/06/13 18:26:48 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_all(t_data *data)
{
	data->texture_path.north_texture = NULL;
	data->texture_path.south_texture = NULL;
	data->texture_path.west_texture = NULL;
	data->texture_path.east_texture = NULL;
	data->textures.north_pixel = NULL;
	data->textures.south_pixel = NULL;
	data->textures.west_pixel = NULL;
	data->textures.east_pixel = NULL;
	data->map.start_pos.x = -1;
	data->map.start_pos.y = -1;
	data->map.map = NULL;
	data->textures.ceiling_color.r = -1;
	data->textures.floor_color.r = -1;
	data->textures.floor_color.g = -1;
	data->textures.ceiling_color.g = -1;
	data->textures.floor_color.b = -1;
	data->textures.ceiling_color.b = -1;
	data->screen_size.x = 1920;
	data->screen_size.y = 1080;
	data->player_dir = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_all(&data);
	parsing(&data, argc, argv);
	load_png(&data);
	if (DEBUG)
		printf_debug(&data);
	start_game(&data);
	free_data(&data);
	return (0);
}
