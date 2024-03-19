/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:07:35 by jongmoon          #+#    #+#             */
/*   Updated: 2023/03/26 14:37:50 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_length(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
	{
		len++;
	}
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	_ft_itoa(int n, char *str, size_t i, size_t len)
{
	if (n == -2147483648)
	{
		ft_memcpy(str, "-2147483648", 11);
	}
	else if (n < 0)
	{
		str[i] = '-';
		_ft_itoa(-n, str + 1, i, len - 1);
	}
	else if (n >= 10)
	{
		_ft_itoa(n / 10, str, i, len - 1);
		_ft_itoa(n % 10, str, len - 1 - i, len);
	}
	else
	{
		str[i] = '0' + n;
	}
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	len = get_length(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str != NULL)
	{
		_ft_itoa(n, str, 0, len);
		str[len] = 0;
	}
	return (str);
}
