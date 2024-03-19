/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:08:56 by jongmoon          #+#    #+#             */
/*   Updated: 2023/03/18 12:14:35 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str != NULL)
	{
		i = 0;
		while (s[i] != 0)
		{
			str[i] = f(i, s[i]);
			i++;
		}
		str[i] = 0;
	}
	return (str);
}
