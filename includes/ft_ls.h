#ifndef FT_LS_H
# define FT_LS_H

#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <errno.h>
#include "../libft/includes/ft_printf.h"

struct node 
{
    int data;
    struct node *left;
    struct node *right;
};

typedef struct		s_flags
{
	int l;
	int R;
	int a;
	int r;
	int t;
	int	g;
}					t_flags;

/*typedef struct		s_size
{
	int				total;
	int				size;
	int				groupspace;
	int				userspace;
	int				linkspace;
	int				min;
	int				maj;
}					t_size;*/

typedef struct		s_info
{
	char			*name;
//	char			*path;
	time_t			date;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	quad_t			st_blocks;
	dev_t			st_rdev;
	struct s_elem	*next;
}					t_info;

void	file_info(struct dirent *dir, struct stat *buf, t_flags *fl);
void	print_finfo(t_info *info, t_flags *fl);

#endif
