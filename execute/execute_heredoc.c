/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:32:32 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/29 19:48:59 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	close_heredoc(int *heredoc_ifds, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (heredoc_ifds[i] != -1)
		{
			close(heredoc_ifds[i]);
		}
		i++;
	}
}

static void	get_here_doc(char *limiter, int ofd)
{
	char	*str;

	while (1)
	{
		str = readline("heredoc> ");
		if (str == NULL)
		{
			break ;
		}
		else if (ft_strcmp(str, limiter) == 0)
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, ofd);
		free(str);
	}
	close(ofd);
}

static int	execute_pre_heredoc(t_node *redir_node, int *heredoc_ifds, int i)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	if (heredoc_ifds[i] != -1)
		close(heredoc_ifds[i]);
	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		default_signal();
		close(fds[0]);
		get_here_doc(redir_node->left->token->str, fds[1]);
		exit(0);
	}
	close(fds[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		heredoc_ifds[i] = -1;
		return (WTERMSIG(status));
	}
	heredoc_ifds[i] = fds[0];
	return (0);
}

int	pre_heredoc(t_node *pipe_node, int *heredoc_ifds)
{
	t_node	*redir_node;
	int		status;
	int		i;

	i = 0;
	while (pipe_node != NULL)
	{
		redir_node = pipe_node->left->left;
		while (redir_node != NULL)
		{
			if (redir_node->token->type == T_DOUBLE_LEFT_REDIR)
			{
				status = execute_pre_heredoc(redir_node, heredoc_ifds, i);
				if (status != 0)
					return (status);
			}
			redir_node = redir_node->next;
		}
		i++;
		pipe_node = pipe_node->right;
	}
	return (0);
}
