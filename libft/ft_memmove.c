/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:48:10 by jongmoon          #+#    #+#             */
/*   Updated: 2023/03/19 20:21:03 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	j;

	if (dst <= src)
	{
		return (ft_memcpy(dst, src, len));
	}
	i = len - 1;
	j = 0;
	while (j < len)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
		i--;
		j++;
	}
	return (dst);
}
