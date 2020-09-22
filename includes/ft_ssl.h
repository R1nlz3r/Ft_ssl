/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapandel <mapandel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:54:44 by mapandel          #+#    #+#             */
/*   Updated: 2020/09/23 01:04:34 by mapandel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "md5.h"
# include "sha256.h"
# include "sha512.h"


/* Error types */
# define ERR_FATAL					1			/* Various errors	- Must exit */
# define ERR_NON_BLOCKANT			2			/* File specific	- Program can continue */


/* Error codes */
# define ERR_UNDEFINED				1			/* Undefined error */
# define ERR_MEM_ALLOCATION			2			/* Memory allocation failure */
# define ERR_NO_ARG					3			/* No command was given */
# define ERR_INVALID_CMD_NAME		4			/* Command name not supported */
# define ERR_OPT_WITHOUT_ARG		5			/* Option require a following argument */
# define ERR_INVALID_OPT			6			/* Option not supported */
# define ERR_FILE_ACCESS			7			/* Opening / Reading / Closing a file is not possible */


/* Flags masks */
# define FLAG_END_OF_PARAMETERS		1			/* Stops parameters parsing */
# define FLAG_NO_ARGUMENT			2			/* No argument given to the command */
/* Message digest specific flags */
# define FLAG_P						4			/* Echo STDIN to STDOUT and append the checksum to STDOUT */
# define FLAG_Q						8			/* Quiet mode */
# define FLAG_R						16			/* Reverse the format of the output */
# define FLAG_S						32			/* Print the sum of the given string */


/* Command type identifier */
# define CMD_MESSAGE_DIGEST			1			/* Message digest algorithm */


/*	Command identifier */
# define CMD_MD5					1			/* MD5 algorithm */
# define CMD_SHA256					2			/* SHA256 algorithm */
# define CMD_SHA512					3			/* SHA512 algorithm */


/*
**	t_flag:
**		Stores the parsed flags and their associated parameters
*/

typedef struct		s_flag {
	int				masks_sum;					/* Sum of the bitwise masks */
	char			*s;							/* Print the sum of the given string */
}					t_flag;


/*
**	t_arg:
**		Stores the variables associated to a parsed argument
**		The file name and descriptor identifier
**		The message used for computations and it's digest result
*/

typedef struct		s_arg {
	char			*file_name;					/* File name */
	int				fd;							/* File descriptor identifier */
	int				pad_0;						/* Padding value */
	unsigned char	*msg;						/* Portion of the file read */
	size_t			msg_len;					/* Length of the file current portion */
	size_t			msg_total_len;				/* Sum of portions read */
	char			*digest;					/* Computed digest of the file */
}					t_arg;


/*
**	t_cmd:
**		Stores the name of the choosen algorithm
**		The command and type identifier that corresponds to the command name
**		The length of the file portions to read or iterate the message on
**		And the computation structures of every command available
*/

typedef struct		s_cmd {
	char			*name;						/* Command name */
	int				id;							/* Command identifier */
	int				type;						/* Command type identifier */
	size_t			step;						/* Length of file portions to read */
	t_md5			*md;						/* MD5 algorithm structure */
	t_sha256		*sha256;					/* SHA256 algorithm structure */
	t_sha512		*sha512;					/* SHA512 algorithm structure */
}					t_cmd;


/*
**	t_ssl: data container for this project
**		Stores a t_cmd* structure to access the command variables
**			and inner computation structures
**		A t_arg* structure to access the current argument variables
**		A t_flag* structure to access parsed flags and associated parameters
**		Stores a boolean who assures the command has been executed one time,
**			an execution is forced reading from STDIN if false after the parsing
**		Defines the main return value of the program, 0 on success or
**			1 if at least one of the executions could not be completed
**		Duplicates argv and stores argc value for easy access
*/

typedef struct		s_ssl {
	t_cmd			*cmd;						/* Command variables */
	t_flag			*flags;						/* Parsed flags variables */
	t_arg			*arg;						/* Argument variables */
	int				bool_one_conversion_done;	/* Assures that one convertion has been done */
	int				return_value;				/* Return value of the program */
	size_t			argc;						/* Copy of argc */
	char			**argv;						/* Copy of argv */
}					t_ssl;


/* commands/message_digest/md5.c */
int					md5(t_ssl *ssl);

/* commands/message_digest/sha256.c */
int					sha256(t_ssl *ssl);

/* commands/message_digest/sha512.c */
int					sha512(t_ssl *ssl);

/* data_structures/t_arg.c */
t_arg				*init_t_arg(void);
void				del_t_arg(t_arg **arg);

/* data_structures/t_cmd.c */
t_cmd				*init_t_cmd(void);
int					set_t_cmd(t_cmd *cmd, char *command_name);
void				del_t_cmd(t_cmd **cmd);

/* data_structures/t_flag.c */
t_flag				*init_t_flag(void);
void				add_t_flag_mask(t_flag *flag, int mask_nb, char *parameter);
void				remove_t_flag_mask(t_flag *flag, int mask_nb);
void				remove_one_shot_flags(t_flag *flag);
void				remove_t_flag_i(t_flag *flag);
void				remove_t_flag_o(t_flag *flag);
void				remove_t_flag_s(t_flag *flag);
void				del_t_flag(t_flag **flag);

/* data_structures/t_ssl.c */
t_ssl				*init_t_ssl(t_ssl *ssl, int argc, char **argv);
void				del_t_ssl(t_ssl **ssl);

/* display/errors.c */
void				display_invalid_cmd(char *justification);
void				display_opt_without_arg(t_ssl *ssl, char *justification);
void				display_invalid_opt(t_ssl *ssl, char *justification);
void				display_file_inaccessible(t_ssl *ssl);
void				display_undefined_error(void);

/* display/hash.c */
void				display_hash(t_ssl *ssl);

/* display/usages/c */
void				display_ft_ssl_usage(void);
void				display_md_algorithm_usage(void);
void				display_cipher_algorithm_usage(void);

/* execution/buffer.c　*/
void				buffer_handler(t_ssl *ssl, int bool_dump);

/* execution/execution.c */
void				execution(t_ssl *ssl, char *file_name);

/* execution/file_access.c */
int					file_opening(t_ssl *ssl, char *file_name);
int					file_reading(t_ssl *ssl);
void				file_closing(t_ssl *ssl);

/* execution/message.c */
int 				message_obtention(t_ssl *ssl);
int					message_dump(t_ssl *ssl);
void				set_flag_s_message(t_ssl *ssl);

/* exit/error_handler.c */
void				error_handler(t_ssl *ssl, int error_code,
						char *justification);
void				fatal_errors(t_ssl *ssl, int error_code,
						char *justification);

/* exit/exit_failure.c */
void				exit_failure(t_ssl *ssl) __attribute__((noreturn));

/* parsing/cipher_flags.c */
void				parsing_cipher_flags(t_ssl *ssl, size_t *argv_i,
						size_t len);

/* parsing/files.c */
void				searching_files(t_ssl *ssl, size_t *argv_i);

/* parsing/flags.c */
void				searching_flags(t_ssl *ssl, size_t *argv_i);

/* parsing/message_digest_flags.c */
void				parsing_message_digest_flags(t_ssl *ssl, size_t *argv_i,
						size_t len);

/* parsing/parsing.c */
void				parsing (t_ssl *ssl);

# endif
