/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_one_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 16:51:58 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/27 16:52:00 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dlist	*get_one_file(char *str, char *s2)
{
	t_dlist		*files;
	struct stat	st;

	lstat(s2, &st);
	files = (t_dlist *)malloc(sizeof(t_dlist));
	files->mtime = st.st_mtime;
	files->name = ft_strdup(str);
	files->path_name = ft_strdup(s2);
	files->next = NULL;
	return (files);
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
