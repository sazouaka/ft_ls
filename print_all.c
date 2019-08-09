/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:29:33 by sazouaka          #+#    #+#             */
/*   Updated: 2019/08/06 21:29:35 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*trim_path(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	while (i && str[i - 1] != '/')
		i--;
	return (str + i);
}

void	print_name(char *s)
{
	ft_putstr(s);
	ft_putstr(":\n");
}

void	print_all_helper(t_dlist *dirs, char *tab)
{
	DIR		*d;
	t_dlist	*head;

	d = opendir(dirs->name);
	if (d == NULL)
	{
		ft_putstr("./ft_ls: ");
		perror(trim_path(dirs->name));
		dirs = dirs->next;
		return;
	}
	head = ft_ls(d, tab[1], dirs->name);
	if (head)
	{
		ascii_sort(head);
		sort_by_flag(head, tab[3], tab[4]);
		ft_l_flag(head, tab, 1);
		(tab[0] == 'R') ? ft_R_flag(head, tab) : 0;
		free_list(head);
	}
	dirs = dirs->next;
}

int		print_all(t_dlist *dirs, char *tab, t_dlist *tmp_file)
{
//	t_dlist	*head;
	t_dlist	*tmp_dirs;
//	DIR		*d;
	int		i;

	tmp_dirs = dirs;
	sort_by_flag(dirs, tab[3], tab[4]);
	i = 0;
	while (dirs)
	{
		(i != 0 || tmp_file) ? ft_putchar('\n') : 0;
		(tmp_file || tmp_dirs->next) ? print_name(dirs->name) : 0;
		i = 1;
		print_all_helper(dirs, tab);
		// if ((d = opendir(dirs->name)) == NULL)
		// {
		// 	ft_putstr("./ft_ls: ");
		// 	perror(trim_path(dirs->path_name));
		// 	dirs = dirs->next;
		// 	continue;
		// }
		// head = ft_ls(d, tab[1], dirs->name);
		// if (head)
		// {
		// 	ascii_sort(head);
		// 	sort_by_flag(head, tab[3], tab[4]);
		// 	ft_l_flag(head, tab, 1);
		// 	(tab[0] == 'R') ? ft_R_flag(head, tab) : 0;
		// 	free_list(head);
		// }
		dirs = dirs->next;
	}
	return (0);
}
