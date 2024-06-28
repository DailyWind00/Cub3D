/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:05:09 by vsoltys           #+#    #+#             */
/*   Updated: 2024/06/17 15:58:07 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	convert_to_hex(uint32_t *texture_map, uint8_t *pixels)
{
	int		i;
	t_4int	color;

	i = 0;
	while (i < TEXTURE_SIZE * TEXTURE_SIZE)
	{
		color.r = pixels[i * 4];
		color.g = pixels[i * 4 + 1];
		color.b = pixels[i * 4 + 2];
		color.l = pixels[i * 4 + 3];
		texture_map[i] = ft_pixel(color.r, color.g, color.b, color.l);
		i++;
	}
}

uint32_t	apply_fog(uint32_t color, float fog_factor)
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	a = (color >> 24) & 0xFF;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (uint8_t)(r * fog_factor);
	g = (uint8_t)(g * fog_factor);
	b = (uint8_t)(b * fog_factor);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

uint8_t	*texture_pixel(t_data *data, t_raywall *rays)
{
	if (rays->wall_type == EAST)
		return (data->textures.east_texture->pixels);
	else if (rays->wall_type == WEST)
		return (data->textures.west_texture->pixels);
	else if (rays->wall_type == NORTH)
		return (data->textures.north_texture->pixels);
	else if (rays->wall_type == SOUTH)
		return (data->textures.south_texture->pixels);
	return (NULL);
}
