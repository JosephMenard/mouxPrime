/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:41:45 by mianni            #+#    #+#             */
/*   Updated: 2024/11/13 12:39:54 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Code operateur : 1 = '<' / 2 = '>' / 3 = '<<' / 4 = '>>' 5 = '&&' / 6 = '||'
// 7 = WILDCARDS / 8 = '|' // 9 = $(...) / 10 = Autre // 11 = '...'
// 12 = "..." // 13 (...)

#include "../minishell.h"

int	execute_command(char *path, t_cmd *cmd, char **env_array)
{
	if (execve(path, cmd->cmd_args, env_array) == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		perror(cmd->cmd_args[0]);
		exit_now(127);
		return (1);
	}
	return (0);
}

int	prepare_and_execute(t_ast *ast, t_data *data, char **env_array)
{
	char	*path;

	ast->commande->cmd_args = find_wildcards(ast->commande);
	if (open_n_do_builtins(ast->commande, data, ast->commande->files))
		return (1);
	path = get_path(ast->commande->cmd_args[0], env_array);
	if (!path)
		return (print_command_not_found(ast->commande->cmd_args[0]));
	if (open_files(ast->commande) == 0)
		return (execute_command(path, ast->commande, env_array));
	else
		exit_now(1);
	return (1);
}

int	command_function(t_ast *ast, t_data *data)
{
	t_env	*env;
	char	**env_array;

	env = get_env(NULL);
	env_array = envlist_to_char(env);
	data = get_data(NULL);
	return (prepare_and_execute(ast, data, env_array));
}

int	exec(t_ast *ast, t_data *data)
{
	if (ast->commande->type == 5)
		and_function(ast);
	else if (ast->commande->type == 6)
		or_function(ast, data);
	else if (ast->commande->type == 8)
		pipe_function(ast, data);
	else if (ast->commande->type == 7)
		subshell_function(ast, data);
	else if (ast->commande->type >= 9 && ast->commande->type <=12)
		(command_function(ast, data));
	data = get_data(NULL);
	return (0);
}

void	execute(t_ast *top, t_data *data)
{
	if (check_if_fork_needed(top) == true)
		fork_and_exec(top, data);
	else
		exec(top, data);
}