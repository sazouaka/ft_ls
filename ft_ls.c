/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:43:22 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/03 21:14:31 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//********************//
//Function to get list//
//********************//

t_dlist *ft_ls(DIR *dir, char a, char *str)
{
	struct dirent *read;
	t_dlist *files;
	t_dlist *head = NULL;
	files = NULL;
	char *t = ft_strjoin(str, "/");    
	while ((read = readdir(dir)))
	{
		if ((ft_char(read->d_name, '.')) == 1 && a != 'a')
			continue;
		if(!files)
		{
			files = get_one_file(read->d_name, ft_strjoin(t, read->d_name));
			head = files;
		}
		else
		{
			files->next = get_one_file( read->d_name,ft_strjoin(t, read->d_name));
			files = files->next;
		}
	}
	closedir(dir);
	return (head);
}

void    display_files(t_dlist *files, char *tab)
{
	t_dlist *file = NULL, *head = NULL;
	while(files)
	{
	   if(!file)
		{
			file = get_one_file(files->name, files->name);
			head = file;
		}
		else
		{
			file->next = get_one_file(files->name, files->name);
			file = file->next;
		}
		files = files->next;
	}
	sort_by_flag(head, tab[3], tab[4]);
	ft_l_flag(head, tab, 0);
}

int main(int argc, char **argv)
{
	t_dlist *files = NULL;
	t_dlist *dirs = NULL;
	char	*tab;
	int		i;

	tab = get_flag_tab(argc, argv, &i);
	if (argc - i == 0)
	{
		dirs = get_file(".");
		print_all(dirs, tab, NULL);
	}
	else
	{
		files = get_files(i, argv, tab);
		dirs = get_dirs(i, argv, tab);
		if (files)
			display_files(files, tab);
		if (dirs)
			print_all(dirs, tab, files);
	}
	
	return (0);
}
