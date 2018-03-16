/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 00:27:51 by nwang             #+#    #+#             */
/*   Updated: 2018/03/12 15:37:12 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	clear_node(t_tree *end)
{
	if (end->st)
	{
		free(end->st->pwd.pw_name);
		free(end->st->grp.gr_name);
		free(end->st);
	}
	if (end->name)
		free(end->name);
	if (end->path)
		free(end->path);
	end->left = NULL;
	end->right = NULL;
	free(end);
}

void	clear_tree(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
		clear_tree(root->left);
	if (root->right)
		clear_tree(root->right);
	clear_node(root);
}

int		clear_ls(t_flags *fl)
{
	if (!fl)
		return (0);
	if (fl->valid_dir)
	{
		clear_tree(fl->valid_dir);
		fl->valid_dir = NULL;
	}
	if (fl->invalid_dir)
	{
		clear_tree(fl->invalid_dir);
		fl->invalid_dir = NULL;
	}
	return (1);
}
