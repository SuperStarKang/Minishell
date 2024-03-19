/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:19:19 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 11:14:17 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signo;

void	default_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sigint_handler(int signo)
{
	pid_t	pid;
	int		status;

	g_signo = signo;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	sigquit_handler(int signo)
{
	pid_t	pid;
	int		status;

	(void)signo;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", STDOUT_FILENO);
	}
	else
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	set_signal(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("signal()");
		exit(1);
	}
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
	{
		perror("signal()");
		exit(1);
	}
}
