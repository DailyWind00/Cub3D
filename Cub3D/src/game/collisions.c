/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:03:59 by mgallais          #+#    #+#             */
/*   Updated: 2024/06/13 19:00:17 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Check collision with a wall
bool	is_wall(t_data *data, t_2float pos, bool is_player)
{
	if (pos.x <= 0 || pos.y <= 0
		|| pos.x >= data->map.map_size.x
		|| pos.y >= data->map.map_size.y)
		return (true);
	if (!is_player)
	{
		if (data->map.map[(int)pos.y][(int)pos.x] == '1')
			return (true);
		return (false);
	}
	if (data->map.map[(int)(pos.y - 0.2f)][(int)(pos.x - 0.2f)] == '1'
		|| data->map.map[(int)(pos.y - 0.2f)][(int)(pos.x + 0.2f)] == '1'
		|| data->map.map[(int)(pos.y + 0.2f)][(int)(pos.x - 0.2f)] == '1'
		|| data->map.map[(int)(pos.y + 0.2f)][(int)(pos.x + 0.2f)] == '1')
		return (true);
	return (false);
}

// Check wall type
short	check_wall_type(t_2float ray_pos, float angle)
{
	t_2float	wall_pos;

	wall_pos.x = ray_pos.x + cos(deg_to_rad(angle)) * (RAY_SPEED / 5);
	wall_pos.y = ray_pos.y + sin(deg_to_rad(angle)) * (RAY_SPEED / 5);
	if ((int)wall_pos.x == (int)ray_pos.x)
	{
		if (wall_pos.y < ray_pos.y)
			return (NORTH);
		else
			return (SOUTH);
	}
	else
	{
		if (wall_pos.x < ray_pos.x)
			return (WEST);
		else
			return (EAST);
	}
}

// Check texture position
short	check_texture_pos(t_2float ray, t_raywall raywall)
{
	if (raywall.wall_type == NORTH)
		return ((int)(ray.x * 64) % TEXTURE_SIZE);
	else if (raywall.wall_type == EAST)
		return ((int)(ray.y * 64) % TEXTURE_SIZE);
	else if (raywall.wall_type == SOUTH)
		return (TEXTURE_SIZE - ((int)(ray.x * 64) % TEXTURE_SIZE) - 1);
	else
		return (TEXTURE_SIZE - ((int)(ray.y * 64) % TEXTURE_SIZE) - 1);
}
