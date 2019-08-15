/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:27:12 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/27 17:27:14 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list(t_dlist *head, char c, char col)
{
	t_dlist		*node;
	struct stat	sb;

	if (col != '1')
		print_list_colum(head, c);
	else
	{
		node = head;
		while (node)
		{
			if (c == 'G')
			{
				lstat(node->path_name, &sb);
				ft_putstr_clr(node->name, sb.st_mode);
			}
			else
				ft_putstr(node->name);
			ft_putchar('\n');
			node = node->next;
		}
	}
}

char	*ft_fill_end_space(char *src, int len)
{
	int		i;
	char	*tab;

	tab = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		tab[i] = ' ';
		i++;
	}
	tab[i] = '\0';
	i = 0;
	while (src[i])
	{
		tab[i] = src[i];
		i++;
	}
	return (tab);
}

char	**list_to_tab(t_dlist *head, int max, int nb)
{
	t_dlist		*node;
	char		**tab;
	int			i;

	node = head;
	tab = (char **)malloc(sizeof(char *) * (nb + 1));
	i = 0;
	while (node)
	{
		tab[i] = ft_fill_end_space(node->name, max);
		i++;
		node = node->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	print_to_colum(char **tab, int row, int nb)
{
	int		i;
	int 	step;

	step = 0;
	while(step < row)
	{
		i = step;
		while (i < nb)
		{
			ft_putstr(tab[i]);
			i = i + row;
		}
		ft_putchar('\n');
		step++;
	}
}

void	print_to_colum_clr(char **tab, int row, int nb, t_dlist *head)
{
	int			i;
	int 		step;
	struct stat	sb;
	step = 0;
	while(step < row)
	{
		i = step;
		while (i < nb && head)
		{
			lstat(head->path_name, &sb);
			ft_putstr_clr(tab[i], sb.st_mode);
			i = i + row;
			head = head->next;
		}
		ft_putchar('\n');
		step++;
	}
}

void	print_list_colum(t_dlist *head, char c)
{
	char			**tab;
	t_dlist			*node;
	struct winsize	w;
	int				i;
	int				nb;
	int				max;
	int				col;
	int				row;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	nb = 0;
	max = 0;
	node = head;
	while (node)
	{
		max = MAX(max, ft_strlen(node->name));
		nb++;
		node = node->next;
	}
	max++;
	while(max % 8)
		max++;
	tab = list_to_tab(head, max, nb);
	col = w.ws_col / max;
	row = nb / col;
	if (nb % col != 0)
	{
		row++;
		col = nb / row;
		if (nb % row != 0)
			col++;
	}
	if(c == 'G')
		print_to_colum_clr(tab, row, nb, head);
	else
		print_to_colum(tab, row, nb);
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}