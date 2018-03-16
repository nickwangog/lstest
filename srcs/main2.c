/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 21:30:14 by nwang             #+#    #+#             */
/*   Updated: 2018/03/16 12:36:07 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				check_flags(char *s, t_flags *fl, int i, int x)
{
	while (s[i])
	{
		if (s[i] == 'l' || s[i] == 'R' || s[i] == 'a' || s[i] == 'r' ||
				s[i] == 't' || s[i] == 'G' || s[i] == 'S' || s[i] == '-')
		{
			s[i] == 'l' ? fl->l = 1 : 0;
			s[i] == 'R' ? fl->big_r = 1 : 0;
			s[i] == 'a' ? fl->a = 1 : 0;
			s[i] == 'r' ? fl->r = 1 : 0;
			s[i] == 't' ? fl->t = 1 : 0;
			s[i] == 'g' ? fl->g = 1 : 0;
			s[i] == 'G' ? fl->big_g = 1 : 0;
			s[i] == 'S' ? fl->big_s = 1 : 0;
			x = 1;
		}
		else
		{
			fl->b_flag = s[i];
			return (0);
		}
		i++;
	}
	if (fl->t == 1 && fl->big_s == 1)
		fl->t = 0;
	return (x);
}

t_flags			*set_flags(int argc, char **argv, t_flags *fl, int x)
{
	int			i;
	t_tree		*ls;

	i = 1;
	ls = NULL;
	while (i < argc && !fl->inv_flag)
	{
		if (fl->d_flag || argv[i][0] != '-' || ft_strlen(argv[i]) == 1)
		{
			ls = new_node(NULL, argv[i]);
			fl->d_flag = 1;
			if (!(ls->st))
				fl->invalid_dir = ins_node(fl, fl->invalid_dir, ls);
			else
				fl->valid_dir = ins_node(fl, fl->valid_dir, ls);
		}
		else if (!fl->d_flag)
			if ((!check_flags(argv[i], fl, 0, 0)))
			{
				ft_printf("ft_ls: illegal option -- %c\n", fl->b_flag);
				x = 0;
			}
		i++;
	}
	return (x ? fl : NULL);
}

void			ft_ls(t_flags *fl)
{
	invalid_print(fl->invalid_dir);
	if (fl->invalid_dir || (fl->valid_dir &&
				(fl->valid_dir->left || fl->valid_dir->right)))
		fl->p_dir = 1;
	if (fl->valid_dir || fl->invalid_dir)
		target_dir(fl, fl->valid_dir);
	else
		run_ls(fl, ".");
	clear_ls(fl);
}

int				main(int argc, char **argv)
{
	t_flags		fl;

	ft_bzero(&fl, sizeof(t_flags));
	if (!(set_flags(argc, argv, &fl, 1)))
	{
		ft_printf("usage: ./ft_ls [-lRartGS] [file ...]\n");
		return (clear_ls(&fl));
	}
	ft_ls(&fl);
	return (0);
}
