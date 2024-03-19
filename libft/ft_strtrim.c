/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:03:01 by jongmoon          #+#    #+#             */
/*   Updated: 2023/03/24 19:17:47 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*s2;

	i = 0;
	while (s1[i] != 0 && ft_strchr(set, s1[i]) != NULL)
	{
		i++;
	}
	j = ft_strlen(s1);
	while (j > i && ft_strchr(set, s1[j]) != NULL)
	{
		j--;
	}
	s2 = ft_substr(s1, i, j - i + 1);
	return (s2);
}
