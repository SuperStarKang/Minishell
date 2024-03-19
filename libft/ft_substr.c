/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 05:26:02 by jongmoon          #+#    #+#             */
/*   Updated: 2023/03/24 19:10:33 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	while (s[i] != 0 && i < start)
	{
		i++;
	}
	j = 0;
	while (s[i + j] != 0 && j < len)
	{
		j++;
	}
	str = (char *)malloc(sizeof(char) * (j + 1));
	if (str != NULL)
	{
		ft_strlcpy(str, s + i, j + 1);
	}
	return (str);
}
