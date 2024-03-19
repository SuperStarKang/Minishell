/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:58:51 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 12:26:08 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../minishell.h"

typedef struct s_check {
	int	idx;
	int	start;
	int	is_squote;
	int	is_dquote;
	int	is_env;
	int	token_type;
}	t_check;

typedef struct s_piece {
	char			*str;
	struct s_piece	*next;
}	t_piece;

// token
t_token	*get_token(t_line *line, t_env *env_root);

// token_utils
void	make_single_quote(t_line *line, t_piece *piece, t_check *check);
void	make_double_quote(t_line *line, t_piece *piece, t_env *env_root,
			t_check *check);
void	make_env(t_line *line, t_piece *piece, t_env *env_root, t_check *check);
int		etc(t_line *line, t_piece *piece, t_check *check);

// piece
t_piece	*make_piece(char *str);
void	append_piece_substr(t_piece *first, char *str, int s, int e);
void	append_piece_expanded(t_piece *first, t_env *env_root, char *key);
void	append_pieces_expanded(t_piece *first, t_env *env_root, char *str,
			int s);

// piece_utils
char	*merge_pieces(t_piece *piece);
void	free_pieces(t_piece *piece);
void	append_piece_expanded_allocated(t_piece *first, t_env *env_root,
			char *key);

// check
void	is_pipe(t_line *line, t_piece *piece, t_check *check);
int		make_right_redir(t_line *line, t_piece *piece, t_check *check);
int		make_left_redir(t_line *line, t_piece *piece, t_check *check);
void	is_qutote(t_line *line, t_piece *piece, t_check *check);
void	is_dollar(t_line *line, t_piece *piece, t_check *check);

// utils
int		redir_have_sibling(t_node *redir_node);
int		is_space(char c);
int		is_special_character(char c);
int		is_empty_piece(t_piece *first);
void	init_check(t_check *check);

#endif