/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 05:10:29 by mapandel          #+#    #+#             */
/*   Updated: 2020/03/06 16:24:58 by mapandel         ###   ########.fr       */
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
	str = (unsigned char*)&md->h0; // + h1 + h2 + h3 behind in the structure

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
**	md5_main_loop:
**		Launches rounds of encryption per 512bits of the message
**		Prepares and updates the hasing values according
**			to the results of each round
*/

static int				md5_main_loop(t_input *input, t_md5 *md)
{
	int		ret;

	while (1)
	{
		if ((ret = md5_message_obtaining(input)))
			return (ret);
		md->w = (unsigned int*)(unsigned long long)input->msg;

		md->a = md->h0;
		md->b = md->h1;
		md->c = md->h2;
		md->d = md->h3;

		md5_computations(md);

		// Update hashing values
		md->h0 += md->a;
		md->h1 += md->b;
		md->h2 += md->c;
		md->h3 += md->d;

		if (md5_message_dumping(input))
			break ;
	}

	return (0);
}


/*
**	md5_init_constants:
**		Initializes the variables used for the md5 algorithm
*/

static void				md5_init_constants(t_md5 *md)
{
	int		i;

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
}


/*
**	md5:
**		Initializes the variables used for the md5 algorithm
**		Computes the hashing variables and concatenates the message digest
**		Returns a negative value for a failed allocation
*/

int						md5(t_input *input)
{
	t_md5		*md;
	int			ret_val;

	// Data container for the computations variables
	if (!(md = ft_memalloc(sizeof(t_md5))))
		return (-1);

	// Initialization
	md5_init_constants(md);

	// Iteration
	ret_val = md5_main_loop(input, md);

	// Digest contraction
	if (!ret_val)
		ret_val = md5_produce_digest(input, md);

	ft_memdel((void**)&md);

	return (ret_val);
}
