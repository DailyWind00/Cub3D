/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:42:14 by mgallais          #+#    #+#             */
/*   Updated: 2024/06/14 18:43:47 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	rgb_to_hex(t_data *data, t_3RGB color, int depth)
{
	int	red;
	int	green;
	int	blue;
	int	black;

	black = depth * 255 / (data->screen_size.y / 2);
	red = color.r * (255 - black) / 255;
	green = color.g * (255 - black) / 255;
	blue = color.b * (255 - black) / 255;
	return (ft_pixel(red, green, blue, 255));
}

void	background(t_data *data)
{
	t_2int	pos;
	int		color;

	pos.x = 0;
	pos.y = 0;
	while (pos.y < data->screen_size.y)
	{
		pos.x = 0;
		if (pos.y > data->screen_size.y / 2)
			color = rgb_to_hex(data, data->textures.floor_color,
					data->screen_size.y - pos.y);
		else
			color = rgb_to_hex(data,
					data->textures.ceiling_color, pos.y);
		while (pos.x < data->screen_size.x)
		{
			mlx_put_pixel(data->camera_view, pos.x, pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}

static void	put_rectangle(mlx_image_t *img, t_2int pos, t_2int size, int color)
{
	t_2int	incr;

	incr.y = 0;
	while (incr.y < size.y)
	{
		incr.x = 0;
		while (incr.x < size.x)
		{
			mlx_put_pixel(img, pos.x + incr.x, pos.y + incr.y, color);
			incr.x++;
		}
		incr.y++;
	}
}

void	minimap(t_data *data)
{
	t_2int	incr;

	incr = (t_2int){0, 0};
	incr.y = 0;
	while (data->map.map[incr.y])
	{
		incr.x = 0;
		while (data->map.map[incr.y][incr.x])
		{
			if (data->map.map[incr.y][incr.x] == '1')
				put_rectangle(data->camera_view,
					(t_2int){incr.x * 16, incr.y * 16},
					(t_2int){16, 16}, 0xAA08AAFF);
			incr.x++;
		}
		incr.y++;
	}
	put_rectangle(data->camera_view,
		(t_2int){(int)(data->player_pos.x * 16),
		(int)(data->player_pos.y * 16)}, (t_2int){2, 2}, 0xFF0202FF);
}
