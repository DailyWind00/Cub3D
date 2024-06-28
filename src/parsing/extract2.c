/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:01:23 by vsoltys           #+#    #+#             */
/*   Updated: 2024/06/20 11:18:02 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <fcntl.h>
#include <stdio.h>

void	extract_value_2_2(t_data *data, char *str)
{
	if (str[0] == 'E' && str[1] == 'A')
	{
		if (data->texture_path.east_texture == NULL)
			data->texture_path.east_texture = extract_texture_path(str);
		else
			exit_extract_rgb(data, str, "Error\n↪\tdouble east");
	}
	if (str[0] == 'F')
	{
		if (data->textures.floor_color.r == -1)
			data->textures.floor_color
				= extract_rgb(data, str, data->textures.floor_color);
		else
			exit_extract_rgb(data, str,
				"Error\n↪\tdouble definition of floor color");
	}
	if (str[0] == 'C')
	{
		if (data->textures.ceiling_color.r == -1)
			data->textures.ceiling_color = extract_rgb(data, str,
					data->textures.ceiling_color);
		else
			exit_extract_rgb(data, str,
				"Error\n↪\tdouble definition of ceiling color");
	}
}

void	exit_extract_rgb(t_data *data, char *str, char *error_msg)
{
	free(str);
	while (1)
	{
		str = get_next_line(data->map.fd);
		if (str == NULL)
			break ;
		free(str);
	}
	exit_msg(data, error_msg, 1);
}
