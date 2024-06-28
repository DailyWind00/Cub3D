/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:06:15 by mgallais          #+#    #+#             */
/*   Updated: 2024/06/25 10:33:23 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <fcntl.h>
#include <stdio.h>

int	all_around_0(char **map, int i, int j)
{
	if (i == 0 || j == 0 || i == (int)ft_strlen(map[i]) - 1
		|| j == (int)ft_strlen(map[i]) - 1)
		return (1);
	if ((map[i][j + 1] != '1' && map[i][j + 1] != '0')
		|| (map[i][j - 1] != '1' && map[i][j - 1] != '0'))
		return (1);
	if ((map[i + 1][j] != '1' && map[i + 1][j] != '0')
		|| (map[i + 1][j] != '1' && map[i + 1][j] != '0'))
		return (1);
	return (0);
}

int	find_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] == 'W'
				|| data->map.map[i][j] == 'N'
				|| data->map.map[i][j] == 'S'
				|| data->map.map[i][j] == 'E')
			{
				data->map.start_pos.x = i;
				data->map.start_pos.y = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	map_close(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (!find_player(data))
		return (1);
	data->map.map[data->map.start_pos.x][data->map.start_pos.y] = '0';
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] != '0' && data->map.map[i][j] != '1'
				&& data->map.map[i][j] != ' ' && data->map.map[i][j] != '\n')
				return (1);
			if (data->map.map[i][j] == '0')
				if (all_around_0(data->map.map, i, j))
					return (1);
			j++;
		}
		i++;
	}
	data->map.map[data->map.start_pos.x][data->map.start_pos.y]
		= data->map.player_start;
	return (0);
}

void	parsing(t_data *data, int argc, char **argv)
{
	if (argc != 2)
		return (ft_printf("Error\n↪\tWrong number of arguments\n"), exit (1));
	data->map.map_path = argv[1];
	extract_value(data);
	if (data->textures.ceiling_color.r == -1
		|| data->textures.ceiling_color.g == -1
		|| data->textures.ceiling_color.b == -1)
		return (ft_printf("Error\n↪\tCeiling color not valid\n"), exit (1));
	if (data->textures.floor_color.r == -1 || data->textures.floor_color.g == -1
		|| data->textures.floor_color.b == -1)
		return (ft_printf("Error\n↪\tFloor color not valid\n"), exit (1));
	read_lenght(data);
	table_to_map(data);
	if (map_close(data) == 1)
	{
		exit_msg(data, "Error\n↪\tParsing\n", 1);
	}
	find_map_size_and_player_pos(data);
	if (data->map.player_start == '+')
		return (ft_printf("Error\n↪\tPlayer position not found\n"), exit (1));
}
