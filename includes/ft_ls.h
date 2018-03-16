/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 01:17:12 by nwang             #+#    #+#             */
/*   Updated: 2018/03/16 14:43:50 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <errno.h>
# include "../libft/includes/ft_printf.h"

# define N_SEC (ls->st->p_stat.st_mtimespec.tv_sec)
# define L_SEC (node->st->p_stat.st_mtimespec.tv_sec)
# define N_NSEC (ls->st->p_stat.st_mtimespec.tv_nsec)
# define L_NSEC (node->st->p_stat.st_mtimespec.tv_nsec)
# define C_CYAN    "\x1b[36m"
# define C_RED     "\x1b[31m"
# define C_RESET   "\x1b[0m"

typedef struct		s_info
{
	struct stat		p_stat;
	struct passwd	pwd;
	struct group	grp;
}					t_info;

typedef struct		s_tree
{
	char			*name;
	char			*path;
	t_info			*st;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct		s_flags
{
	int				l;
	int				big_r;
	int				a;
	int				r;
	int				t;
	int				g;
	int				big_g;
	int				big_s;
	int				d_flag;
	int				b_flag;
	int				p_dir;
	int				nline;
	int				inv_flag;
	int				blocks;
	t_tree			*valid_dir;
	t_tree			*invalid_dir;
}					t_flags;

void				l_print(t_flags *fl, t_tree *node);
void				invalid_print(t_tree *node);
void				permission(t_tree *node);
void				run_ls(t_flags *fl, char *d_name);
void				target_dir(t_flags *fl, t_tree *node);
t_tree				*ins_node(t_flags *fl, t_tree *node, t_tree *ls);
t_tree				*new_node(char *c_dir, char *s);
int					clear_ls(t_flags *fl);
void				permission(t_tree *node);
void				clear_tree(t_tree *root);
void				recursive_ls(t_flags *fl, t_tree *root, char *c_dir);
void				print_dir(t_flags *fl, t_tree *root, char *c_dir);
void				print_date(time_t date);

#endif
