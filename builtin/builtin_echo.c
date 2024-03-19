/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 20:17:18 by jongmoon          #+#    #+#             */
/*   Updated: 2023/12/29 19:17:13 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*check_option(t_node *temp, int *opt)
{
	char	*str;
	int		i;

	while (temp != NULL)
	{
		str = temp->token->str;
		if (str[0] != '-' || str[1] != 'n')
			break ;
		i = 1;
		while (str[i] == 'n')
			i++;
		if (str[i] == 0)
			*opt = 1;
		else
			break ;
		temp = temp->next;
	}
	return (temp);
}

void	builtin_echo(t_env *env_root, t_node *cmd_node)
{
	t_node	*temp;
	int		opt;

	opt = 0;
	temp = check_option(cmd_node->next, &opt);
	while (temp != NULL)
	{
		ft_putstr_fd(temp->token->str, STDOUT_FILENO);
		if (temp->next != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		temp = temp->next;
	}
	if (!opt)
		ft_putchar_fd('\n', STDOUT_FILENO);
	update_recent_exit_status(env_root, 0);
}
