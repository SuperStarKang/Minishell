/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:00:14 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/29 20:09:59 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	redir_have_sibling(t_node *redir_node)
{
	if (!(redir_node))
		return (1);
	while (redir_node->next)
		redir_node = redir_node->next;
	if (!(redir_node->left))
		return (0);
	else
		return (1);
}

int	is_empty_piece(t_piece *first)
{
	return (first->next == NULL);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special_character(char c)
{
	return (c == '\'' || c == '"' || c == '<' || c == '>'
		|| c == '|' || c == '$' || is_space(c) || c == '?');
}

void	init_check(t_check *check)
{
	check->idx = 0;
	check->start = 0;
	check->is_squote = 0;
	check->is_dquote = 0;
	check->is_env = 0;
	check->token_type = T_NONE;
}
