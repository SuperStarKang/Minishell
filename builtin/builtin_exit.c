/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 20:17:49 by jongmoon          #+#    #+#             */
/*   Updated: 2023/12/30 11:31:45 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_exit(t_node *cmd_node)
{
	int	status;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd_node->next == NULL)
	{
		exit(0);
	}
	else if (cmd_node->next->next == NULL)
	{
		if (ft_isdigit(cmd_node->next->token->str[0]))
		{
			status = ft_atoi(cmd_node->next->token->str);
			exit(status);
		}
		else
		{
			ft_putendl_fd("jksh: exit: numeric argument required", 2);
			exit(255);
		}
	}
	else
	{
		ft_putendl_fd("jksh: exit: too many arguments", 2);
	}
}
