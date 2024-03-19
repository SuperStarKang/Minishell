/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 04:41:23 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 12:03:30 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_home(t_env *env_root)
{
	char	*home;

	printf("cd home\n");
	home = find_env(env_root, "HOME");
	if (!(home))
	{
		ft_putendl_fd("HOME not set", STDERR_FILENO);
		return (1);
	}
	if (chdir(home))
	{
		perror("chdir()");
		return (1);
	}
	return (0);
}

char	*make_path(t_node *path_node)
{
	char	*path;
	char	*oldpath;
	t_node	*tmp;

	if (!(path_node))
		return (0);
	tmp = path_node;
	path = (char *)xmalloc(1);
	path[0] = '\0';
	while (tmp)
	{
		oldpath = path;
		path = ft_strjoin(oldpath, tmp->token->str);
		free(oldpath);
		tmp = tmp->next;
		if (tmp)
		{
			oldpath = path;
			path = ft_strjoin(oldpath, "/");
			free(oldpath);
		}
	}
	return (path);
}

int	check_dir(char *path)
{
	struct stat	is_dir;

	if (stat(path, &is_dir))
	{
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (1);
	}
	else if (!S_ISDIR(is_dir.st_mode))
	{
		ft_putendl_fd("Not a directory", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	execute_cd(t_node *cd_node, t_env *env_root)
{
	char		*path;

	path = make_path(cd_node->next);
	if (!(path))
	{
		if (cd_home(env_root))
			return (1);
		return (0);
	}
	if (!check_dir(path))
	{
		if (chdir(path))
		{
			perror("chdir()");
			free(path);
			return (1);
		}
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

void	builtin_cd(t_env *env_root, t_node *cd_node)
{
	char	*pwd;

	if (execute_cd(cd_node, env_root))
		return (update_recent_exit_status(env_root, 1));
	pwd = getcwd(NULL, 0);
	insert_env(env_root, "PWD", pwd);
	return (update_recent_exit_status(env_root, 0));
}
