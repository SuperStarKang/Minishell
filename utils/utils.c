/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:36:53 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 11:40:46 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!(ptr))
	{
		perror("malloc");
		exit(1);
	}
	return (ptr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != 0 || s2[i] != 0)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

void	free_tree_token(t_node *node)
{
	if (node)
	{
		if (node->token)
		{
			if (node->token->str)
				free(node->token->str);
			free(node->token);
		}
	}
}

void	free_tree(t_node *root)
{
	if (root)
	{
		free_tree(root->left);
		free_tree(root->right);
		free_tree(root->next);
		free_tree_token(root);
		free(root);
	}
}
