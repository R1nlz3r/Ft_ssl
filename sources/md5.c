/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 05:10:29 by mapandel          #+#    #+#             */
/*   Updated: 2019/12/08 03:11:47 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	md5_produce_digest:
**		Transforms the hashing values into a digest
**		Returns a negative value for a failed allocation
*/

static int				md5_produce_digest(t_input *input, t_md5 *md)
{
	char			*digest;
	unsigned char	*str;
	char			*tmp;
	int				i;

	digest = NULL;
	str = (unsigned char*)&md->h0; // h1 / h2 / h3 are behind in the structure

	i = 0;
	while (i < 16)
	{
		if (!(tmp = ft_lltoabase_unsigned(str[i++], 16)))
			return (-1);
		if (!tmp[1] && !(digest = ft_strjoin_leakless(digest, "0")))
			return (-1);
		if (!(digest = ft_strjoin_leakless(digest, tmp)))
			return (-1);
		ft_strdel(&tmp);
	}
	input->digest = digest;

	return (0);
}


/*
**	md5_left_rotate:
**		Rotates bitwise by the left a 32bits value
*/

static unsigned int		md5_left_rotate(unsigned int val, unsigned int rot)
{
	return ((val << rot) | (val >> (32 - rot)));
}


/*
**	md5_computations:
**		Confuses and rotates the parameters according to a 512bits word
**		Thoses will update the hasing values at the end
*/

static void				md5_computations(t_md5 *md)
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
		md->b += md5_left_rotate(md->a + md->f + md->k[i] + md->w[md->g],
			md->r[i]);
		md->a = tmp;

		++i;
	}
}


/*
**	md5_main_loop:
**		Launches rounds of encryption per 512bits of the message
**		Prepares and updates the hasing values according
**			to the results of each round
*/

static void				md5_main_loop(t_input *input, t_md5 *md)
{
	size_t		i;

	i = 0;
	while (i < input->msg_len)
	{
		md->w = (void*)(input->msg + i);

		md->a = md->h0;
		md->b = md->h1;
		md->c = md->h2;
		md->d = md->h3;

		md5_computations(md);

		md->h0 += md->a;
		md->h1 += md->b;
		md->h2 += md->c;
		md->h3 += md->d;
		i += 64;
	}
}


/*
**	md5:
**		Initializes the variables used for the md5 algorithm computations
**		Computes, produces and stores the message digest
**		Returns a negative value for a failed allocation
*/

int						md5(t_input *input)
{
	t_md5		*md;
	int			i;

	// Data container for the computations variables
	if (!(md = ft_memalloc(sizeof(t_md5))))
		return (-1);

	// Initialization
	i = 0;
	while (i < 64)
	{
		md->r[i] = md5_rotations[i];
		md->k[i] = (unsigned int)(floor(fabs(sin(i + 1)) * pow(2, 32)));
		++i;
	}
	md->h0 = 1732584193;
	md->h1 = 4023233417;
	md->h2 = 2562383102;
	md->h3 = 271733878;

	// Iteration
	md5_main_loop(input, md);

	// Digest contraction
	if (md5_produce_digest(input, md))
		return (-1);

	ft_memdel((void**)&md);

	return (0);
}
