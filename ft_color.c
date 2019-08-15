/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:42:32 by sazouaka          #+#    #+#             */
/*   Updated: 2019/08/14 15:42:34 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_f_color(mode_t mode)
{
	if (S_ISBLK(mode))
		return (F_BLU);
	if (S_ISCHR(mode))
		return (F_BLU);
	if (S_ISFIFO(mode))
		return (F_YEL);
	if (S_ISLNK(mode))
		return (F_MAG);
	if (S_ISSOCK(mode))
		return (F_GRN);
	if (((mode & S_IXUSR) || (mode & S_IXGRP) ||
		(mode & S_IXOTH)) && (!S_ISDIR(mode)))
		return (F_RED);
	if ((mode & S_IXUSR) && (mode & S_ISUID))
		return (F_BLK);
	if ((mode & S_IXGRP) && (mode & S_ISGID))
		return (F_BLK);
	if ((mode & S_IWOTH) && (mode & S_ISVTX))
		return (F_BLK);
	if ((mode & S_IWOTH) && !(mode & S_ISVTX))
		return (F_BLK);
	if (S_ISDIR(mode))
		return (F_BLU);
	return (F_NRM);
}

char	*get_b_color(mode_t mode)
{
	if (S_ISBLK(mode))
		return (B_CYN);
	if (S_ISCHR(mode))
		return (B_YEL);
	if ((mode & S_IXUSR) && (mode & S_ISUID) && (!S_ISDIR(mode)))
		return (B_RED);
	if ((mode & S_IXGRP) && (mode & S_ISGID) && (!S_ISDIR(mode)))
		return (B_CYN);
	if (S_ISDIR(mode))
	{
		if ((mode & S_IWOTH) && (mode & S_ISVTX))
			return (B_GRN);
		if ((mode & S_IWOTH) && !(mode & S_ISVTX))
			return (B_YEL);
	}
	return (B_NRM);
}

void	ft_putstr_clr(char *s, mode_t mode)
{
	char	*f_color;
	char	*b_color;

	f_color = get_f_color(mode);
	b_color = get_b_color(mode);
	if (s)
	{
		ft_putstr(f_color);
		ft_putstr(b_color);
		ft_putstr(s);
		ft_putstr(F_NRM);
		ft_putstr(B_NRM);
	}
}

void	ft_putstr_clr_colum(char *s, char *f_color, char *b_color)
{
	int		i;

	if (s)
	{
		i = 0;
		ft_putstr(f_color);
		ft_putstr(b_color);
		while (s[i])
		{
			if (s[i] == ' ' && s[i + 1] == ' ')
				ft_putstr(B_NRM);
			write(1, &s[i], 1);
			i++;
		}
		ft_putstr(F_NRM);
		ft_putstr(B_NRM);
	}
}
