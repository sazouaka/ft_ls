/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 15:58:37 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/28 15:58:39 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		verify_type(char *str)
{
	struct stat	st;
	int			ret;

	if ((ret = lstat(str, &st)) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (1);
		if (S_ISLNK(st.st_mode))
			return (3);
		else
			return (2);		
	}
	if (ret == -1)
		return (-1);
	return (0);
}

int		if_read_lnk2(char *str, char *tab)
{
	int t;
	int l;

	t = verify_type(str);
	l = ft_strlen(str) - 1;
	if (t == -1)
	{
		ft_putstr("./ft_ls: ");
		perror(str);
		return (0);
	}
	if (t == 2 || (t == 3 && tab[2] == 'l' && str[l] != '/'))
		return (1);
	else
	{
		return (0);
	}
}

t_dlist	*get_files(int index, char **argv, char *tab)
{
	t_dlist	*files;
	t_dlist	*head1;

	files = NULL;
	head1 = NULL;
	while (argv[index])
	{
		if (if_read_lnk2(argv[index], tab))
		{
			if (!files)
			{
				files = get_file(argv[index]);
				head1 = files;
			}
			else
			{
				files->next = get_file(argv[index]);
				files = files->next;
			}
		}
		index++;
	}
	return (head1);
}

int		if_read_lnk(char *str, char *tab)
{
	int t;
	int l;

	t = verify_type(str);
	l = ft_strlen(str) - 1;
	if (t == 1 || ((t == 3) && tab[2] != 'l') ||
		((t == 3) && tab[2] == 'l' && str[l] == '/'))
		return (1);
	else
	{
		return (0);
	}
}

t_dlist	*get_dirs(int i, char **argv, char *tab)
{
	t_dlist	*dirs;
	t_dlist	*head1;

	dirs = NULL;
	head1 = NULL;
	while (argv[i])
	{
		if (if_read_lnk(argv[i], tab))
		{
			if (!dirs)
			{
				dirs = get_file(argv[i]);
				head1 = dirs;
			}
			else
			{
				dirs->next = get_file(argv[i]);
				dirs = dirs->next;
			}
		}
		i++;
	}
	return (head1);
}
