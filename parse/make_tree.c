/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:45:40 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/29 20:28:47 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_node	*make_root(t_node *root)
{
	t_token	*token_pipe;
	t_node	*cmd_node;

	token_pipe = (t_token *)xmalloc(sizeof(t_token));
	token_pipe->str = ft_strdup("|");
	token_pipe->type = T_PIPE;
	cmd_node = (t_node *)xmalloc(sizeof(t_node));
	*cmd_node = (t_node){.left = 0, .right = 0, .next = 0, .token = 0};
	root = (t_node *)xmalloc(sizeof(t_node));
	*root = (t_node){.next = 0, .right = 0, \
					.left = cmd_node, .token = token_pipe};
	return (root);
}

void	make_pipe(t_node *root, t_node *new_node)
{
	t_node	*cmd_node;
	t_node	*tmp;

	cmd_node = (t_node *)xmalloc(sizeof(t_node));
	*cmd_node = (t_node){.left = 0, .right = 0, .next = 0, .token = 0};
	new_node->left = cmd_node;
	if (!(root->right))
		root->right = new_node;
	else
	{
		tmp = root;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new_node;
	}
}

void	make_word(t_node *root, t_node *new_node)
{
	t_node	*tmp;

	tmp = root;
	while (tmp->right)
		tmp = tmp->right;
	tmp = tmp->left;
	if (redir_have_sibling(tmp->left))
	{
		if (!(tmp->right))
			tmp->right = new_node;
		else
		{
			tmp = tmp->right;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_node;
		}
	}
	else
	{
		tmp = tmp->left;
		while (tmp->next)
			tmp = tmp->next;
		tmp->left = new_node;
	}
}

void	make_redir(t_node *root, t_node *new_node)
{
	t_node	*tmp;

	tmp = root;
	while (tmp->right)
		tmp = tmp->right;
	tmp = tmp->left;
	if (!(tmp->left))
		tmp->left = new_node;
	else
	{
		tmp = tmp->left;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_node	*make_tree(t_node *root, t_token *token)
{
	t_node	*new_node;

	if (!(token))
		return (root);
	new_node = (t_node *)xmalloc(sizeof(t_node));
	*new_node = (t_node){.left = 0, .right = 0, .next = 0, .token = token};
	if (!(root))
		root = make_root(root);
	if (token->type == T_PIPE)
		make_pipe(root, new_node);
	else
	{
		if (token->type == T_WORD)
			make_word(root, new_node);
		else
			make_redir(root, new_node);
	}
	return (root);
}
