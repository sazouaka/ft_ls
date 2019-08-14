/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:22:57 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/27 17:22:59 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		flag_search(char c)
{
	int	i;

	i = 0;
	while (FLAGS[i] != '\0')
	{
		if (FLAGS[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*flag_tab(char *tab, char **av, int i)
{
	int		z;
	int		j;

	z = 1;
	while (av[i][z])
	{
		j = flag_search(av[i][z]);
		if (j == -1)
		{
			ft_putstr("./ft_ls: illegal option -- ");
			ft_putchar(av[i][z]);
			ft_putstr("\nusage: ./ft_ls [-Ralrt] [file ...]\n");
			exit(1);
		}
		else
			tab[j] = av[i][z];
		z++;
	}
	return (tab);
}

void	tab_double_dash(void)
{
	ft_putstr("./ft_ls: illegal option -- -\n");
	ft_putstr("usage: ./ft_ls [-Ralrt] [file ...]\n");
	exit(1);
}

char	*get_flag_tab(int ac, char **av, int *index)
{
	int		i;
	char	*tab;

	tab = (char *)malloc(sizeof(char) * 6);
	i = 0;
	while (i < 6)
		tab[i++] = '0';
	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
	{
		if (av[i][1] == '-')
		{
			if (av[i][2] == '\0')
			{
				i++;
				break ;
			}
			else
				tab_double_dash();
		}
		flag_tab(tab, av, i);
		i++;
	}
	*index = i;
	return (tab);
}
