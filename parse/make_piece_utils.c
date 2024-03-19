/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_piece_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:10:40 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 12:23:35 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_pieces(t_piece *piece)
{
	t_piece	*temp;
	t_piece	*next;

	temp = piece;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp->str);
		free(temp);
		temp = next;
	}
}

char	*merge_pieces(t_piece *piece)
{
	char	*before_str;
	char	*after_str;
	t_piece	*temp;

	if (is_empty_piece(piece))
	{
		free_pieces(piece);
		return (NULL);
	}
	after_str = ft_strdup("");
	temp = piece;
	while (temp != NULL)
	{
		before_str = after_str;
		after_str = ft_strjoin(before_str, temp->str);
		free(before_str);
		temp = temp->next;
	}
	free_pieces(piece);
	return (after_str);
}

void	append_piece_expanded_allocated(t_piece *first, t_env *env_root,
	char *key)
{
	append_piece_expanded(first, env_root, key);
	free(key);
}
