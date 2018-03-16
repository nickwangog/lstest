/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 01:10:21 by nwang             #+#    #+#             */
/*   Updated: 2018/03/16 00:26:04 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
void	do_ls_stuff(t_ls_flags *f, char *current_direc_name)
{
	DIR				*temp;
	struct dirent	*dir;
	t_ls_arg		*new;
	t_ls_arg		*root;

	if (!(temp = opendir(current_direc_name)))
	{
		f->print_newline = f->print_newline ? write(1, "\n", 1) : 1;
		f->print_dir ? ft_pflite("%s:\n", current_direc_name) : 1;
		ft_pflite("ft_ls: %s: %s\n", current_direc_name, strerror(errno));
		return ;
	}
	root = NULL;
	ft_bzero(&f->len, sizeof(t_ls_maxlen));
	while ((dir = readdir(temp)))
	{
		if (!f->a && dir->d_name[0] == '.')
			continue ;
		new = new_arg(current_direc_name, dir->d_name);
		root = insert_arg(f, root, new);
		f->l ? set_new_maxlens(&f->len, new) : 0;
	}
	closedir(temp);
	still_do_ls_stuff(f, root, current_direc_name, &f->len);
}
void	still_do_ls_stuff(t_ls_flags *f, t_ls_arg *r, char *cdn, t_ls_maxlen *l)
{
	f->l ? adjust_new_maxlens(l) : 0;
	f->print_newline = f->print_newline ? write(1, "\n", 1) : 1;
	f->print_dir ? ft_pflite("%s:\n", cdn) : 0;
	f->l && r ? ft_pflite("total %u\n", l->total_blocks) : 0;
	f->r ? print_args_right(f, r, l) : print_args_left(f, r, l);
	f->rr ? do_recursive_ls_stuff(f, r, cdn) : 0;
	free_binary_tree_ls(r);
}
*/
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
			l_print(node);
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
