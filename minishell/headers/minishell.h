/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:44:21 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/28 11:41:01 by rteles-f         ###   ########.fr       */
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
# include <termios.h>
# include <dirent.h>
# include <sys/types.h>
# define PARENT -350
# define HERE write(1, "here\n", 5)
# define ALMOST write(1, "almost\n", 7)
# define THERE write(1, "there\n", 6)

typedef void				(*t_exe)();
typedef struct s_control	t_control;
typedef struct s_command	t_command;
typedef struct sigaction	t_sigaction;

struct s_control {
	char		*input;
	char		**envp;
	char		**paths;
	char		***tokens;
	char		*prompt;
	int			temp;
	int			in_out[2];
	int			status;
	t_sigaction	siginfo;
	t_list		*commands;
} ;

struct s_command {
	char		*exec_path;
	char		**flags;
	char		**terminal;
	int			id;
	int			in_pipe[2];
	int			out_pipe[2];
	int			status;
	int			parse;
	t_control	*main;
	t_exe		execute;
} ;

// Setup
void		setup(t_control *get, char **envp);
char		*get_prompt(void);
void		control_d(int signal);
void		control_c(int signal);
char 		**dup_env(char **env);

// Main
void		catch_input(t_control *get);
t_control	**control(void);

//Execution
void		run_input(t_control *get);
void		find_directions(t_list *this);
void		execute_command(t_command *get);
void		check_dup2(int in, int out);
void		safe_close_fd(int fd, int fd2);

// Commands
void		structure_commands(t_control *get);
t_command	*new_command(t_control *get);
t_exe		solve(char *find);
void		try_command(t_command *get, int index);
char		*build_executable_path(t_control *get, char *command);

// Normalize
void		normalize_input(t_control *get);
int			count_cases(char **string);

// Cleanup/Reset
void		end_shell(t_control *get);
void		input_reset(t_control *get);
void		delete_command(void *command);
void		safe_free_null(char **string);

// Built-in: prepare | execute
void		cd_prepare(t_command *command, int index);
void		pwd_prepare(t_command *get, int index);
void		env_prepare(t_command *command, int index);
void		echo_prepare(t_command *command, int index);
void		unset_prepare(t_command *command, int index);
void		status_prepare(t_command *command, int index);
void		export_prepare(t_command *command, int index);
void		input_redirect(t_command *command, int index);
void		output_redirect(t_command *command, int index);

void		do_nothing(void);
void		cd_execute(char	*str);
void		exit_execute(t_command *command, int index);
void		status_execute(char *print);
void		builtin_execute(char *print);
void		bonus_execute(t_command *command, int index);

// Shellsplit + 4
char		**shell_split(char *s);

// Shellsplit Utils
int			split_case(char *line);
void		free_shellsplit(char ****arg);
char		**copy_shellsplit(char **split);
int			ignore_quotes(char *string);
void		*free_split(char **arg);

// Libft Plus
char		*sttc_itoa(int number);
char		*ft_stradd(char **original, char *add);
char		*ft_unsplit(char **split, int posize, char c);
int			is_space(char c);
void		*free_triple_pointer(char ***pointer);

void		printf_input(t_control *get);
void		finish_list_with(char **list, char *put);
int			valid_sequence(t_list *node);
void		print_split_input(char ***input);
void		stop_command(char **split);

void		start_subshell(t_command *command, int index);
void		end_subshell(t_command *command);

char 		**find_var(char *name, char **env, int *index, int *size);

#endif