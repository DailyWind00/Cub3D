/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:24:38 by vsoltys           #+#    #+#             */
/*   Updated: 2024/06/14 19:12:15 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	tcheck_max_rgb_value(t_data *data, char *temp, char *str)
{
	int	return_value;

	return_value = ft_atoi(temp);
	if (return_value > 255 || return_value < 0)
	{
		free(temp);
		free(str);
		while (1)
		{
			str = get_next_line(data->map.fd);
			if (str == NULL)
				break ;
			free(str);
		}
		exit_msg(data, "Error\n↪\tRGB value is not between 0 and 255", 1);
	}
	return (return_value);
}

void	tcheck_file(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.map_path[i])
		i++;
	if (data->map.map_path[i - 1] != 'b' || data->map.map_path[i - 2] != 'u'
		|| data->map.map_path[i - 3] != 'c' || data->map.map_path[i - 4] != '.')
		exit_msg(data, "Error\n↪\tMap file is not a .cub file", 0);
	data->map.fd = open(data->map.map_path, O_RDONLY | __O_DIRECTORY);
	if (data->map.fd != -1)
	{
		close(data->map.fd);
		exit_msg(data, "Error\n↪\tMap file is a directory", 0);
	}
	data->map.fd = open(data->map.map_path, O_RDONLY);
	if (data->map.fd == -1)
		exit_msg(data, "Error\n↪\tMap file not found", 0);
}

void	find_map_size_and_player_pos(t_data *data)
{
	t_3int	t;

	t = (t_3int){0, 0, 0};
	while (data->map.map[t.x] != NULL)
	{
		t.y = 0;
		while (data->map.map[t.x][t.y] != '\0')
		{
			if (data->map.map[t.x][t.y] == 'N' || data->map.map[t.x][t.y] == 'S'
				|| data->map.map[t.x][t.y] == 'W'
				|| data->map.map[t.x][t.y] == 'E')
			{
				data->player_pos.x = t.y + 0.5;
				data->player_pos.y = t.x + 0.5;
				data->map.map[t.x][t.y] = '0';
			}
			t.y++;
		}
		if (t.y > t.z)
			t.z = t.y;
		t.x++;
	}
	data->map.map_size.x = t.z;
	data->map.map_size.y = t.x;
}
