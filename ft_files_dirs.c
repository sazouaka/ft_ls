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
		if (S_ISREG(st.st_mode))
			return (2);
		if (S_ISLNK(st.st_mode))
			return (3);
	}
	if (ret == -1)
		return (-1);
	return (0);
}

t_dlist	*get_file(char *str)
{
	t_dlist		*file;
	struct stat	st;

	lstat(str, &st);
	file = (t_dlist *)malloc(sizeof(t_dlist));
	file->name = ft_strdup(str);
	file->mtime = st.st_mtime;
	file->path_name = file->name;
	file->next = NULL;
	return (file);
}

t_dlist	*get_files(int index, char **argv, char *tab)
{
	t_dlist	*files;
	t_dlist	*head1;
	int		t;
	int		l;

	files = NULL;
	head1 = NULL;
	while (argv[index])
	{
		t = verify_type(argv[index]);
		l = ft_strlen(argv[index]) - 1;
		if (t == -1)
		{
			ft_putstr("./ft_ls: ");
			perror(argv[index]);
		}
		if (t == 2 || (t == 3 && tab[2] == 'l' && argv[index][l] != '/'))
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

t_dlist	*get_dirs(int i, char **argv, char *tab)
{
	t_dlist	*dirs;
	t_dlist	*head1;
	int		t;
	int		l;

	dirs = NULL;
	head1 = NULL;
	while (argv[i])
	{
		t = verify_type(argv[i]);
		l = ft_strlen(argv[i]) - 1;
		if (t == 1 || ((t == 3) && tab[2] != 'l') || ((t == 3) &&
			tab[2] == 'l' && argv[i][l] == '/'))
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
