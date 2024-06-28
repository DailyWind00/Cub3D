/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:45:29 by mgallais          #+#    #+#             */
/*   Updated: 2024/06/20 10:30:25 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// return true if the player has moved
static bool	player_controls(t_data *data)
{
	bool	has_moved;

	has_moved = false;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) && move_forward(data) != 2)
		has_moved = true;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) && move_backward(data) != 2)
		has_moved = true;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) && move_left(data) != 2)
		has_moved = true;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) && move_right(data) != 2)
		has_moved = true;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	return (has_moved);
}

// return true if the player moved camera
static bool	camera_controls(t_data *data)
{
	t_2int	mouse_pos;

	if (BONUS)
	{
		mouse_pos.x = 0;
		mouse_pos.y = 0;
		mlx_get_mouse_pos(data->mlx, &mouse_pos.x, &mouse_pos.y);
		if (mouse_pos.x > data->screen_size.x / 2 + 10)
			data->player_dir += (mouse_pos.x - data->screen_size.x / 2) / 10;
		else if (mouse_pos.x < data->screen_size.x / 2 - 10)
			data->player_dir -= (data->screen_size.x / 2 - mouse_pos.x) / 10;
		else
			return (false);
		mlx_set_mouse_pos(data->mlx, data->screen_size.x / 2,
			data->screen_size.y / 2);
		return (true);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player_dir -= PLAYER_ROTATION_SPEED;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player_dir += PLAYER_ROTATION_SPEED ;
	else
		return (false);
	data->player_dir = round_deg(data->player_dir);
	return (true);
}

static bool	window_resized(t_data *data)
{
	static t_2int	previous_screen_size = {1920, 1080};

	if (data->screen_size.x != previous_screen_size.x
		|| data->screen_size.y != previous_screen_size.y)
	{
		previous_screen_size.x = data->screen_size.x;
		previous_screen_size.y = data->screen_size.y;
		return (true);
	}
	return (false);
}

// game loop
void	events(void *params)
{
	t_data			*data;
	bool			do_raycast;
	double			frame_time;

	data = (t_data *)params;
	frame_time = mlx_get_time() - data->last_frame;
	if (frame_time < 1 / FPS)
		return ;
	do_raycast = false;
	if (player_controls(data))
		do_raycast = true;
	if (camera_controls(data))
		do_raycast = true;
	if (window_resized(data))
		do_raycast = true;
	if (do_raycast)
	{
		mlx_delete_image(data->mlx, data->camera_view);
		data->camera_view = mlx_new_image(data->mlx,
				data->screen_size.x, data->screen_size.y);
		background(data);
		new_raycast(data);
		minimap(data);
		mlx_image_to_window(data->mlx, data->camera_view, 0, 0);
	}
}
