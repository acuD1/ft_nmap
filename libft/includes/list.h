/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 03:12:18 by cempassi          #+#    #+#             */
/*   Updated: 2022/01/02 17:09:00 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include <string.h>

typedef void		*(*t_lstmod)(void *);
typedef void		*(*t_lstmap)(void *, void *);
typedef int			(*t_cmp)(void *, void *);
typedef void		(*t_del)(void *);

typedef struct		s_list
{
	void			*data;
	size_t			data_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_stack
{
	size_t			size;
	t_list			*head;
}					t_stack;

void				ft_mergesort(t_list **lst, int (*cmp)(void *, void *));
t_list				*ft_lstnew(void const *data, size_t data_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *));
void				ft_lstdelnext(t_list *current, void f(void *));
void				*ft_lstdel(t_list **alst, void (*del)(void *));
int					ft_lstdelfirst(t_list **alst, void (*del)(void *));
void				ft_lstadd(t_list **alst, t_list *);
void 				ft_lstfold(t_list *lst, void *acc,\
							void (*f)(void *data, void *acc));
void				ft_lstiter(t_list *lst, void (*f)(void *data));
int		            ft_lstiter_ctx(t_list *lst, void *context
				            , int (*f)(void *data, void* context));
size_t				ft_lstlen(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *context, t_lstmap func
							, t_del del);
t_list				*ft_lstmerge(t_list **alst, t_list *blst);
void				ft_lstrev(t_list **alst);
int					ft_lstaddback(t_list **alst, t_list *);
t_list				*ft_tabtolst(char **t);
t_list				*ft_lstfilter(t_list *lst, void *to_find, t_cmp filter,\
							t_cmp cpy);
t_list				*ft_lstfind(t_list *alst, void *to_find, t_cmp f);
int 				ft_lstmove_if(t_list **src, t_list **dst, void *to_find,\
							t_cmp cmp);
int					ft_lstremove_if(t_list **lst, void *data, t_cmp cmp,\
							t_del del);
t_list				*ft_lstsplit_if(t_list **lst, void *data, t_cmp cmp);
int					ft_lstcmp(t_list *lst1, t_list *lst2,\
					int (*f)(void *, void *));
t_list				*ft_getargslst(int ac, char **av);
int					ft_stckpush(t_stack *stack, void *data, size_t size);
int					ft_stckpushnode(t_stack *stack, t_list *node);
void				*ft_stckpop(t_stack *stack);
t_list				*ft_stckpopnode(t_stack *stack);
size_t				ft_stcksize(t_stack *stack);
void				ft_stckinit(t_stack *stack);
void				*ft_stcktop(t_stack *stack);
void				ft_stckdestroy(t_stack *stack, void (*f)(void *));
char				**ft_lsttotab(t_list *lst, char *(*f)(void *));
void                ft_lst_remove_self(t_list **lst, t_cmp cmp);
#endif
