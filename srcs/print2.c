/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 16:58:18 by nwang             #+#    #+#             */
/*   Updated: 2018/03/16 00:48:27 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	permission(t_tree *node)
{
	ft_putchar((S_ISFIFO(node->st->p_stat.st_mode)) ? 'p' : '\0');
	ft_putchar((S_ISCHR(node->st->p_stat.st_mode)) ? 'c' : '\0');
	ft_putchar((S_ISDIR(node->st->p_stat.st_mode)) ? 'd' : '\0');
	ft_putchar((S_ISBLK(node->st->p_stat.st_mode)) ? 'b' : '\0');
	ft_putchar((S_ISREG(node->st->p_stat.st_mode)) ? '-' : '\0');
	ft_putchar((S_ISLNK(node->st->p_stat.st_mode)) ? 'l' : '\0');
	ft_putchar((S_ISSOCK(node->st->p_stat.st_mode)) ? 's' : '\0');
	ft_putchar((node->st->p_stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((node->st->p_stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((node->st->p_stat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((node->st->p_stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((node->st->p_stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((node->st->p_stat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((node->st->p_stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((node->st->p_stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((node->st->p_stat.st_mode & S_IXOTH) ? 'x' : '-');
	ft_putchar(listxattr(node->path, 0, 0, 0) > 0 ? '@' : ' ');
	ft_putstr(" ");
}

void	print_date(time_t date)
{
	char	*s1;
	char	*s2;
	time_t	a_time;

	a_time = time(0);
	s1 = ctime(&date);
	if ((a_time - 15778463) > date || a_time < date)
	{
		s2 = ft_strnew(6);
		s2 = ft_strsub(s1, 20, 4);
		s1 = ft_strsub(s1, 4, 6);
		s1 = ft_strjoin(s1, "  ");
		s1 = ft_strjoin(s1, s2);
		free(s2);
	}
	else
		s1 = ft_strsub(s1, 4, 12);
	s1[12] = '\0';
	ft_putstr(s1);
	ft_putchar(' ');
	free(s1);
}
