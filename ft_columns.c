/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_columns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 20:09:39 by afaraji           #+#    #+#             */
/*   Updated: 2019/08/15 20:10:01 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		max_colum(int *nb, t_dlist *head, char c)
{
	int				max;
	t_dlist			*node;

	*nb = 0;
	max = 0;
	node = head;
	while (node)
	{
		max = MAX(max, ft_strlen(node->name));
		(*nb)++;
		node = node->next;
	}
	max++;
	if (c != 'G')
		while (max % 8)
			max++;
	return (max);
}

int		get_col(int max, int *r, int nb)
{
	int				col;
	int				row;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col = w.ws_col / max;
	row = nb / col;
	if (nb % col != 0)
	{
		row++;
		col = nb / row;
		if (nb % row != 0)
			col++;
	}
	*r = row;
	return (col);
}

void	print_to_colum_clr(char ***tab, int row, int nb)
{
	int			i;
	int			step;

	step = 0;
	while (step < row)
	{
		i = step;
		while (i < nb)
		{
			ft_putstr_clr_colum(tab[i][0], tab[i][1], tab[i][2]);
			i = i + row;
		}
		ft_putchar('\n');
		step++;
	}
}

char	**ft_fill_clr(t_dlist *node, int max)
{
	struct stat	sb;
	char		**tab;

	tab = (char **)malloc(sizeof(char *) * 4);
	lstat(node->path_name, &sb);
	tab[0] = ft_fill_end_space(node->name, max);
	tab[1] = ft_strdup(get_f_color(sb.st_mode));
	tab[2] = ft_strdup(get_b_color(sb.st_mode));
	tab[3] = NULL;
	return (tab);
}

char	***list_to_clr(t_dlist *head, int max, int nb)
{
	t_dlist		*node;
	char		***tab;
	int			i;

	node = head;
	tab = (char ***)malloc(sizeof(char **) * (nb + 1));
	i = 0;
	while (i < nb)
	{
		tab[i] = ft_fill_clr(node, max);
		i++;
		node = node->next;
	}
	tab[nb] = NULL;
	return (tab);
}
