/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 21:42:12 by nwang             #+#    #+#             */
/*   Updated: 2018/03/15 21:16:34 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_info		*node_stat(char *path)
{
	t_info	*nstat;

	if (!path)
		return (NULL);
	if (!(nstat = (t_info *)malloc(sizeof(t_info))))
	{
		ft_printf("Error, failed memory allocation.\n");
		return (NULL);
	}
	if (lstat(path, &nstat->p_stat) == -1)
	{
		free(nstat);
		return (NULL);
	}
	return (nstat);
}

t_tree		*new_node(char *c_dir, char *s)
{
	t_tree		*node;

	if (!(node = (t_tree *)ft_memalloc(sizeof(t_tree))))
	{
		ft_printf("Error, failed memory allocation.\n");
		return (NULL);
	}
	if (!(node->name = ft_strdup(s)))
	{
		free(node);
		ft_printf("Error, failed memory allocation.\n");
		return (NULL);
	}
	node->path = c_dir ? ft_strjoin(c_dir, "/") : NULL;
	node->path = c_dir ? ft_strfjoin(&node->path, s) : ft_strdup(s);
	if ((node->st = node_stat(node->path)))
	{
		node->st->grp = *getgrgid(node->st->p_stat.st_gid);
		node->st->grp.gr_name = ft_strdup(node->st->grp.gr_name);
		node->st->pwd = *getpwuid(node->st->p_stat.st_uid);
		node->st->pwd.pw_name = ft_strdup(node->st->pwd.pw_name);
	}
	return (node);
}

t_tree		*ins_node(t_flags *fl, t_tree *node, t_tree *ls)
{
	if (!(node))
		return (ls);
	if (fl->big_s && ls->st)
		if (ls->st->p_stat.st_size > node->st->p_stat.st_size)
			if ((node->left = ins_node(fl, node->left, ls)))
				return (node);
	if (fl->big_s && ls->st)
		if (ls->st->p_stat.st_size < node->st->p_stat.st_size)
			if ((node->right = ins_node(fl, node->right, ls)))
				return (node);
	if (fl->t && ls->st)
		if ((L_SEC > N_SEC) || ((L_SEC == N_SEC) && (L_NSEC > N_NSEC)))
			if ((node->left = ins_node(fl, node->left, ls)))
				return (node);
	if (fl->t && ls->st)
		if ((L_SEC < N_SEC) || ((L_SEC == N_SEC) && (L_NSEC < N_NSEC)))
			if ((node->right = ins_node(fl, node->right, ls)))
				return (node);
	if (ft_strcmp(ls->name, node->name) < 1)
		node->left = ins_node(fl, node->left, ls);
	else
		node->right = ins_node(fl, node->right, ls);
	return (node);
}
