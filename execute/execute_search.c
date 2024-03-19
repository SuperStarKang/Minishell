/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:30:39 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/30 11:45:29 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*search_cmd_containing_slash(char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			return (path);
		}
		perror(NULL);
		exit(126);
	}
	perror(NULL);
	exit(127);
}

char	*search_cmd(char **paths, char *cmd)
{
	char	*path;
	char	*orignal_cmd;

	orignal_cmd = cmd;
	if (ft_strchr(cmd, '/') != NULL)
		return (search_cmd_containing_slash(cmd));
	cmd = ft_strjoin("/", cmd);
	while (*paths != NULL)
	{
		path = ft_strjoin(*paths, cmd);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				free(cmd);
				return (path);
			}
			perror(NULL);
			exit(126);
		}
		free(path);
		paths++;
	}
	cmd_not_found(orignal_cmd);
	exit(127);
}
