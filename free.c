/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 01:27:22 by afaraji           #+#    #+#             */
/*   Updated: 2019/08/11 01:27:40 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_list(t_dlist *head)
{
	t_dlist *current;
	t_dlist *tmp;

	current = head;
	while (current)
	{
		IFREE(current->name);
		IFREE(current->path_name);
		tmp = current;
		current = current->next;
		IFREE(tmp);
	}
}

void	free_list2(t_dlist *head)
{
	t_dlist *current;
	t_dlist *tmp;

	current = head;
	while (current)
	{
		IFREE(current->name);
		tmp = current;
		current = current->next;
		IFREE(tmp);
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_tab(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free_tab(tab[i]);
		i++;
	}
	free(tab);
}
