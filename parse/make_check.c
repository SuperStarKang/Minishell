/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:04:15 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/29 20:08:23 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	is_pipe(t_line *line, t_piece *piece, t_check *check)
{
	if (check->start < check->idx)
	{
		append_piece_substr(piece, line->str, check->start, check->idx);
		check->start = check->idx;
	}
	if (!is_empty_piece(piece))
		return ;
	check->token_type = T_PIPE;
	while (line->str[check->idx] != 0 && line->str[check->idx] == '|')
		check->idx++;
	append_piece_substr(piece, line->str, check->start, check->idx);
	check->start = check->idx;
}

int	make_right_redir(t_line *line, t_piece *piece, t_check *check)
{
	if (check->start < check->idx)
	{
		append_piece_substr(piece, line->str, check->start, check->idx);
		check->start = check->idx;
	}
	if (!is_empty_piece(piece))
		return (1);
	check->token_type = T_SINGLE_RIGHT_REDIR;
	while (line->str[check->idx] != 0 && line->str[check->idx] == '>')
		check->idx++;
	append_piece_substr(piece, line->str, check->start, check->idx);
	check->start = check->idx;
	return (1);
}

int	make_left_redir(t_line *line, t_piece *piece, t_check *check)
{
	if (check->start < check->idx)
	{
		append_piece_substr(piece, line->str, check->start, check->idx);
		check->start = check->idx;
	}
	if (!is_empty_piece(piece))
		return (1);
	check->token_type = T_SINGLE_LEFT_REDIR;
	while (line->str[check->idx] != 0 && line->str[check->idx] == '<')
		check->idx++;
	append_piece_substr(piece, line->str, check->start, check->idx);
	check->start = check->idx;
	return (1);
}

void	is_qutote(t_line *line, t_piece *piece, t_check *check)
{
	if (line->str[check->idx] == '\'')
	{
		append_piece_substr(piece, line->str, check->start, check->idx);
		check->is_squote = 1;
		check->start = check->idx;
		check->idx++;
	}
	else if (line->str[check->idx] == '"')
	{
		append_piece_substr(piece, line->str, check->start, check->idx);
		check->is_dquote = 1;
		check->start = check->idx;
		check->idx++;
	}
}

void	is_dollar(t_line *line, t_piece *piece, t_check *check)
{
	append_piece_substr(piece, line->str, check->start, check->idx);
	check->is_env = 1;
	check->start = check->idx;
	check->idx++;
}
