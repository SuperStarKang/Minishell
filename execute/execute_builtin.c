/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:32:00 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/29 19:32:10 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_builtin(t_node *cmd_node)
{
	char	*str;

	if (cmd_node == NULL)
		return (0);
	str = cmd_node->token->str;
	return (ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0);
}

int	run_builtin(t_env *env_root, t_node *cmd_node)
{
	char	*str;

	if (cmd_node == NULL)
		return (0);
	str = cmd_node->token->str;
	if (ft_strcmp(str, "echo") == 0)
		builtin_echo(env_root, cmd_node);
	else if (ft_strcmp(str, "cd") == 0)
		builtin_cd(env_root, cmd_node);
	else if (ft_strcmp(str, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(str, "export") == 0)
		builtin_export(env_root, cmd_node);
	else if (ft_strcmp(str, "unset") == 0)
		builtin_unset(env_root, cmd_node);
	else if (ft_strcmp(str, "env") == 0)
		builtin_env(env_root);
	else if (ft_strcmp(str, "exit") == 0)
		builtin_exit(cmd_node);
	else
		return (0);
	return (1);
}
