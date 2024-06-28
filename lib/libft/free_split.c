/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:21:42 by val               #+#    #+#             */
/*   Updated: 2024/05/23 13:03:29 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Libere un tableau de chaîne de caractères
void	free_split(char **table)
{
	int	j;

	j = 0;
	while (table[j])
	{
		free(table[j]);
		j++;
	}
	free(table);
}
