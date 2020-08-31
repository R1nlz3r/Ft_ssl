/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_computations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 09:45:50 by mapandel          #+#    #+#             */
/*   Updated: 2020/07/18 11:39:39 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	sha512_computations:
**		Confuses and rotates the parameters according to a 1024 bits word
**		Thoses will update the hasing values at the end
*/

void				sha512_computations(t_sha512 *sha)
{
	size_t		i;

	i = 0;
	while (i < 80)
	{
		sha->s0 = ft_right_rotate_u64(sha->e, 14)
			^ ft_right_rotate_u64(sha->e, 18) ^ ft_right_rotate_u64(sha->e, 41);
		sha->s1 = ft_right_rotate_u64(sha->a, 28)
			^ ft_right_rotate_u64(sha->a, 34) ^ ft_right_rotate_u64(sha->a, 39);
		sha->ch = (sha->e & sha->f) ^ (~sha->e & sha->g);
		sha->maj = (sha->a & sha->b) ^ (sha->a & sha->c) ^ (sha->b & sha->c);
		sha->tmp1 = sha->h + sha->s0 + sha->ch + sha->k[i] + sha->w[i];
		sha->tmp2 = sha->s1 + sha->maj;

		sha->h = sha->g;
		sha->g = sha->f;
		sha->f = sha->e;
		sha->e = sha->d + sha->tmp1;
		sha->d = sha->c;
		sha->c = sha->b;
		sha->b = sha->a;
		sha->a = sha->tmp1 + sha->tmp2;

		++i;
	}
}
