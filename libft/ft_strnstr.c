/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:05:47 by jongmoon          #+#    #+#             */
/*   Updated: 2023/03/24 18:49:41 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == 0)
	{
		return ((char *)haystack);
	}
	i = 0;
	while (i < len && haystack[i] != 0)
	{
		j = 0;
		while ((haystack[i + j] != 0 || needle[j] != 0) && i + j < len)
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
		}
		if (needle[j] == 0)
		{
			return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
