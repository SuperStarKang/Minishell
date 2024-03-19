/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangmlee <kangmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:58:46 by jongmoon          #+#    #+#             */
/*   Updated: 2023/12/29 20:49:29 by kangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*make_env_entry(char *key, char *value)
{
	t_env	*entry;

	entry = (t_env *)malloc(sizeof(t_env));
	if (entry == NULL)
		exit(1);
	entry->key = key;
	entry->value = value;
	entry->next = NULL;
	return (entry);
}

t_env	*construct_env(char **envp)
{
	t_env	*env_root;
	char	*key;
	char	*value;
	char	*p;
	int		i;

	env_root = make_env_entry("", ft_strdup("0"));
	while (*envp != NULL)
	{
		p = ft_strchr(*envp, '=');
		if (p != NULL)
		{
			i = p - *envp;
			key = ft_substr(*envp, 0, i);
			i++;
			value = ft_substr(*envp, i, ft_strlen(*envp) - i);
			insert_env(env_root, key, value);
			free(key);
		}
		envp++;
	}
	return (env_root);
}

void	update_recent_exit_status(t_env *env_root, int status)
{
	char	*value;

	value = ft_itoa(status);
	free(env_root->value);
	env_root->value = value;
}

char	*find_env(t_env *env_root, char *key)
{
	t_env	*temp;

	temp = env_root->next;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
