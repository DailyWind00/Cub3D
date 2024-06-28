/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:01:00 by valentins         #+#    #+#             */
/*   Updated: 2024/06/20 11:12:16 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <fcntl.h>
#include <stdio.h>

char	*extract_texture_path(char *str)
{
	int		i;
	int		j;
	char	*return_str;

	j = 2;
	while (str[j] == ' ')
		j++;
	i = j;
	while (str[i] && str[i] != '\n')
		i++;
	return_str = malloc(sizeof(char) * i + 1 - j);
	i = j;
	while (str[i] && str[i] != '\n')
	{
		return_str[i - j] = str[i];
		i++;
	}
	return_str[i - j] = '\0';
	return (return_str);
}

char	*extract_rgb_2(char *str, int *i, int *which_value)
{
	int		counter;
	int		counter_temp;
	char	*temp;

	counter = 0;
	counter_temp = 0;
	while (ft_isdigit(str[*i]) == 1 && str[*i] && str[*i] != ',')
	{
		(*i)++;
		counter++;
	}
	temp = malloc(sizeof(char) * counter + 1);
	*i -= counter;
	while (counter_temp != counter)
	{
		temp[counter_temp] = str[*i + counter_temp];
		counter_temp++;
	}
	temp[counter_temp] = '\0';
	*i += counter;
	(*which_value)++;
	return (temp);
}

t_3RGB	extract_rgb(t_data *data, char *str, t_3RGB return_value)
{
	int		i;
	int		which_value;
	char	*temp;

	i = 1;
	which_value = 0;
	while (str[i] && str[i] != '\n' && which_value != 3 && str[i] != '-')
	{
		if (ft_isdigit(str[i]) == 1)
		{
			temp = extract_rgb_2(str, &i, &which_value);
			if (which_value == 1)
				return_value.r = tcheck_max_rgb_value(data, temp, str);
			else if (which_value == 2)
				return_value.g = tcheck_max_rgb_value(data, temp, str);
			else if (which_value == 3)
				return_value.b = tcheck_max_rgb_value(data, temp, str);
			free(temp);
		}
		else if (str[i] == ' ' || str[i] == ',')
			i++;
		else
			exit_extract_rgb(data, str, "Error\n↪\trbg error");
	}
	return (return_value);
}

void	extract_value_2(t_data *data, char *str)
{
	if (str[0] == 'N' && str[1] == 'O')
	{
		if (data->texture_path.north_texture == NULL)
			data->texture_path.north_texture = extract_texture_path(str);
		else
			exit_extract_rgb(data, str, "Error\n↪\tdouble north");
	}
	if (str[0] == 'S' && str[1] == 'O')
	{
		if (data->texture_path.south_texture == NULL)
			data->texture_path.south_texture = extract_texture_path(str);
		else
			exit_extract_rgb(data, str, "Error\n↪\tdouble south");
	}
	if (str[0] == 'W' && str[1] == 'E')
	{
		if (data->texture_path.west_texture == NULL)
			data->texture_path.west_texture = extract_texture_path(str);
		else
			exit_extract_rgb(data, str, "Error\n↪\tdouble west");
	}
	extract_value_2_2(data, str);
}

int	extract_value(t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	tcheck_file(data);
	while (1)
	{
		str = get_next_line(data->map.fd);
		if (str == NULL)
			break ;
		extract_value_2(data, str);
		free(str);
		i++;
	}
	close(data->map.fd);
	extract_value_condition(data);
	return (0);
}
