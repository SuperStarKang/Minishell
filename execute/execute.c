/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 20:03:19 by jongmoon          #+#    #+#             */
/*   Updated: 2023/12/30 11:26:37 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern int	g_signo;

static void	execute_left_redir(int *heredoc_ifd, char *str, int type)
{
	int	ifd;

	if (type == T_SINGLE_LEFT_REDIR)
	{
		ifd = open(str, O_RDONLY);
		if (ifd == -1)
		{
			perror(NULL);
			exit(1);
		}
		dup2(ifd, 0);
		close(ifd);
	}
	else if (type == T_DOUBLE_LEFT_REDIR)
	{
		ifd = *heredoc_ifd;
		if (ifd != -1)
		{
			dup2(ifd, 0);
			close(ifd);
			*heredoc_ifd = -1;
		}
	}	
}

static void	execute_right_redir(char *str, int type)
{
	int	ofd;

	if (type == T_SINGLE_RIGHT_REDIR)
	{
		ofd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ofd == -1)
		{
			perror(NULL);
			exit(1);
		}
		dup2(ofd, 1);
		close(ofd);
	}
	else if (type == T_DOUBLE_RIGHT_REDIR)
	{
		ofd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (ofd == -1)
		{
			perror(NULL);
			exit(1);
		}
		dup2(ofd, 1);
		close(ofd);
	}
}

void	redir(t_node *redir_node, int *heredoc_ifd)
{
	char	*str;
	int		type;

	while (redir_node != NULL)
	{
		type = redir_node->token->type;
		str = redir_node->left->token->str;
		execute_left_redir(heredoc_ifd, str, type);
		execute_right_redir(str, type);
		redir_node = redir_node->next;
	}
}

static void	exec_child(t_node *pipe_node, t_exec *exec)
{
	t_node	*redir_node;
	t_node	*cmd_node;

	default_signal();
	close(exec->fds[0]);
	if (exec->idx < exec->pipe_count - 1)
		dup2(exec->fds[1], 1);
	close(exec->fds[1]);
	redir_node = pipe_node->left->left;
	redir(redir_node, &exec->hdoc_ifds[exec->idx]);
	cmd_node = pipe_node->left->right;
	if (cmd_node == NULL)
		exit(0);
	if (is_builtin(cmd_node))
	{
		run_builtin(exec->env_root, cmd_node);
		exit(ft_atoi(exec->env_root->value));
	}
	exec->paths = get_paths(exec->env_root);
	exec->argv = construct_argv(cmd_node);
	exec->cmd = search_cmd(exec->paths, exec->argv[0]);
	exec->envp = construct_envp(exec->env_root);
	free_paths(exec->paths);
	execve(exec->cmd, exec->argv, exec->envp);
	exit(1);
}

void	exec_tree(t_node *p_node, t_env *env_root, int p_cnt, int *hdoc_ifds)
{
	t_exec	exec;
	int		pid;

	init_exec(&exec, env_root, p_cnt, hdoc_ifds);
	exec.idx = 0;
	exec.pids = (int *)xmalloc(sizeof(int) * p_cnt);
	while (p_node != NULL)
	{
		pipe(exec.fds);
		pid = fork();
		if (pid == 0)
			exec_child(p_node, &exec);
		close(exec.fds[1]);
		dup2(exec.fds[0], 0);
		close(exec.fds[0]);
		exec.pids[exec.idx] = pid;
		exec.idx++;
		p_node = p_node->right;
	}
	update_status(&exec);
}
