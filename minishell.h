/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmoon <jongmoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:43:46 by jongmoon          #+#    #+#             */
/*   Updated: 2023/12/30 12:28:48 by jongmoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

# include "libft.h"

# define T_NONE (0)
# define T_WORD (1)
# define T_SINGLE_LEFT_REDIR (2)
# define T_DOUBLE_LEFT_REDIR (3)
# define T_SINGLE_RIGHT_REDIR (4)
# define T_DOUBLE_RIGHT_REDIR (5)
# define T_PIPE (6)
# define T_MORE_LEFT_REDIR (7)
# define T_MORE_RIGHT_REDIR (8)
# define T_MORE_PIPE (9)

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_line {
	char	*str;
	int		i;
}	t_line;

typedef struct s_token {
	int		type;
	char	*str;
}	t_token;

typedef struct s_node {
	t_token			*token;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*next;
}	t_node;

// signal
void	set_signal(void);

// parse
t_line	*make_line(char *str);
t_token	*get_token(t_line *line, t_env *env_root);
t_node	*make_tree(t_node *root, t_token *token);
void	free_tree(t_node *root);

// error
int		syntax_error_check(t_node *root);

// enviroment
t_env	*make_env_entry(char *key, char *value);
void	insert_env(t_env *env_root, char *key, char *value);
void	remove_env(t_env *env_root, char *key);
t_env	*construct_env(char **envp);
void	update_recent_exit_status(t_env *env_root, int status);
char	*find_env(t_env *env_root, char *key);
void	free_env(t_env *env_root);

// execute
int		get_pipe_count(t_node *pipe_node);
void	exec_tree(t_node *pipe_node, t_env *env_root, int pipe_count,
			int *heredoc_ifds);
int		is_builtin(t_node *cmd_node);
int		run_builtin(t_env *env_root, t_node *cmd_node);
int		pre_heredoc(t_node *pipe_node, int *heredoc_ifds);
void	close_heredoc(int *heredoc_ifds, int pipe_count);
void	redir(t_node *redir_node, int *heredoc_ifd);

// builtin
void	builtin_echo(t_env *env_root, t_node *cmd_node);
void	builtin_cd(t_env *env_root, t_node *cmd_node);
void	builtin_pwd(void);
void	builtin_export(t_env *env_root, t_node *cmd_node);
void	builtin_unset(t_env *env_root, t_node *cmd_node);
void	builtin_env(t_env *env_root);
void	builtin_exit(t_node *cmd_node);

// signal
void	default_signal(void);

// utils
int		ft_strcmp(char *s1, char *s2);
void	*xmalloc(size_t size);

#endif
