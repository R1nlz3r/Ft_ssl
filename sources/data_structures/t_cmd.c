/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:10:10 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/21 18:29:32 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	del_t_cmd:
**		Frees up a t_cmd* structure pointed by its address
**		All the allocated variables inside the structure are freed up too
**		The function do not return a value
*/

void			del_t_cmd(t_cmd **cmd)
{
	if (!(cmd && *cmd))
		return ;

	if ((*cmd)->name)
		ft_strdel(&(*cmd)->name);
	if ((*cmd)->md)
		ft_memdel((void**)&(*cmd)->md);
	if ((*cmd)->sha256)
		ft_memdel((void**)&(*cmd)->sha256);
	if ((*cmd)->sha512)
		ft_memdel((void**)&(*cmd)->sha512);

	ft_memdel((void**)cmd);
	*cmd = NULL;
}


/*
**	get_command_step:
**		Returns the command step length corresponding to the command identifier
**			in the structure or a nul value otherwise
*/

static size_t	get_command_step(t_cmd *cmd)
{
	if (cmd->id == CMD_MD5
		|| cmd->id == CMD_SHA256)
		return (64);
	else if (cmd->id == CMD_SHA512)
		return (128);

	return (0);
}


/*
**	get_command_type:
**		Returns the command type corresponding to the command identifier
**			in the structure or a negative value otherwise
*/

static int		get_command_type(t_cmd *cmd)
{
	if (cmd->id == CMD_MD5
		|| cmd->id == CMD_SHA256
		|| cmd->id == CMD_SHA512)
		return (CMD_MESSAGE_DIGEST);

	return (-1);
}


/*
**	get_command_id:
**		Returns the command identifier corresponding to the command name
**			in the structure or a negative value otherwise
*/

static int		get_command_id(t_cmd *cmd)
{
	if (ft_strequ(cmd->name, "md5"))
		return (CMD_MD5);
	else if (ft_strequ(cmd->name, "sha256"))
		return (CMD_SHA256);
	else if (ft_strequ(cmd->name, "sha512"))
		return (CMD_SHA512);

	return (-1);
}


/*
**	set_t_cmd:
**		Sets the t_cmd variables accordingly to the given command name
**		Returns a negative value on fail
*/

int				set_t_cmd(t_cmd *cmd, char *command_name)
{
	if (!(cmd->name = ft_strdup(command_name))
		|| (cmd->id = get_command_id(cmd)) == -1
		|| (cmd->type = get_command_type(cmd)) == -1
		|| (cmd->step = get_command_step(cmd)) == 0)
		return (-1);

	return (0);
}


/*
**	init_t_cmd:
**		Allocates memory for a new t_cmd* structure
**		Initializes its variables
**		Returns it or NULL if an allocation failed
*/

t_cmd			*init_t_cmd(void)
{
	t_cmd		*cmd;

	if (!(cmd = ft_memalloc(sizeof(t_cmd))))
		return (NULL);

	cmd->id = 0;
	cmd->type = 0;
	cmd->step = 0;
	cmd->md = NULL;
	cmd->sha256 = NULL;
	cmd->sha512 = NULL;

	return (cmd);
}
