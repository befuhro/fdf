/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/01 15:33:45 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/01 15:33:45 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *next_to_del;

	while (*alst)
	{
		next_to_del = (*alst)->next;
		ft_lstdelone(&(*alst), del);
		*alst = next_to_del;
	}
	*alst = NULL;
}
