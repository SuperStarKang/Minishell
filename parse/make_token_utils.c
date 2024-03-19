/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:14:11 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 12:25:15 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	etc(t_line *line, t_piece *piece, t_check *check)
{
	if (is_space(line->str[check->idx]))
	{
		if (check->start < check->idx)
			append_piece_substr(piece, line->str, check->start, check->idx);
		while (is_space(line->str[check->idx]))
			check->idx++;
		check->start = check->idx;
		return (1);
	}
	check->idx++;
	return (0);
}

void	make_env(t_line *line, t_piece *piece, t_env *env_root, t_check *check)
{
	char	*temp;

	while (line->str[check->idx] != 0
		&& !is_special_character(line->str[check->idx]))
		check->idx++;
	if (line->str[check->idx] == '?' && check->start + 1 == check->idx)
	{
		append_piece_expanded(piece, env_root, "?");
		check->idx++;
	}
	else
	{
		temp = ft_substr(line->str, check->start + 1,
				check->idx - (check->start + 1));
		append_piece_expanded(piece, env_root, temp);
		free(temp);
	}
	check->start = check->idx;
	check->is_env = 0;
}

void	make_double_quote(t_line *line, t_piece *piece, t_env *env_root,
	t_check *check)
{
	char	*temp;

	while (line->str[check->idx] != 0 && line->str[check->idx] != '"')
		check->idx++;
	if (line->str[check->idx] == '"')
	{
		temp = ft_substr(line->str, check->start + 1,
				check->idx - (check->start + 1));
		append_pieces_expanded(piece, env_root, temp, 0);
		check->idx++;
		free(temp);
	}
	else
	{
		temp = ft_substr(line->str, check->start, check->idx - check->start);
		append_pieces_expanded(piece, env_root, temp, 0);
		free(temp);
	}
	check->start = check->idx;
	check->is_dquote = 0;
}

void	make_single_quote(t_line *line, t_piece *piece, t_check *check)
{
	while (line->str[check->idx] != 0 && line->str[check->idx] != '\'')
		check->idx++;
	if (line->str[check->idx] == '\'')
	{
		append_piece_substr(piece, line->str, check->start + 1, check->idx);
		check->idx++;
	}
	else
		append_piece_substr(piece, line->str, check->start, check->idx);
	check->start = check->idx;
	check->is_squote = 0;
}
