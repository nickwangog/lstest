/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 16:58:18 by nwang             #+#    #+#             */
/*   Updated: 2018/03/16 14:43:21 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	invalid_print(t_tree *node)
{
	if (!node)
		return ;
	if (node->left)
		invalid_print(node->left);
	ft_printf("ft_ls: %s: No such file or directory\n", node->name);
	if (node->right)
		invalid_print(node->right);
}

void	l_print(t_flags *fl, t_tree *node)
{
	permission(node);
	ft_printf("%d ", node->st->p_stat.st_nlink);
	ft_printf("%s  ", node->st->pwd.pw_name);
	ft_printf("%s ", node->st->grp.gr_name);
	ft_printf("%d ", node->st->p_stat.st_size);
	print_date(node->st->p_stat.st_mtime);
	if (fl->big_g && S_ISDIR(node->st->p_stat.st_mode))
		ft_printf(C_CYAN "%s\n"C_RESET, node->name);
	else if (fl->big_g && S_ISREG(node->st->p_stat.st_mode)
			&& !S_ISDIR(node->st->p_stat.st_mode))
		ft_printf(C_RED "%s\n"C_RESET, node->name);
	else
		ft_printf("%s\n", node->name);
}

void	print_left(t_flags *fl, t_tree *node)
{
	struct stat		tmp;

	if (!node)
		return ;
	if (node->left)
		print_left(fl, node->left);
	if (node->st)
	{
		if (fl->l)
			l_print(fl, node);
		else if (fl->big_g && S_ISDIR(node->st->p_stat.st_mode))
			ft_printf(C_CYAN "%s\n"C_RESET, node->name);
		else if (fl->big_g && S_ISREG(node->st->p_stat.st_mode)
				&& !S_ISDIR(node->st->p_stat.st_mode))
			ft_printf(C_RED "%s\n"C_RESET, node->name);
		else
			ft_putendl(node->name);
	}
	else
	{
		stat(node->path, &tmp);
		ft_printf("ft_ls: %s: %s\n", node->name, strerror(errno));
	}
	if (node->right)
		print_left(fl, node->right);
}

void	print_right(t_flags *fl, t_tree *node)
{
	struct stat		tmp;

	if (!node)
		return ;
	if (node->right)
		print_right(fl, node->right);
	if (node->st)
	{
		if (fl->l)
			l_print(fl, node);
		else if (fl->big_g && S_ISDIR(node->st->p_stat.st_mode))
			ft_printf(C_CYAN "%s\n"C_RESET, node->name);
		else if (fl->big_g && S_ISREG(node->st->p_stat.st_mode)
				&& !S_ISDIR(node->st->p_stat.st_mode))
			ft_printf(C_RED "%s\n"C_RESET, node->name);
		else
			ft_putendl(node->name);
	}
	else
	{
		stat(node->path, &tmp);
		ft_printf("ft_ls: %s: %s\n", node->name, strerror(errno));
	}
	if (node->left)
		print_right(fl, node->left);
}

void	print_dir(t_flags *fl, t_tree *root, char *c_dir)
{
	fl->nline = fl->nline ? write(1, "\n", 1) : 1;
	fl->p_dir ? ft_printf("%s:\n", c_dir) : 0;
	fl->l && root ? ft_printf("total %i\n", fl->blocks) : 0;
	fl->blocks = 0;
	if (fl->r)
		print_right(fl, root);
	else
		print_left(fl, root);
	if (fl->big_r)
		recursive_ls(fl, root, c_dir);
	clear_tree(root);
}
