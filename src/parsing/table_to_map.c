/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_to_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:29:14 by val               #+#    #+#             */
/*   Updated: 2024/06/20 14:21:11 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	player_dir(t_data *data)
{
	if (data->map.player_start == 'N')
		data->player_dir = 270;
	else if (data->map.player_start == 'E')
		data->player_dir = 0;
	else if (data->map.player_start == 'S')
		data->player_dir = 90;
	else if (data->map.player_start == 'W')
		data->player_dir = 180;
}

void	table_to_map_2(t_data *data, int k, int i)
{
	char	**map;
	int		j;

	j = 0;
	map = (char **)malloc(sizeof(char *) * (k - i + 2));
	while (i <= k)
	{
		map[j] = ft_strdup(data->map.map[i]);
		i++;
		j++;
	}
	map[j] = NULL;
	free_split(data->map.map);
	data->map.map = map;
}

int	table_to_map_3(t_data *data, t_4int i)
{
	while (data->map.map[i.r][i.g])
	{
		if ((data->map.map[i.r][i.g] == 'N'
			|| data->map.map[i.r][i.g] == 'S'
			|| data->map.map[i.r][i.g] == 'W'
			|| data->map.map[i.r][i.g] == 'E'))
		{
			if (data->map.player_start != '+')
				exit_msg(data, "Error\n↪\tMultiple player start\n", 1);
			data->map.player_start = data->map.map[i.r][i.g];
			player_dir(data);
		}
		else if (data->map.map[i.r][i.g] != ' '
			&& data->map.map[i.r][i.g] != '1' && data->map.map[i.r][i.g] != '0'
			&& data->map.map[i.r][i.g] != '\n')
			return (table_to_map_2(data, i.l, i.r + 1), 1);
		i.g++;
	}
	return (0);
}

void	table_to_map(t_data *data)
{
	t_4int	i;

	i.r = 0;
	i.g = 0;
	i.b = 0;
	data->map.player_start = '+';
	while (data->map.map[i.r] != NULL)
		i.r++;
	i.r -= 1;
	i.l = i.r;
	while (i.r != 0)
	{
		if (!data->map.map[i.r])
			return (table_to_map_2(data, i.l, i.r + 1));
		if (data->map.map[i.r][i.g] == '\n')
			return (table_to_map_2(data, i.l, i.r + 1));
		if (table_to_map_3(data, i) == 1)
			return ;
		i.g = 0;
		if (i.b != 0)
			break ;
		i.r--;
	}
	exit(1);
}
