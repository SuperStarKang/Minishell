/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:20:10 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 11:45:28 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

typedef struct s_exec {
	char	**paths;
	char	**argv;
	char	**envp;
	char	*cmd;
	int		*pids;
	int		fds[2];
	int		idx;
	int		pipe_count;
	int		*hdoc_ifds;
	t_env	*env_root;
}	t_exec;

// utils
void	init_exec(t_exec *exec, t_env *env_root, int p_cnt, int *hdoc_ifds);
void	free_paths(char **paths);
int		get_pipe_count(t_node *pipe_node);
char	**get_paths(t_env *env_root);
void	cmd_not_found(char *str);

// search
char	*search_cmd_containing_slash(char *path);
char	*search_cmd(char **paths, char *cmd);

// builtin
int		is_builtin(t_node *cmd_node);
int		run_builtin(t_env *env_root, t_node *cmd_node);

// heredoc
void	close_heredoc(int *heredoc_ifds, int pipe_count);
int		pre_heredoc(t_node *pipe_node, int *heredoc_ifds);

// execute
void	exec_tree(t_node *p_node, t_env *env_root, int p_cnt, int *hdoc_ifds);
void	redir(t_node *redir_node, int *heredoc_ifd);

// construct
char	**construct_argv(t_node *cmd_node);
char	**construct_envp(t_env *env_root);
void	update_status(t_exec *exec);

#endif