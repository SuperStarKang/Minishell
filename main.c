/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 20:03:16 by jongmoon          #+#    #+#             */
/*   Updated: 2023/12/30 12:10:10 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signo;

t_line	*make_line(char *str)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (line == NULL)
	{
		exit(1);
	}
	line->str = str;
	line->i = 0;
	return (line);
}

t_node	*create_tree(t_line *line, t_env *env_root, char *str)
{
	t_token	*token;
	t_node	*tree_root;

	tree_root = NULL;
	while (1)
	{
		token = get_token(line, env_root);
		if (token == NULL)
		{
			if (str[line->i] == 0)
				break ;
			continue ;
		}
		tree_root = make_tree(tree_root, token);
	}
	return (tree_root);
}

void	execute_cmd(t_node *tree_root, t_env *env_root)
{
	int		pipe_count;
	int		heredoc_status;
	int		*heredoc_ifds;

	pipe_count = get_pipe_count(tree_root);
	heredoc_ifds = (int *)malloc(sizeof(int) * pipe_count);
	ft_memset(heredoc_ifds, -1, sizeof(int) * pipe_count);
	heredoc_status = pre_heredoc(tree_root, heredoc_ifds);
	if (heredoc_status != 0)
	{
		update_recent_exit_status(env_root, 128 + heredoc_status);
		g_signo = 0;
	}
	else
	{
		if (pipe_count == 1 && is_builtin(tree_root->left->right))
		{
			redir(tree_root->left->left, &heredoc_ifds[0]);
			run_builtin(env_root, tree_root->left->right);
		}
		else
			exec_tree(tree_root, env_root, pipe_count, heredoc_ifds);
	}
	close_heredoc(heredoc_ifds, pipe_count);
	free(heredoc_ifds);
}

void	run_shell(t_env *env_root, int original_ifd, int original_ofd)
{
	char	*str;
	t_line	*line;
	t_node	*tree_root;

	while (1)
	{
		set_signal();
		str = readline("jksh> ");
		if (str == NULL)
			break ;
		if (g_signo == SIGINT)
			update_recent_exit_status(env_root, 1);
		g_signo = 0;
		line = make_line(str);
		tree_root = create_tree(line, env_root, str);
		free(line);
		add_history(str);
		free(str);
		if (syntax_error_check(tree_root))
			continue ;
		execute_cmd(tree_root, env_root);
		dup2(original_ifd, 0);
		dup2(original_ofd, 1);
		free_tree(tree_root);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env_root;

	(void)argv;
	if (argc != 1)
		exit(1);
	set_signal();
	env_root = construct_env(envp);
	run_shell(env_root, dup(0), dup(1));
	free_env(env_root);
	return (0);
}
