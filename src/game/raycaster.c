/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:18:09 by mgallais          #+#    #+#             */
/*   Updated: 2024/06/20 10:36:34 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

uint32_t	draw_rays_2(t_data *data, t_2int incr, t_raywall *rays, t_2int y)
{
	float		fog_factor;
	uint32_t	*texture;
	uint32_t	color;

	texture = NULL;
	if (rays[incr.x].wall_type == EAST)
		texture = data->textures.east_pixel;
	else if (rays[incr.x].wall_type == WEST)
		texture = data->textures.west_pixel;
	else if (rays[incr.x].wall_type == NORTH)
		texture = data->textures.north_pixel;
	else if (rays[incr.x].wall_type == SOUTH)
		texture = data->textures.south_pixel;
	y.y = ((incr.y - (data->screen_size.y
					/ 2 - y.x / 2)) * TEXTURE_SIZE) / y.x;
	fog_factor = 1.0 - fminf(rays[incr.x].distance
			/ MAX_DISTANCE * 15.0, 1.0);
	color = texture[TEXTURE_SIZE * y.y
		+ (rays[incr.x].texture_pos)];
	color = apply_fog(color, fog_factor);
	return (color);
}

void	draw_rays(t_data *data, t_raywall *rays)
{
	t_2int		y_height;
	t_2int		incr;

	incr.x = 0;
	while (incr.x != data->screen_size.x)
	{
		y_height.x = (data->screen_size.y * 0.5f)
			/ tan(FOV * 0.5f) / rays[incr.x].distance * 5;
		incr.y = (data->screen_size.y / 2 - y_height.x / 2);
		while (incr.y != data->screen_size.y / 2 + y_height.x / 2)
		{
			if (incr.y < 0 || incr.y >= data->screen_size.y)
			{
				incr.y++;
				continue ;
			}
			mlx_put_pixel(data->camera_view, incr.x, incr.y,
				draw_rays_2(data, incr, rays, y_height));
			incr.y++;
		}
		incr.x++;
	}
}

static t_raywall	single_raycast(t_data *data, float angle)
{
	t_2float	ray_pos;
	t_raywall	ray;

	(ray_pos) = data->player_pos;
	while (!is_wall(data, ray_pos, false))
	{
		ray_pos.x += cos(deg_to_rad(angle)) * RAY_SPEED;
		ray_pos.y += sin(deg_to_rad(angle)) * RAY_SPEED;
	}
	while (is_wall(data, ray_pos, false))
	{
		ray_pos.x -= cos(deg_to_rad(angle)) * (RAY_SPEED / 5);
		ray_pos.y -= sin(deg_to_rad(angle)) * (RAY_SPEED / 5);
	}
	ray.distance = sqrt(pow(data->player_pos.x - ray_pos.x, 2)
			+ pow(data->player_pos.y - ray_pos.y, 2));
	ray.distance = ray.distance * cos(deg_to_rad(data->player_dir - angle));
	if (ray.distance < 0.5f)
		ray.distance = 0.5f;
	ray.wall_type = check_wall_type(ray_pos, angle);
	ray.texture_pos = check_texture_pos(ray_pos, ray);
	return (ray);
}

static float	find_angle(t_data *data, int i)
{
	float	angle;

	angle = data->player_dir - (FOV / 2) + (i * FOV / data->screen_size.x);
	return (round_deg(angle));
}

// Raycasting function called when the player or the camera moves
void	new_raycast(t_data *data)
{
	t_raywall	*rays;
	int			i;

	i = 0;
	rays = malloc(sizeof(t_raywall) * data->screen_size.x);
	while (i != data->screen_size.x)
	{
		rays[i] = single_raycast(data, find_angle(data, i));
		i++;
	}
	draw_rays(data, rays);
	free(rays);
}
