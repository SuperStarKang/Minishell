/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:28:39 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 11:45:33 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	init_exec(t_exec *exec, t_env *env_root, int p_cnt, int *hdoc_ifds)
{
	exec->paths = 0;
	exec->argv = 0;
	exec->envp = 0;
	exec->cmd = 0;
	exec->pids = 0;
	exec->idx = 0;
	exec->pipe_count = p_cnt;
	exec->env_root = env_root;
	exec->hdoc_ifds = hdoc_ifds;
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

int	get_pipe_count(t_node *pipe_node)
{
	int	i;

	i = 0;
	while (pipe_node != NULL)
	{
		i++;
		pipe_node = pipe_node->right;
	}
	return (i);
}

char	**get_paths(t_env *env_root)
{
	char	*paths;

	paths = find_env(env_root, "PATH");
	if (paths != NULL)
	{
		return (ft_split(paths, ':'));
	}
	return (ft_split("", ':'));
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd("jksh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("command not found", 2);
}
