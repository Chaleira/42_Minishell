/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:44:21 by rteles-f          #+#    #+#             */
/*   Updated: 2023/08/11 20:13:54 by plopes-c         ###   ########.fr       */
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
// # define ALMOST write(1, "almost\n", 7)
// # define THERE write(1, "there\n", 6)
# define RED "\001\e[01;31m\004"
# define BOLD "\001\e[01;1m\004"
# define BLUE "\001\e[01;34m\004"
# define YELLOW "\001\e[01;33m\004"
# define RESET "\001\e[0m\004"

typedef struct s_control	t_control;
typedef struct s_command	t_command;
typedef struct sigaction	t_sigaction;
typedef void				(*t_exe)();
typedef struct s_iterate	t_iterate;

struct s_control {
	char		*input;
	char		*prompt;
	char		**envp;
	char		**export;
	char		**paths;
	char		***tokens;
	int			in_out[2];
	int			status;
	int			input_count;
	t_sigaction	siginfo;
	t_list		*commands;
} ;

struct s_command {
	char		*exec_path;
	char		**flags;
	char		**terminal;
	int			id;
	int			status;
	int			parse;
	int			in_pipe[2];
	int			out_pipe[2];
	t_control	*main;
	t_exe		execute;
} ;

// Setup + 1 | Utils
void		setup(t_control *get, char **envp);
void		update_paths(char **envp, t_control *get);
char		*get_prompt(void);

char		**get_envaddress(char **envp, char *find);
void		control_c(int signal);
void		control_d(t_control *get);

// Main + 1
t_control	**control(void);

//Execution | Utils
void		run_input(t_control *get);
void		find_directions(t_list *this);
void		execute_command(t_command *get);

void		safe_close_fd(int fd, int fd2);
void		check_dup2(int in, int out);
void		cut_wait(void);

// Commands | Utils
void		structure_commands(t_control *get);
t_exe		solve(char *find);
void		try_command(t_command *get, int index);
char		*build_executable_path(t_control *get, char *command);

t_command	*new_command(t_control *get);
void		delete_command(void *command);
int			is_executable(char *check);

// Normalize + 3
int			normalize_input(t_control *get);
char		**copy_split_size(char **split, int size);

// Cleanup/Reset
void		end_shell(t_control *get);
void		input_reset(t_control *get);
void		safe_free_null(char **string);

// Quotes
int			remove_pair(char *string, char *find);
int			find_pair(char *string, char *jump);

// Expansion + 2
char		*input_expand(char *input, char **envp, int ignore);
char		**wildcard(char *str);
char		**wildcard_aux(char **split);


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
void		exit_execute(t_command *command, int index);
void		bonus_execute(t_command *command, int index);
void		builtin_execute(char *print);
void		do_nothing(void);
int			execute_now(t_command *get);
void		status_expand(t_command *command, int index);

// Shellsplit + 4
char		**shell_split(char *s);

// Shellsplit Utils
int			split_case(char *line);
void		free_shellsplit(char ****arg);
char		**copy_shellsplit(char **split);
void		*free_split(char **arg);
int			ignore_quotes(char *string);

// Libft Plus
char		*sttc_itoa(int number);
char		*ft_stradd(char **original, char *add);
char		*ft_unsplit(char **split, int posize, char c, int flag_nl);
int			is_space(char c);
void		*free_triple_pointer(char ***pointer);

void		finish_list_with(char **list, char *put);
int			valid_sequence(t_list *node);
void		print_split_input(char ***input);
void		stop_command(char ***split);

char		**find_var(char *name, char **env, int *index, int *size);
void		jump_command(t_command *command, int index);
char		*fix_quotes_expand(char *string);

void		update_paths(char **envp, t_control *get);
int			remove_pair(char *string, char *find);
int			find_pair(char *string, char *jump);

int			is_folder_or_file(char *check);
void		cut_wait(void);
void		print_split(char **input);
int			change_env_variable(char **env, char *variable, char *value);
int			split_size(char **split);
int			ft_strlenchr(char *str, char c);

// Parse
char		**parse(char *str, t_control *get);
int			parsing(char **split);
void		here_doc(t_command *get, char *eof);
char		*catch_one(t_control *get);
char		**ft_join_split(char **split, char **add, int index);
int			last_split_index(char **split);
void		stop_heredoc(int signal);
char		**env_copy(char **env, char *new_str);
int			count_char(char **split, char c);
int			check_first_char(char **split);
int			check_last_char(char **split);

#endif
