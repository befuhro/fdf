/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/01 15:33:45 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/01 15:33:45 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(t_list *src)
{
	t_list *dst;

	if (!(dst = (t_list*)malloc(sizeof(t_list))))
		return (0);
	if (!src->content)
	{
		dst->content = NULL;
		dst->content_size = 0;
	}
	else
	{
		if (!(dst->content = malloc(sizeof(src->content))))
		{
			free(dst);
			return (0);
		}
		ft_memcpy(dst->content, src->content, src->content_size);
		dst->content_size = src->content_size;
	}
	dst->next = NULL;
	return (dst);
}
