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

int verify_type(char *str)
{
	struct stat st;
    if(lstat(str, &st) == 0)
    {
        if(S_ISDIR(st.st_mode))
            return(1);
        if(S_ISREG(st.st_mode))
            return(2);
		if(S_ISLNK(st.st_mode))
			return(3);
    }
	return(0);
}
t_dlist *get_file(char *str)
{
	t_dlist *file;
	struct stat st;

	lstat(str, &st);
	file = (t_dlist *)malloc(sizeof(t_dlist));
	file->name = ft_strdup(str);
	file->mtime = st.st_mtime;
	file->path_name = file->name;
	file->next = NULL;
	return(file);
}
t_dlist *get_files(int argc, char **argv)
{
    int i = 1;
    t_dlist *files = NULL;
	t_dlist *head1 = NULL;
	char	*tab;

	tab = get_flag_tab(argc, argv);
    while(i < argc)
	{
		if(verify_type(argv[i]) == 2 || ((verify_type(argv[i]) == 3) && tab[2] == 'l' && argv[i][ft_strlen(argv[i]) - 1] != '/'))
		{
			if(!files)
			{
				files = get_file(argv[i]);
				head1 = files;
			}
			else
			{
				files->next = get_file(argv[i]);
				files = files->next;
			}
		}
        i++;
    }
    return (head1);
}

t_dlist *get_dirs(int argc, char **argv)
{
    int i = 1;
    t_dlist *dirs = NULL;
	t_dlist *head1 = NULL;
	char	*tab;

	tab = get_flag_tab(argc, argv);
    while(i < argc)
	{
		if(verify_type(argv[i]) == 1  || ((verify_type(argv[i]) == 3) && tab[2] != 'l') || ((verify_type(argv[i]) == 3) && tab[2] == 'l' && argv[i][ft_strlen(argv[i]) - 1] == '/'))
		{
			if(!dirs)
			{
				dirs = get_file(argv[i]);
				head1 = dirs;
			}else
			{
				dirs->next = get_file(argv[i]);;
				dirs = dirs->next;
			}
		}
        i++;
    }
    return (head1);
}