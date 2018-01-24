/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/01 15:33:46 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/01 15:33:46 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *elem;

	if (!(elem = (t_list*)malloc(sizeof(elem))))
		return (NULL);
	if (!content)
	{
		elem->content_size = 0;
		elem->content = NULL;
	}
	else
	{
		if (!(elem->content = malloc(sizeof(content))))
		{
			free(elem);
			return (NULL);
		}
		ft_memcpy(elem->content, content, content_size);
		elem->content_size = content_size;
	}
	elem->next = NULL;
	return (elem);
}
