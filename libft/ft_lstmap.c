/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/01 15:33:46 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/01 15:33:46 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *copy))
{
	t_list *liste;
	t_list *first;
	t_list *copy;

	if (!lst || !f)
		return (NULL);
	copy = f(lst);
	if (!(liste = ft_lstnew(copy->content, copy->content_size)))
		return (NULL);
	lst = lst->next;
	first = liste;
	while (lst)
	{
		copy = f(lst);
		if (!(liste->next = ft_lstnew(copy->content, copy->content_size)))
			return (NULL);
		liste = liste->next;
		lst = lst->next;
	}
	return (first);
}
