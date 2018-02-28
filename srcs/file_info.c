/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 16:58:18 by nwang             #+#    #+#             */
/*   Updated: 2018/02/26 19:37:17 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <sys/stat.h>
#include <stdio.h>

void	file_info(struct dirent *dir, struct stat *buf, t_flags *fl)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->name = dir->d_name;
	//info->path = ft_strjoin(path, name);
/*	if (lstat(info->name, &buf-> == -1)
	{
		basicerror("ft_ls: ", info->name, 1);
		return (NULL);
	}*/
	info->st_mode = buf->st_mode;
	info->st_nlink = buf->st_nlink;
	info->st_uid = buf->st_uid;
	info->st_gid = buf->st_gid;
	info->st_size = buf->st_size;
	info->st_blocks = buf->st_blocks;
	info->date = buf->st_mtime; //(arg.u == 1 ? buf->st_atime : buf->st_mtime);
	info->st_rdev = buf->st_rdev;
	info->next = NULL;
	print_finfo(info, fl);
}

void	print_finfo(t_info *info, t_flags *fl)
{
	if (fl->l == 0)
		ft_printf("%s\n", info->name);
	else if (fl->l == 1)
	{
	// permissions
		ft_printf("%d\n", (int)info->st_nlink);
		//ft_printf("%s\n", (char *)info->st_uid);
		//ft_printf("%s\n", (char *)info->st_gid);
		ft_printf("%d\n", (int)info->st_size);
		ft_printf("%s\n", (char *)info->date);
		ft_printf("%s\n", info->name);
	}
}

/*void	print_finfo()
{
	lstat(dir->d_name, buf);
	//ft_printf("%s\n", dir->d_name);
	//ft_printf("%d\n", buf->st_size);
	//ft_printf("%d\n", buf->st_mtime);
	ft_printf("\nlstat() for link %s returned:\n", dir->d_name);
	ft_printf("inode: %d\n", (int) buf->st_ino);
	ft_printf("dev id: %d\n", (int) buf->st_dev);
	ft_printf("user id: %d\n", (int) buf->st_uid);
	ft_printf("links: %d\n",  buf->st_nlink);
	ft_printf("file size: %d\n", (int) buf->st_size);
	ft_printf("mode: %08x\n",  buf->st_mode);
}*/

/*void	print_access(t_elem *elem)
{
	ft_putchar((S_ISFIFO(elem->st_mode)) ? 'p' : '\0');
	ft_putchar((S_ISCHR(elem->st_mode)) ? 'c' : '\0');
	ft_putchar((S_ISDIR(elem->st_mode)) ? 'd' : '\0');
	ft_putchar((S_ISBLK(elem->st_mode)) ? 'b' : '\0');
	ft_putchar((S_ISREG(elem->st_mode)) ? '-' : '\0');
	ft_putchar((S_ISLNK(elem->st_mode)) ? 'l' : '\0');
	ft_putchar((S_ISSOCK(elem->st_mode)) ? 's' : '\0');
	ft_putchar((elem->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((elem->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((elem->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((elem->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((elem->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((elem->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((elem->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((elem->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((elem->st_mode & S_IXOTH) ? 'x' : '-');
	ft_putstr("  ");
}*/
