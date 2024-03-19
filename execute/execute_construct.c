/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_construct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:46:32 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/29 20:48:38 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern int	g_signo;

char	**construct_argv(t_node *cmd_node)
{
	t_node	*temp;
	char	**argv;
	int		cnt;

	cnt = 0;
	temp = cmd_node;
	while (temp != NULL)
	{
		cnt++;
		temp = temp->next;
	}
	argv = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (argv == NULL)
		exit(1);
	argv[cnt] = NULL;
	cnt = 0;
	temp = cmd_node;
	while (temp != NULL)
	{
		argv[cnt] = temp->token->str;
		cnt++;
		temp = temp->next;
	}
	return (argv);
}

char	**construct_envp(t_env *env_root)
{
	t_env	*temp;
	char	**envp;
	char	*key;
	int		cnt;

	cnt = 0;
	temp = env_root->next;
	while (temp != NULL)
	{
		cnt++;
		temp = temp->next;
	}
	envp = (char **)xmalloc(sizeof(char *) * (cnt + 1));
	envp[cnt] = NULL;
	cnt = 0;
	temp = env_root->next;
	while (temp != NULL)
	{
		key = ft_strjoin(temp->key, "=");
		envp[cnt] = ft_strjoin(key, temp->value);
		free(key);
		cnt++;
		temp = temp->next;
	}
	return (envp);
}

void	update_status(t_exec *exec)
{
	int	status;

	exec->idx = 0;
	while (exec->idx < exec->pipe_count)
	{
		waitpid(exec->pids[exec->idx], &status, 0);
		exec->idx++;
	}
	free(exec->pids);
	if (WIFSIGNALED(status))
		update_recent_exit_status(exec->env_root, 128 + WTERMSIG(status));
	else
		update_recent_exit_status(exec->env_root, WEXITSTATUS(status));
	g_signo = 0;
}
