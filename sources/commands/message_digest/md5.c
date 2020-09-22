/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 05:10:29 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 00:51:27 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	produce_md5_digest:
**		Transforms the final state of hash values into the digest
**		This function do not return a value
*/

static void		produce_md5_digest(t_ssl *ssl, t_md5 *md)
{
	char			*digest;
	unsigned char	*str;
	char			*tmp;
	int				i;

	digest = NULL;
	str = (unsigned char*)&md->h0; /* + h1 + h2 + h3 behind in the structure */

	i = 0;
	while (i < 16)
	{
		if (!(tmp = ft_lltoabase_unsigned(str[i++], 16))
			|| (!tmp[1] && !(digest = ft_strjoin_leakless(digest, "0")))
			|| !(digest = ft_strjoin_leakless(digest, tmp)))
			error_handler(ssl, ERR_MEM_ALLOCATION, NULL);
		ft_strdel(&tmp);
	}

	ssl->arg->digest = digest;
}


/*
**	md5_computations:
**		Confuses and rotates the computation parameters
**		This function do not return a value
*/

static void		md5_computations(t_md5 *md)
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


/*
**	md5_loop:
**		Launches rounds of computations every 512 bits on the message
**		Prepares and updates the hasing values according to the result
**			of computations each round
**		Returns zero for on success or a positive value for a failed file access
*/

static int		md5_loop(t_ssl *ssl, t_md5 *md)
{
	while (1)
	{
		if (message_obtention(ssl))
			return (1);

		md->w = (unsigned int*)(unsigned long long)ssl->arg->msg;

		md->a = md->h0;
		md->b = md->h1;
		md->c = md->h2;
		md->d = md->h3;

		md5_computations(md);

		/* Update hashing values */
		md->h0 += md->a;
		md->h1 += md->b;
		md->h2 += md->c;
		md->h3 += md->d;

		if (message_dump(ssl))
			return (0);
	}
}


/*
**	init_md5_constants:
**		Initializes the variables used for the md5 algorithm
**		This function do not return a value
*/

static void		init_md5_constants(t_md5 *md)
{
	int		i;

	i = 0;
	while (i < 64)
	{
		md->r[i] = MD5_R[i];
		md->k[i] = (unsigned int)(floor(fabs(sin(i + 1)) * pow(2, 32)));
		++i;
	}
	md->h0 = 1732584193;
	md->h1 = 4023233417;
	md->h2 = 2562383102;
	md->h3 = 271733878;
}


/*
**	md5:
**		Initializes the variables used for the md5 algorithm
**		Computes the hashing variables and concatenates the message digest
**		Returns zero for on success or a positive value for a failed file access
*/

int				md5(t_ssl *ssl)
{
	int			ret_val;

	/* Data container for the computations variables */
	if (!(ssl->cmd->md = ft_memalloc(sizeof(t_md5))))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	/* Initialization */
	init_md5_constants(ssl->cmd->md);

	/* Iterations */
	ret_val = md5_loop(ssl, ssl->cmd->md);

	/* Digest contraction */
	if (!ret_val)
	{
		produce_md5_digest(ssl, ssl->cmd->md);
		display_hash(ssl);
	}

	ft_memdel((void**)&ssl->cmd->md);

	return (ret_val);
}
