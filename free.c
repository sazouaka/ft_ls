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
		free(current->name);
		free(current->path_name);
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

void	free_list2(t_dlist *head)
{
	t_dlist *current;
	t_dlist *tmp;

	current = head;
	while (current)
	{
		free(current->name);
		tmp = current;
		current = current->next;
		free(tmp);
	}
}
