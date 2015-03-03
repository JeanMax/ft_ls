/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 03:39:14 by mcanal            #+#    #+#             */
/*   Updated: 2015/03/03 15:31:03 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDIT_H

# define EDIT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>

/*
** lst1 struct
*/
typedef struct s_list	t_list;
struct	s_list
{
	void	*content;
	size_t	content_size;
	t_list	*next;
};

/*
** lst2 struct
*/
typedef struct s_lst	t_lst;
struct	s_lst
{
	char	*file;
	char	*dir;
	char	*user;
	char	*group;
	long	date;
	int		user2;
	int		group2;
	int		mode;
	int		mode2;
	int		size;
	int		block;
	int		link;
	char	is_hidden;
	char	is_ninja;
	char	is_dir;
	char	ssize;
	t_lst	*next;
	t_lst	*prev;
};

/*
** lst1
*/
void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
t_list	*ft_lstfind(t_list **alst, void *data);
t_list	*ft_lstnew(void const *content, size_t content_size);
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** lst2
*/

t_lst	*ft_lfind(t_lst **alst, char *data);
void	ft_lfree(t_lst **lst);
t_lst	*ft_lnew(struct dirent *d, struct stat *b, char *dir);
#endif
