/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:58:01 by mapandel          #+#    #+#             */
/*   Updated: 2020/03/06 16:08:45 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	parsing_flag_s:
**		Sets up a new input argument from a 's' flag trigger
**		Computes the digest for the found argument
**		Displays it
**		A missing input is considered a parsing error,
**			it then displays the appropriate error message
**		Returns a negative value for a failed allocation or a parsing error
*/

static int		parsing_flag_s(t_ssl *ssl, size_t *argv_i, size_t *argv_j,
	size_t len)
{
	ssl->bool_one_conversion_done = 1;
	if (*argv_j + 1 < len)
	{
		if (parsing_file(ssl, &ssl->argv[*argv_i][++*argv_j], FLAG_S) == -1)
			return (-1);
	}
	else if (*argv_i + 1 < ssl->argc)
	{
		if (parsing_file(ssl, ssl->argv[++*argv_i], FLAG_S) == -1)
			return (-1);
	}
	else
		return (display_parsing_error(ssl, ERR_OPT_WITHOUT_ARG,
		&ssl->argv[*argv_i][*argv_j]));

	return (0);
}


/*
**	parsing_flag_p:
**		Sets up a new input argument from a 'p' flag trigger
**		Computes the digest for the found argument
**		Displays it
**		Returns a negative value for a failed allocation
*/

static int		parsing_flag_p(t_ssl *ssl)
{
	ssl->bool_one_conversion_done = 1;
	if (parsing_file(ssl, NULL, FLAG_P) == -1)
		return (-1);

	return (0);
}


/*
**	parsing_flags_search:
**		Iterates for potential flags on an argument
**		Handles 'qr' and delegates 'ps' flags
**		An invalid option is considered a parsing error,
**			it then displays the appropriate error message
**		Returns a negative value for a failed allocation or a parsing error
*/

static int		parsing_flags_search(t_ssl *ssl, size_t *argv_i, size_t len)
{
	size_t		argv_j;

	argv_j = 1;
	while (argv_j < len)
	{
		if (ssl->argv[*argv_i][argv_j] == 'p')
		{
			if (parsing_flag_p(ssl) == -1)
				return (-1);
		}
		else if (ssl->argv[*argv_i][argv_j] == 'q')
		{
			if (!(ssl->flags & FLAG_Q))
				ssl->flags += FLAG_Q;
		}
		else if (ssl->argv[*argv_i][argv_j] == 'r')
		{
			if (!(ssl->flags & FLAG_R))
				ssl->flags += FLAG_R;
		}
		else if (ssl->argv[*argv_i][argv_j] == 's')
			return (parsing_flag_s(ssl, argv_i, &argv_j, len));
		else
			return (display_parsing_error(ssl, ERR_INVALID_OPT,
				&ssl->argv[*argv_i][argv_j]));
		++argv_j;
	}

	return (0);
}


/*
**	parsing_flags:
**		Filters a flag search for an argument
**		Handles "-" and "--" flags and delegates the rest
**		Sets up the appropriate arguments and flags to initialize right away
**		Returns a negative value for a failed allocation or a parsing error
*/

int				parsing_flags(t_ssl *ssl, size_t *argv_i)
{
	size_t		len;

	// Stops parameters parsing
	len = ft_strlen(ssl->argv[*argv_i]);
	if (len == 1)
	{
		ssl->flags += FLAG_END_OF_PARAMETERS;
		ssl->bool_one_conversion_done = 1;
		return (parsing_file(ssl, ssl->argv[*argv_i], 0));
	}
	else if (ft_strequ(ssl->argv[*argv_i], "--"))
	{
		ssl->flags += FLAG_END_OF_PARAMETERS;
		if (*argv_i == 2)
			ssl->bool_one_conversion_done = 1;
		return (0);
	}

	// Iterates on potential flags
	return (parsing_flags_search(ssl, argv_i, len));
}
