/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:44:21 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/06 18:42:17 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <libft.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# define HERE write(1, "here\n", 5)
# define ALMOST write(1, "almost\n", 7)
# define THERE write(1, "there\n", 6)


typedef struct s_control	t_control;
typedef struct s_func		t_func;
typedef struct s_shell		t_shell;
typedef struct s_command	t_command;
typedef struct sigaction	t_sigaction;
typedef void				(*t_exe)();

struct s_control {
	char		*input;
	char		**envp;
	char		**paths;
	char		***pieces;
	int			pipe[2];
	t_sigaction	siginfo;
	t_list		*commands;
} ;

typedef struct s_command {
	char		*exec_path;
	char		**flags;
	char		**terminal;
	char		*aux;
	int			id;
	int			instream;
	int			pipe[2];
	int			is_last;
	int			counter;
	int			valid;
	t_control	*main;
	t_exe		execute;
} t_command;

char	*sttc_itoa(int number);
void	free_biarray(void **arg, int size);
char	*ft_stradd(char **original, char *add);
char	**shell_split(char *s, char c);
void	free_split(char **arg);
void	free_shellsplit(char ***arg);
void	delete_command(void *command);
void	printf_input(t_control *get);

void	normalize_input(t_control *get);
int		ignore_quotes(char *string);
void	free_shellsplit(char ***arg);

void	execve_aux(t_command *get);
void	setup(t_control *get, char **envp);
void	structure_commands(t_control *get);
void	run_input(t_list *node);

char	*ft_unsplit(char **split, int posize);
void	echo_prepare(t_command *command, int index);
void	echo_exe(t_command *get);
void	do_nothing(void);


#endif