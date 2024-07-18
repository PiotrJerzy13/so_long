/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:38:13 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/03/13 20:53:02 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	size_t	i;
	size_t	nb;
	char	*p;

	nb = n * size;
	p = malloc(nb);
	if (p != NULL)
	{
		i = 0;
		while (i < nb)
		{
			p[i] = 0;
			i++;
		}
	}
	return (p);
}
