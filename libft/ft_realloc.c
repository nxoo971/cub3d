/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:37:54 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/24 23:53:16 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_realloc(char *dst, const char *src)
{
	char	*res;
	size_t	lendst;

	if (dst)
	{
		lendst = ft_strlen(dst);
		res = malloc(ft_strlen(src) + lendst + 1);
		if (res)
		{
			ft_strcpy(res, dst);
			ft_strcpy(res + lendst, src);
			free(dst);
			return (res);
		}
	}
	return (ft_strdup(src));
}
