/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_to_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:11:49 by vsoltys           #+#    #+#             */
/*   Updated: 2024/06/25 10:58:12 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// void	read_lenght_2(t_data *data, char *str, int i)
// {
// 	i = 0;
// 	while (1)
// 	{
// 		str = get_next_line(data->map.fd);
// 		if (str == NULL)
// 			break ;
// 		data->map.map[i] = ft_strdup(str);
// 		free(str);
// 		i++;
// 	}
// 	data->map.map[i] = NULL;
// 	close(data->map.fd);
// }

// void	read_lenght(t_data *data)
// {
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	data->map.map = NULL;
// 	data->map.fd = open(data->map.map_path, O_RDONLY);
// 	while (1)
// 	{
// 		str = get_next_line(data->map.fd);
// 		if (str == NULL)
// 			break ;
// 		i++;
// 		free(str);
// 	}
// 	free(str);
// 	str = NULL;
// 	close(data->map.fd);
// 	data->map.map = (char **)malloc(sizeof(char *) * (i + 1));
// 	data->map.fd = open(data->map.map_path, O_RDONLY);
// 	read_lenght_2(data, str, i);
// }

void	add_n(t_data *data)
{
	int		i;
	char	**temp;

	i = 0;
	if (!data->map.map || data->map.map[0][0] == '\0' || !data->map.map[0])
		exit_msg(data,
			"Error\n↪\t empty file after reading(arthur i hate you)", 1);
	while (data->map.map[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (data->map.map[i])
	{
		temp[i] = ft_strjoin(data->map.map[i], "\n");
		i++;
	}
	free_split(data->map.map);
	temp[i] = NULL;
	data->map.map = temp;
}

char	*read_lenght_norm(t_data *data, char *result)
{
	char	*temp;
	char	*str;

	str = NULL;
	temp = NULL;
	while (1)
	{
		str = get_next_line(data->map.fd);
		if (str == NULL)
			break ;
		if (result == NULL)
			result = ft_strdup(str);
		else
		{
			temp = ft_strjoin(result, str);
			free(result);
			result = ft_strdup(temp);
			free(temp);
		}
		free(str);
	}
	return (result);
	free(str);
	str = NULL;
}

void	read_lenght(t_data *data)
{
	char	*result;

	result = NULL;
	data->map.map = NULL;
	data->map.fd = open(data->map.map_path, O_RDONLY);
	result = read_lenght_norm(data, result);
	data->map.map = ft_split(result, '\n');
	free(result);
	add_n(data);
	close(data->map.fd);
}
