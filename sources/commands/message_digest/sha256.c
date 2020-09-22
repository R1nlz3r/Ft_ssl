/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 04:00:58 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 00:50:38 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	produce_sha256_digest:
**		Transforms the final state of hash values into the digest
**		This function do not return a value
*/

static void		produce_sha256_digest_2(t_ssl *ssl, uint32_t hashing_value)
{
	char			*tmp;
	char			*paded;

	if (!(tmp = ft_lltoabase_unsigned(hashing_value, 16)))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	while (tmp && ft_strlen_nullcrashless(tmp) < 8)
	{
		paded = ft_strjoin("0", tmp);
		ft_strdel(&tmp);
		tmp = paded;
	}
	if (!tmp)
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	if (!(ssl->arg->digest = ft_strjoin_leakless(ssl->arg->digest, tmp)))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	ft_strdel(&tmp);
}

static void		produce_sha256_digest(t_ssl *ssl, t_sha256 *sha)
{
	produce_sha256_digest_2(ssl, sha->h0);
	produce_sha256_digest_2(ssl, sha->h1);
	produce_sha256_digest_2(ssl, sha->h2);
	produce_sha256_digest_2(ssl, sha->h3);
	produce_sha256_digest_2(ssl, sha->h4);
	produce_sha256_digest_2(ssl, sha->h5);
	produce_sha256_digest_2(ssl, sha->h6);
	produce_sha256_digest_2(ssl, sha->h7);
}


/*
**	sha256_computations:
**		Confuses and rotates the computation parameters
**		This function do not return a value
*/

static void		sha256_computations(t_sha256 *sha)
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


/*
**	set_sha256_words:
**		Sets up the words used for the next round of encryption
**		This function do not return a value
*/

static void		set_sha256_words(t_ssl *ssl, t_sha256 *sha)
{
	size_t		i;

	i = 0;
	while (i < 16)
	{
		sha->w[i] = (uint32_t)
			(ssl->arg->msg[i * 4 + 0] << 24
			| ssl->arg->msg[i * 4 + 1] << 16
			| ssl->arg->msg[i * 4 + 2] << 8
			| ssl->arg->msg[i * 4 + 3]);
		++i;
	}
	while (i < 64)
	{
		sha->s0 = ft_right_rotate_u32(sha->w[i - 15], 7)
			^ ft_right_rotate_u32(sha->w[i - 15], 18) ^ (sha->w[i - 15] >> 3);
		sha->s1 = ft_right_rotate_u32(sha->w[i - 2], 17)
			^ ft_right_rotate_u32(sha->w[i - 2], 19) ^ (sha->w[i - 2] >> 10);
		sha->w[i] = sha->w[i - 16] + sha->s0 + sha->w[i - 7] + sha->s1;
		++i;
	}
}


/*
**	sha256_loop:
**		Launches rounds of computations every 512 bits on the message
**		Sets up the words used
**		Prepares and updates the hasing values according to the result
**			of computations each round
**		Returns zero for on success or a positive value for a failed file access
*/

static int		sha256_loop(t_ssl *ssl, t_sha256 *sha)
{
	while (1)
	{
		if (message_obtention(ssl))
			return (1);

		set_sha256_words(ssl, sha);

		sha->a = sha->h0;
		sha->b = sha->h1;
		sha->c = sha->h2;
		sha->d = sha->h3;
		sha->e = sha->h4;
		sha->f = sha->h5;
		sha->g = sha->h6;
		sha->h = sha->h7;

		sha256_computations(sha);

		/* Update hashing values */
		sha->h0 += sha->a;
		sha->h1 += sha->b;
		sha->h2 += sha->c;
		sha->h3 += sha->d;
		sha->h4 += sha->e;
		sha->h5 += sha->f;
		sha->h6 += sha->g;
		sha->h7 += sha->h;

		if (message_dump(ssl))
			return (0);
	}
}


/*
**	init_sha256_constants:
**		Initializes the variables used for the sha256 algorithm
**		This function do not return a value
*/

static void		init_sha256_constants(t_sha256 *sha)
{
	int			i;

	i = 0;
	while (i < 64)
	{
		sha->k[i] = SHA256_K[i];
		++i;
	}
	sha->h0 = 1779033703;
	sha->h1 = 3144134277;
	sha->h2 = 1013904242;
	sha->h3 = 2773480762;
	sha->h4 = 1359893119;
	sha->h5 = 2600822924;
	sha->h6 = 528734635;
	sha->h7 = 1541459225;
}


/*
**	sha256:
**		Initializes the variables used for the sha256 algorithm
**		Computes the hashing variables and concatenates the message digest
**		Returns zero for on success or a positive value for a failed file access
*/

int				sha256(t_ssl *ssl)
{
	int			ret_val;

	/* Data container for the computations variables */
	if (!(ssl->cmd->sha256 = ft_memalloc(sizeof(t_sha256))))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	/* Initialization */
	init_sha256_constants(ssl->cmd->sha256);

	/* Iterations */
	ret_val = sha256_loop(ssl, ssl->cmd->sha256);

	/* Digest contraction */
	if (!ret_val)
	{
		produce_sha256_digest(ssl, ssl->cmd->sha256);
		display_hash(ssl);
	}

	ft_memdel((void**)&ssl->cmd->sha256);

	return (ret_val);
}
