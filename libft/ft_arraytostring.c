/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraytostring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:39:43 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/24 23:52:55 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_array_to_string(char **array)
{
	char	*tostring;
	char	*tmp;
	int		i;

	i = 0;
	tostring = 0;
	while (array[i])
	{
		if (array[i + 1] == 0)
			tostring = ft_realloc(tostring, array[i]);
		else
		{
			tmp = ft_strjoin(array[i], " ");
			tostring = ft_realloc(tostring, tmp);
			ft_memdel((void **)& tmp);
		}
		i++;
	}
	return (tostring);
}
