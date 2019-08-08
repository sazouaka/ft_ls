/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 18:04:57 by sazouaka          #+#    #+#             */
/*   Updated: 2019/07/03 18:04:59 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

int     ft_char(char *s, char c);
char	*ft_strdup(const char *s1);
int     ft_strcmp(const char *s1, const char *s2);
void	ft_putstr(char const *s);
void	ft_putchar(char c);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
void	ft_putnbr(int n);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strlen(const char *s);

#endif