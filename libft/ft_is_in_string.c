/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:43:23 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/25 01:23:40 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int	ft_is_in_string(const char *s, const char *charset)
{
	size_t	i;
	size_t	k;

	k = 0;
	while (s[k])
	{
		i = 0;
		while (charset[i])
		{
			if (charset[i] == s[k])
				return (k);
			i++;
		}
		k++;
	}
	return (-1);
}
