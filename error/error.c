/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:49:37 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 12:26:33 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_have_file(t_node *redir_node)
{
	t_node	*tmp_node;

	tmp_node = redir_node;
	while (tmp_node)
	{
		if (!(tmp_node->left))
			return (1);
		tmp_node = tmp_node->next;
	}
	return (0);
}

int	check_redir(t_node *redir_node)
{
	if (redir_node->token->type >= T_MORE_LEFT_REDIR
		&& redir_node->token->type <= T_MORE_PIPE)
	{
		ft_putendl_fd("syntax error", 2);
		return (1);
	}
	if (redir_node->token->type >= T_SINGLE_LEFT_REDIR
		&& redir_node->token->type <= T_DOUBLE_RIGHT_REDIR)
	{
		if (redir_have_file(redir_node))
		{
			ft_putendl_fd("syntax error near unexpected token 'redirection'",
				2);
			return (1);
		}
	}
	return (0);
}

int	syntax_error_check(t_node *root)
{
	t_node	*pipe_node;

	pipe_node = root;
	while (pipe_node)
	{
		if (!(pipe_node->left->left) && !(pipe_node->left->right))
		{
			ft_putendl_fd("syntax error near unexpected token `|'", 2);
			free_tree(root);
			return (1);
		}
		if (pipe_node->left->left)
		{
			if (check_redir(pipe_node->left->left))
			{
				free_tree(root);
				return (1);
			}
		}
		pipe_node = pipe_node->right;
	}
	return (0);
}
