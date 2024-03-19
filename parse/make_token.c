/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 20:01:58 by jongmoon          #+#    #+#             */
/*   Updated: 2023/12/30 12:18:27 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	tag_token(t_token *token)
{
	int	len;

	len = ft_strlen(token->str);
	if (token->type == T_SINGLE_LEFT_REDIR)
	{
		if (len == 2)
			token->type = T_DOUBLE_LEFT_REDIR;
		else if (len > 2)
			token->type = T_MORE_LEFT_REDIR;
	}
	else if (token->type == T_SINGLE_RIGHT_REDIR)
	{
		if (len == 2)
			token->type = T_DOUBLE_RIGHT_REDIR;
		else if (len > 2)
			token->type = T_MORE_RIGHT_REDIR;
	}
	else if (token->type == T_PIPE)
	{
		if (len > 1)
			token->type = T_MORE_PIPE;
	}
	else
		token->type = T_WORD;
}

static t_token	*make_token(int type, char *str)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		exit(1);
	}
	token->type = type;
	token->str = str;
	return (token);
}

static t_token	*get_token_internal(t_piece *piece, int token_type)
{
	char	*str;
	t_token	*token;

	str = merge_pieces(piece);
	if (str == NULL)
		return (NULL);
	token = make_token(token_type, str);
	tag_token(token);
	return (token);
}

static int	branch_out(t_line *line, t_piece *piece, t_env *env_root,
	t_check *check)
{
	if (check->is_squote)
		make_single_quote(line, piece, check);
	else if (check->is_dquote)
		make_double_quote(line, piece, env_root, check);
	else if (check->is_env)
		make_env(line, piece, env_root, check);
	else if ((line->str[check->idx] == '\'') || (line->str[check->idx] == '"'))
		is_qutote(line, piece, check);
	else if (line->str[check->idx] == '<')
		return (make_left_redir(line, piece, check));
	else if (line->str[check->idx] == '>')
		return (make_right_redir(line, piece, check));
	else if (line->str[check->idx] == '|')
	{
		is_pipe(line, piece, check);
		return (1);
	}
	else if (line->str[check->idx] == '$')
		is_dollar(line, piece, check);
	else
	{
		if (etc(line, piece, check))
			return (1);
	}
	return (0);
}

t_token	*get_token(t_line *line, t_env *env_root)
{
	t_check	check;
	t_piece	*piece;

	init_check(&check);
	check.start = line->i;
	if (line->str[check.start] == 0)
		return (NULL);
	check.idx = check.start;
	piece = make_piece(ft_strdup(""));
	while (line->str[check.idx] != 0)
	{
		if (branch_out(line, piece, env_root, &check))
			break ;
	}
	if (line->str[check.idx] == 0)
		append_piece_substr(piece, line->str, check.start, check.idx);
	line->i = check.idx;
	return (get_token_internal(piece, check.token_type));
}
