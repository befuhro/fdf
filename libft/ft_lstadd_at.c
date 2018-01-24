/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstadd_at.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/01 15:33:45 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/01 15:33:45 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_at(t_list *list, t_list *new, unsigned int index)
{
	t_list *adrr;

	adrr = (t_list*)malloc(sizeof(t_list));
	adrr->next = list[index - 1].next;
	list[index - 1].next = new;
	new->next = adrr->next;
	free(adrr);
}
