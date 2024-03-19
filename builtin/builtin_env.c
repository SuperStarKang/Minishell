/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 20:17:36 by jongmoon          #+#    #+#             */
/*   Updated: 2023/12/30 12:43:47 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *str, int *flag)
{
	ft_putstr_fd("jksh: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	*flag = 1;
}

void	export_var(t_env *env_root, t_node	*temp, int *flag)
{
	char	*key;
	char	*value;
	char	*str;
	char	*p;
	int		i;

	while (temp != NULL)
	{
		str = temp->token->str;
		p = ft_strchr(str, '=');
		if (p == str)
			print_error(str, flag);
		else if (p != NULL)
		{
			i = p - str;
			key = ft_substr(str, 0, i);
			i++;
			value = ft_substr(str, i, ft_strlen(str) - i);
			insert_env(env_root, key, value);
			free(key);
		}
		temp = temp->next;
	}
}

void	builtin_export(t_env *env_root, t_node *cmd_node)
{
	int		flag;
	t_node	*temp;

	flag = 0;
	temp = cmd_node->next;
	if (temp == NULL)
	{
		builtin_env(env_root);
		update_recent_exit_status(env_root, 0);
		return ;
	}
	export_var(env_root, temp, &flag);
	update_recent_exit_status(env_root, flag);
}

void	builtin_unset(t_env *env_root, t_node *cmd_node)
{
	t_node	*temp;
	char	*key;

	temp = cmd_node->next;
	while (temp != NULL)
	{
		key = temp->token->str;
		remove_env(env_root, key);
		temp = temp->next;
	}
	update_recent_exit_status(env_root, 0);
}

void	builtin_env(t_env *env_root)
{
	t_env	*temp;

	temp = env_root->next;
	while (temp != NULL)
	{
		ft_putstr_fd(temp->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(temp->value, STDOUT_FILENO);
		temp = temp->next;
	}
	update_recent_exit_status(env_root, 0);
}
