/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:32:21 by mgallais          #+#    #+#             */
/*   Updated: 2024/06/10 09:19:15 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	move_forward(t_data *data)
{
	t_2float	new_pos;
	int			return_value;

	return_value = 0;
	new_pos = data->player_pos;
	new_pos.x += cos(deg_to_rad(data->player_dir)) * PLAYER_SPEED;
	if (!is_wall(data, new_pos, true))
		data->player_pos = new_pos;
	else
		return_value++;
	new_pos.y += sin(deg_to_rad(data->player_dir)) * PLAYER_SPEED;
	if (!is_wall(data, new_pos, true))
		data->player_pos = new_pos;
	else
		return_value++;
	return (return_value);
}

int	move_backward(t_data *data)
{
	t_2float	new_pos;
	int			return_value;

	return_value = 0;
	new_pos = data->player_pos;
	new_pos.x -= cos(deg_to_rad(data->player_dir)) * PLAYER_SPEED;
	if (!is_wall(data, new_pos, true))
		data->player_pos = new_pos;
	else
		return_value++;
	new_pos.y -= sin(deg_to_rad(data->player_dir)) * PLAYER_SPEED;
	if (!is_wall(data, new_pos, true))
		data->player_pos = new_pos;
	else
		return_value++;
	return (return_value);
}

int	move_left(t_data *data)
{
	t_2float	new_pos;
	int			return_value;

	return_value = 0;
	new_pos = data->player_pos;
	new_pos.x += cos(deg_to_rad(data->player_dir - 90)) * PLAYER_SPEED;
	if (!is_wall(data, new_pos, true))
		data->player_pos = new_pos;
	else
		return_value++;
	new_pos.y += sin(deg_to_rad(data->player_dir - 90)) * PLAYER_SPEED;
	if (!is_wall(data, new_pos, true))
		data->player_pos = new_pos;
	else
		return_value++;
	return (return_value);
}

int	move_right(t_data *data)
{
	t_2float	new_pos;
	int			return_value;

	return_value = 0;
	new_pos = data->player_pos;
	new_pos.x -= cos(deg_to_rad(data->player_dir - 90)) * PLAYER_SPEED;
	if (!is_wall(data, new_pos, true))
		data->player_pos = new_pos;
	else
		return_value++;
	new_pos.y -= sin(deg_to_rad(data->player_dir - 90)) * PLAYER_SPEED;
	if (!is_wall(data, new_pos, true))
		data->player_pos = new_pos;
	else
		return_value++;
	return (return_value);
}
