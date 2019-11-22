/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:21 by mapandel          #+#    #+#             */
/*   Updated: 2019/11/22 06:03:23 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	del_t_input: delete t_input
**		Frees up a t_input* pointed by its address
**		All the allocated variables inside the structure are freed up too
**		The function do not return a value
*/

static void		del_t_input(t_input *node, size_t unused_value) {
	if (node) {
		if (node->input)
			ft_strdel(&node->input);
		if (node->digest)
			ft_strdel(&node->digest);
		ft_memdel((void**)&node);
	}
}


/*
**	del_t_ssl: delete t_ssl
**		Frees up a t_ssl* pointed by its address
**		All the allocated variables inside the structure are freed up too
**		The function do not return a value
*/

static void		del_t_ssl(t_ssl *ssl) {
	if (ssl) {
		if (ssl->command_name)
			ft_strdel(&ssl->command_name);
		if (ssl->argv)
			ft_strmapdel(&ssl->argv);
		ft_lstdel(&ssl->inputs, (void (*)(void *, size_t))&del_t_input);
		ft_memdel((void**)&ssl);
	}
}


/*
**	init_t_input: initialize t_input
**		Allocates in memory a t_input* structure
**		Initializes its variables
**		Returns it or NULL if the allocation failed
*/

t_input			*init_t_input() {
	t_input		*node;

	if (!(node = ft_memalloc(sizeof(t_input))))
		return (NULL);
	node->input = NULL;
	node->digest = NULL;
	node->flags = 0;
	return (node);
}


/*
**	init_t_ssl: initialize t_ssl
**		Allocates in memory a t_ssl* structure
**		Initializes its variables
**		Duplicates argv as a char** in the structure for easy access
**		Returns it or NULL if an allocation failed
*/

static t_ssl	*init_t_ssl(t_ssl *ssl, int argc, char **argv) {
	if (!(ssl = ft_memalloc(sizeof(t_ssl))))
		return (NULL);
	ssl->command_name = NULL;
	ssl->flags = 0;
	ssl->return_value = 0;
	ssl->argc = argc;
	ssl->inputs = NULL;
	if (!(ssl->argv = ft_strmapdup((const char**)(unsigned long)argv)))
		return (NULL);

	return (ssl);
}


/*
**	main:
**		Initializes the t_ssl structure "container" for the project
**		Parses argv for the algorithm, inputs to convert and flags
**		Executes the choosen algorithm
**		Displays all the collected digests
**		And finishes by freeing all the allocated memory blocs
**		Returns a negative value for a failed allocation or wrong parsing,
**			zero otherwise
*/

int				main (int argc, char **argv) {
	t_ssl	*ssl;
	int		return_value;

	// Initialization
	ssl = NULL;
	return_value = 0;
	if (!(ssl = init_t_ssl(ssl, argc, argv)))
		return (-1);

	// Parsing
	if (parsing(ssl))
	{
		return_value = ssl->return_value;
		del_t_ssl(ssl);
		return (return_value);
	}

	// Execution
	//	if (ft_strcmp(ssl->command_name, "md5"))
	//		md5(ssl);
	//	else if (ft_strcmp(ssl->command_name, "sha256"))
	//		sha256(ssl);

	// Display
	// Debug purpose
	// display_t_ssl(ssl);

	// Freeing
	return_value = ssl->return_value;
	del_t_ssl(ssl);

	// Debug purpose
	// infinite_loop(&ssl);

	return (return_value);
}
