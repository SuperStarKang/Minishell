/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:07:04 by jongmoon          #+#    #+#             */
/*   Updated: 2023/03/25 19:01:41 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(char const *s, char c)
{
	int		flag;
	size_t	size;
	size_t	i;

	flag = 0;
	size = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (!flag && s[i] != c)
		{
			flag = 1;
		}
		else if (flag && s[i] == c)
		{
			flag = 0;
			size++;
		}
		i++;
	}
	if (flag)
	{
		size++;
	}
	return (size);
}

static size_t	get_word(char const *s, char c, char **word)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] == c)
	{
		i++;
	}
	j = 0;
	while (s[i + j] != 0 && s[i + j] != c)
	{
		j++;
	}
	*word = (char *)malloc(sizeof(char) * (j + 1));
	if (*word != NULL)
	{
		ft_strlcpy(*word, s + i, j + 1);
	}
	return (i + j);
}

static void	clear_words(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	char	**arr;
	size_t	i;
	size_t	j;

	size = get_size(s, c);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (arr != NULL)
	{
		i = 0;
		j = 0;
		while (j < size)
		{
			i += get_word(s + i, c, arr + j);
			if (arr[j] == NULL)
			{
				clear_words(arr, j);
				return (NULL);
			}
			j++;
		}
		arr[size] = NULL;
	}
	return (arr);
}
