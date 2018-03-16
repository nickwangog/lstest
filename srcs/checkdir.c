/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 01:10:21 by nwang             #+#    #+#             */
/*   Updated: 2018/03/16 14:43:05 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	recursive_ls(t_flags *fl, t_tree *root, char *c_dir)
{
	if (!root)
		return ;
	recursive_ls(fl, (fl->r) ? root->right : root->left, c_dir);
	if (!root->st || (root->name[0] == '.' && root->name[1] == '.') ||
			(root->name[0] == '.' && !root->name[1]))
		;
	else if (S_ISDIR(root->st->p_stat.st_mode))
		run_ls(fl, root->path);
	recursive_ls(fl, (fl->r) ? root->left : root->right, c_dir);
}

void	target_dir(t_flags *fl, t_tree *node)
{
	if (!node)
		return ;
	if (!(S_ISDIR(node->st->p_stat.st_mode)))
	{
		fl->blocks += node->st->p_stat.st_blocks;
		if (fl->l)
			l_print(fl, node);
		else if (fl->big_g && S_ISDIR(node->st->p_stat.st_mode))
			ft_printf(C_CYAN "%s\n"C_RESET, node->name);
		else if (fl->big_g && S_ISREG(node->st->p_stat.st_mode)
				&& !S_ISDIR(node->st->p_stat.st_mode))
			ft_printf(C_RED "%s\n"C_RESET, node->name);
		else
		{
			ft_putendl(node->name);
			fl->nline = fl->nline ? write(1, "\n", 1) : 1;
		}
	}
	target_dir(fl, fl->r ? node->right : node->left);
	if (S_ISDIR(node->st->p_stat.st_mode))
		run_ls(fl, node->name);
	target_dir(fl, fl->r ? node->left : node->right);
}

void	run_ls(t_flags *fl, char *c_dir)
{
	DIR				*temp;
	struct dirent	*dir;
	t_tree			*node;
	t_tree			*root;

	temp = NULL;
	dir = NULL;
	root = NULL;
	if ((temp = opendir(c_dir)) == NULL)
	{
		fl->nline = fl->nline ? write(1, "\n", 1) : 1;
		fl->p_dir ? ft_printf("%s:\n", c_dir) : 1;
		ft_printf("ft_ls: %s: %s\n", c_dir, strerror(errno));
		return ;
	}
	while ((dir = readdir(temp)))
	{
		if (!fl->a && dir->d_name[0] == '.')
			continue;
		node = new_node(c_dir, dir->d_name);
		root = ins_node(fl, root, node);
		fl->blocks += node->st->p_stat.st_blocks;
	}
	closedir(temp);
	print_dir(fl, root, c_dir);
}
