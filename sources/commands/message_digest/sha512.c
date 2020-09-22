/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 07:47:47 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 00:45:50 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	produce_sha512_digest:
**		Transforms the final state of hash values into the digest
**		This function do not return a value
*/

static void		produce_sha512_digest_2(t_ssl *ssl, uint64_t hashing_value)
{
	char			*tmp;
	char			*paded;

	if (!(tmp = ft_lltoabase_unsigned(hashing_value, 16)))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	while (tmp && ft_strlen_nullcrashless(tmp) < 16)
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

static void		produce_sha512_digest(t_ssl *ssl, t_sha512 *sha)
{
	produce_sha512_digest_2(ssl, sha->h0);
	produce_sha512_digest_2(ssl, sha->h1);
	produce_sha512_digest_2(ssl, sha->h2);
	produce_sha512_digest_2(ssl, sha->h3);
	produce_sha512_digest_2(ssl, sha->h4);
	produce_sha512_digest_2(ssl, sha->h5);
	produce_sha512_digest_2(ssl, sha->h6);
	produce_sha512_digest_2(ssl, sha->h7);
}


/*
**	sha512_computations:
**		Confuses and rotates the computation parameters
**		This function do not return a value
*/

static void		sha512_computations(t_sha512 *sha)
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


/*
**	set_sha512_words:
**		Sets up the words used for the next round of encryption
**		This function do not return a value
*/

static void		set_sha512_words(t_ssl *ssl, t_sha512 *sha)
{
	size_t		i;

	i = 0;
	while (i < 16)
	{
		sha->w[i] = (uint64_t)((uint64_t)ssl->arg->msg[i * 8] << 56
			| (uint64_t)ssl->arg->msg[i * 8 + 1] << 48
			| (uint64_t)ssl->arg->msg[i * 8 + 2] << 40
			| (uint64_t)ssl->arg->msg[i * 8 + 3] << 32
			| (uint64_t)ssl->arg->msg[i * 8 + 4] << 24
			| (uint64_t)ssl->arg->msg[i * 8 + 5] << 16
			| (uint64_t)ssl->arg->msg[i * 8 + 6] << 8
			| (uint64_t)ssl->arg->msg[i * 8 + 7]);
		++i;
	}
	while (i < 80)
	{
		sha->s0 = ft_right_rotate_u64(sha->w[i - 15], 1)
			^ ft_right_rotate_u64(sha->w[i - 15], 8) ^ (sha->w[i - 15] >> 7);
		sha->s1 = ft_right_rotate_u64(sha->w[i - 2], 19)
			^ ft_right_rotate_u64(sha->w[i - 2], 61) ^ (sha->w[i - 2] >> 6);
		sha->w[i] = sha->w[i - 16] + sha->s0 + sha->w[i - 7] + sha->s1;
		++i;
	}
}


/*
**	sha512_loop:
**		Launches rounds of computations every 1024 bits on the message
**		Sets up the words used
**		Prepares and updates the hasing values according to the result
**			of computations each round
**		Returns zero for on success or a positive value for a failed file access
*/

static int		sha512_loop(t_ssl *ssl, t_sha512 *sha)
{
	while (1)
	{
		if (message_obtention(ssl))
			return (1);

		set_sha512_words(ssl, sha);

		sha->a = sha->h0;
		sha->b = sha->h1;
		sha->c = sha->h2;
		sha->d = sha->h3;
		sha->e = sha->h4;
		sha->f = sha->h5;
		sha->g = sha->h6;
		sha->h = sha->h7;

		sha512_computations(sha);

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
**	init_sha512_constants:
**		Initializes the variables used for the sha256 algorithm
**		This function do not return a value
*/

static void		init_sha512_constants(t_sha512 *sha)
{
	int			i;

	i = 0;
	while (i < 80)
	{
		sha->k[i] = SHA512_K[i];
		i++;
	}
	sha->h0 = UINT64_C(0x6a09e667f3bcc908);
	sha->h1 = UINT64_C(0xbb67ae8584caa73b);
	sha->h2 = UINT64_C(0x3c6ef372fe94f82b);
	sha->h3 = UINT64_C(0xa54ff53a5f1d36f1);
	sha->h4 = UINT64_C(0x510e527fade682d1);
	sha->h5 = UINT64_C(0x9b05688c2b3e6c1f);
	sha->h6 = UINT64_C(0x1f83d9abfb41bd6b);
	sha->h7 = UINT64_C(0x5be0cd19137e2179);
}


/*
**	sha512:
**		Initializes the variables used for the sha512 algorithm
**		Computes the hashing variables and concatenates the message digest
**		Returns zero for on success or a positive value for a failed file access
*/

int				sha512(t_ssl *ssl)
{
	int			ret_val;

	/* Data container for the computations variables */
	if (!(ssl->cmd->sha512 = ft_memalloc(sizeof(t_sha512))))
		error_handler(ssl, ERR_MEM_ALLOCATION, NULL);

	/* Initialization */
	init_sha512_constants(ssl->cmd->sha512);

	/* Iteration */
	ret_val = sha512_loop(ssl, ssl->cmd->sha512);

	/* Digest contraction */
	if (!ret_val)
	{
		produce_sha512_digest(ssl, ssl->cmd->sha512);
		display_hash(ssl);
	}

	ft_memdel((void**)&ssl->cmd->sha512);

	return (ret_val);
}
