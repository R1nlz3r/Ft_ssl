/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_computations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 04:41:35 by mapandel          #+#    #+#             */
/*   Updated: 2020/02/01 04:41:51 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	sha256_computations:
**		Confuses and rotates the parameters according to a 512bits word
**		Thoses will update the hasing values at the end
*/

void				sha256_computations(t_sha256 *sha)
{
	size_t		i;

	i = 0;
	while (i < 64)
	{
		sha->s0 = ft_right_rotate_u32(sha->e, 6)
			^ ft_right_rotate_u32(sha->e, 11) ^ ft_right_rotate_u32(sha->e, 25);
		sha->s1 = ft_right_rotate_u32(sha->a, 2)
			^ ft_right_rotate_u32(sha->a, 13) ^ ft_right_rotate_u32(sha->a, 22);
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
