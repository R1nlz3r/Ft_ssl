/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_computations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 02:57:44 by mapandel          #+#    #+#             */
/*   Updated: 2020/01/31 04:08:31 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	md5_computations:
**		Confuses and rotates the parameters according to a 512bits word
**		Thoses will update the hasing values at the end
*/

void				md5_computations(t_md5 *md)
{
	unsigned int	i;
	unsigned int	tmp;

	i = 0;
	while (i < 64)
	{
		if (i < 16)
		{
			md->f = (md->b & md->c) | (~md->b & md->d);
			md->g = i;
		}
		else if (i < 32)
		{
			md->f = (md->d & md->b) | (~md->d & md->c);
			md->g = (i * 5 + 1) % 16;
		}
		else if (i < 48)
		{
			md->f = md->b ^ md->c ^ md->d;
			md->g = (i * 3 + 5) % 16;
		}
		else
		{
			md->f = md->c ^ (md->b | ~md->d);
			md->g = (i * 7) % 16;
		}

		tmp = md->d;
		md->d = md->c;
		md->c = md->b;
		md->b += ft_left_rotate_u32(md->a + md->f + md->k[i] + md->w[md->g],
			md->r[i]);
		md->a = tmp;

		++i;
	}
}
