/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 18:25:18 by nwang             #+#    #+#             */
/*   Updated: 2018/02/27 10:28:53 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		check_flags(char *s, t_flags *fl)
{
	int i;
	int x;

	i = 1;
	x = 0;
	while (s[i])
	{
		if (s[i] == 'l' || s[i] == 'R' || s[i] == 'a' || s[i] == 'r'||
				s[i] == 't' || s[i] == 'G')
		{
			if (s[i] == 'l')
				fl->l = 1;
			if (s[i] == 'R')
				fl->R = 1;
			if (s[i] == 'a')
				fl->a = 1;
			if (s[i] == 'r')
				fl->r = 1;
			if (s[i] == 't')
				fl->t = 1;
			if (s[i] == 'G')
				fl->l = 1;
			x = 1;
		}
		i++;
	}
	return (x);
}

void	target_dir(struct stat *buf, char **argv)
{
	int i;
	int x;
	t_flags fl;
	DIR *temp;
	struct dirent *dir;

	temp = NULL;
	dir = NULL;
	i = 0;
	x = 1;
	ft_bzero(&fl, sizeof(t_flags));
	if (argv[1][i] == '-' && argv[1][i + 1])
	{
		if (!check_flags(argv[1], &fl))
		{
			ft_printf("Error, illegal flag\n");
			ft_printf("usage: ./ft_ls [-lRartG] [file ...]\n");
			exit(0);
		}
		x++;
	}
	while(argv[x])
	{
		if ((temp = opendir(argv[x])) == NULL)
		{
			ft_printf("Cannot open directory %s\n", argv[x]);
			closedir(temp);
		}
		if ((temp = opendir(argv[x])))
		{
			while ((dir = readdir(temp)) != NULL)
			{
				file_info(dir, buf, &fl);
			}
		}
		closedir(temp);
		x++;
	}
}

void	root_dir()
{
	DIR *temp;
	struct dirent *dir;

	temp = NULL;
	dir = NULL;
	temp = opendir(".");
	if (temp)
		while ((dir = readdir(temp)) != NULL)
			ft_printf("%s\n", dir->d_name);
	closedir(temp);
}

struct node* newNode(int data)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return(node);
}

//insert node function
//pass head
//how i want to store them

int		main(int argc, char **argv)
{
	int i;
	int x;
	struct node *head;
	struct stat buf = {};

	i = 0;
	x = 1;
	head = newNode(1);
	if (argc > 1)
		target_dir(&buf, argv);
	if (argc <= 1)
		root_dir();
	return (0);
}
