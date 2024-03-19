/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:09:16 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 12:23:43 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_piece	*make_piece(char *str)
{
	t_piece	*piece;

	piece = (t_piece *)malloc(sizeof(t_piece));
	if (piece == NULL)
	{
		exit(1);
	}
	piece->str = str;
	piece->next = NULL;
	return (piece);
}

static void	append_piece(t_piece *first, char *str)
{
	t_piece	*temp;

	temp = first;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = make_piece(str);
}

void	append_piece_substr(t_piece *first, char *str, int s, int e)
{
	char	*substr;

	substr = ft_substr(str, s, e - s);
	append_piece(first, substr);
}

void	append_piece_expanded(t_piece *first, t_env *env_root, char *key)
{
	char	*value;

	if (ft_strcmp(key, "") == 0)
	{
		append_piece(first, ft_strdup("$"));
		return ;
	}
	else if (ft_strcmp(key, "?") == 0)
	{
		append_piece(first, ft_strdup(env_root->value));
		return ;
	}
	value = find_env(env_root, key);
	if (value == NULL)
		value = "";
	append_piece(first, ft_strdup(value));
}

void	append_pieces_expanded(t_piece *first, t_env *env_root, char *str,
	int s)
{
	char	*p;
	int		i;

	p = ft_strchr(str, '$');
	while (p != NULL)
	{
		i = p - str;
		append_piece_substr(first, str, s, i - s);
		s = i++;
		while (str[i] != 0 && !is_special_character(str[i]))
			i++;
		if (str[i] == '?' && s + 1 == i)
		{
			append_piece_expanded(first, env_root, "?");
			i++;
		}
		else
		{
			append_piece_expanded_allocated(first, env_root,
				ft_substr(str, s + 1, i - (s + 1)));
		}
		s = i;
		p = ft_strchr(str + s, '$');
	}
	append_piece_substr(first, str, s, ft_strlen(str));
}
