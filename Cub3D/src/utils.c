/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:39:04 by vsoltys           #+#    #+#             */
/*   Updated: 2024/06/13 18:54:32 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	exit_msg(t_data *data, char *msg, int status)
{
	ft_printf("%s\n", msg);
	if (status)
		free_data(data);
	exit(1);
}

void	extract_value_condition(t_data *data)
{
	if (!data->texture_path.north_texture
		|| !data->texture_path.south_texture
		|| !data->texture_path.west_texture
		|| !data->texture_path.east_texture
		|| data->textures.ceiling_color.r == -1
		|| data->textures.ceiling_color.g == -1
		|| data->textures.ceiling_color.b == -1
		|| data->textures.floor_color.r == -1
		|| data->textures.floor_color.g == -1
		|| data->textures.floor_color.b == -1)
	{
		exit_msg(data, "Error\n↪\tTexture path or color not found\n", 1);
	}
}

double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	round_deg(float angle)
{
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}
