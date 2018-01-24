/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/01 15:33:50 by befuhro      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/01 15:33:50 by befuhro     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c, int *a, int *b)
{
	int	i;
	int	count;

	*a = 0;
	*b = -1;
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	ft_tabcpy(char const *s, char *tab, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
}

char		**ft_strsplit(char const *s, char c)
{
	int		size;
	int		i;
	int		j;
	int		len;
	char	**tab;

	if (s && c)
	{
		size = word_count(s, c, &j, &i);
		if (!(tab = (char**)malloc(sizeof(tab) * (size + 1))))
			return (0);
		while (++i < size)
		{
			while (s[j] == c)
				j++;
			len = word_len(s + j, c);
			if (!(tab[i] = ft_strnew(len)))
				return (0);
			ft_tabcpy(s + j, tab[i], len);
			j = j + len;
		}
		tab[i] = 0;
		return (tab);
	}
	return (0);
}
