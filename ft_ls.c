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
	char *t;
	char *t2;
	if(ft_strcmp(str,"/") == 0)
		t = str;
	else
		t = ft_strjoin(str, "/");    
	while ((read = readdir(dir)))
	{
		if ((ft_char(read->d_name, '.')) == 1 && a != 'a')
			continue;
		if(!files)
		{
			t2 = ft_strjoin(t, read->d_name);
			files = get_one_file(read->d_name, t2);
			head = files;
		}
		else
		{
			t2 = ft_strjoin(t, read->d_name);
			files->next = get_one_file( read->d_name,t2);
			files = files->next;
		}
		free(t2);
	}
	free(t);
	closedir(dir);
	return (head);
}

void    display_files(t_dlist *head, char *tab)
{
	t_dlist *file = NULL;
	t_dlist *new_head = NULL;
	t_dlist *current;

	current = head;
	while(current)
	{
	   if(!file)
		{
			file = get_one_file(current->name, current->name);
			new_head = file;
		}
		else
		{
			file->next = get_one_file(current->name, current->name);
			file = file->next;
		}
		current = current->next;
	}
	sort_by_flag(new_head, tab[3], tab[4]);
	ft_l_flag(new_head, tab, 0);
	free_list(new_head);
}

void		free_list(t_dlist *head)
{
	t_dlist *current;
	t_dlist *tmp;

	current = head;
	while(current)
	{
		
		free(current->name);
		// free(current);
		// // if (current->path_name)
		free(current->path_name);
		tmp = current;
		// printf("-------------------\n");
		// printf("current:%p\nname:   %p\npath:   %p\n", current, &current->name, &current->path_name);
		// printf("-------------------\n");
		
		current = current->next;
		free(tmp);
	}
	
}

void		free_list2(t_dlist *head)
{
	t_dlist *current;
	t_dlist *tmp;

	current = head;
	while(current)
	{
		
		free(current->name);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	
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
		free_list2(dirs);
	}
	else
	{
		files = get_files(i, argv, tab);
		dirs = get_dirs(i, argv, tab);
		if (files)
		{
			display_files(files, tab);
			//free_list2(files);
			
		}		
		if (dirs)
		{
			print_all(dirs, tab, files);
			free_list2(dirs);
		}
		if(files)
			free_list2(files);
	}
	free(tab);
	return (0);
}
