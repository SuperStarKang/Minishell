/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: superstar <superstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:42:01 by kangmlee          #+#    #+#             */
/*   Updated: 2023/12/29 21:16:33 by superstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	insert_env(t_env *env_root, char *key, char *value)
{
	t_env	*temp;
	t_env	*entry;

	temp = env_root;
	while (temp->next != NULL && ft_strcmp(temp->next->key, key) < 0)
		temp = temp->next;
	if (temp->next == NULL)
		temp->next = make_env_entry(ft_strdup(key), value);
	else if (ft_strcmp(temp->next->key, key) == 0)
	{
		free(temp->next->value);
		temp->next->value = value;
	}
	else
	{
		entry = make_env_entry(ft_strdup(key), value);
		entry->next = temp->next;
		temp->next = entry;
	}
}

void	remove_env(t_env *env_root, char *key)
{
	t_env	*temp;
	t_env	*next;

	temp = env_root;
	while (temp->next != NULL && ft_strcmp(temp->next->key, key) < 0)
		temp = temp->next;
	if (temp->next != NULL && ft_strcmp(temp->next->key, key) == 0)
	{
		next = temp->next->next;
		free(temp->next->key);
		free(temp->next->value);
		free(temp->next);
		temp->next = next;
	}
}

void	free_env(t_env *env_root)
{
	t_env	*temp;
	t_env	*next;

	temp = env_root->next;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		temp = next;
	}
	free(env_root->value);
	free(env_root);
}
