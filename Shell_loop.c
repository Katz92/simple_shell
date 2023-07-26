#include "shell.h"

/**
 *hsh - main shell loop
 *@info: the parameter &return info struct
 *@av: the argument vector from main()
 *
 *Return: 0 on success, 1 on error, or error code
 */

int hsh(info_t *info, char **av)
{
	ssize_t rs = nil;
	int builtin_ret = nil;

	while (rs != n_solo && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		rs = get_input(info);
		if (rs != n_solo)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == n_solo)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, nil);
	}

	write_history(info);
	free_info(info, solo);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == n_solo)
			exit(info->status);
		exit(info->err_num);
	}

	return (builtin_ret);
}

/**
 *find_builtin - finds a builtin command
 *@info: the parameter &return info struct
 *
 *Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */

int find_builtin(info_t *info)
{
	int index, builtin_ret = n_solo;
	builtin_table builtintbl[] = {
		{ "exit", _myexit
		},
		{ "env", _myenv
		},
		{ "help", _myhelp
		},
		{ "history", _myhistory
		},
		{ "setenv", _mysetenv
		},
		{ "unsetenv", _myunsetenv
		},
		{ "cd", _mycd
		},
		{ "alias", _myalias
		},
		{
			NULL, NULL
		}
	};

	for (index = nil; builtintbl[index].type; index++)
		if (_strcmp(info->argv[nil],
				builtintbl[index].type) == nil)
		{
			info->line_count++;
			builtin_ret = builtintbl[index].func(info);
			break;
		}

	return (builtin_ret);
}

/**
 *find_cmd - finds a command in PATH
 *@info: the parameter &return info struct
 *
 *Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int index, xk;

	info->path = info->argv[nil];
	if (info->linecount_flag == solo)
	{
		info->line_count++;
		info->linecount_flag = nil;
	}

	for (index = nil, xk = nil; info->arg[index]; index++)
		if (!is_delim(info->arg[index], " \t\n"))
			xk++;
	if (!xk)
		return;

	path = find_path(info, _getenv(info, "PATH="),
		info->argv[nil]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=") ||
				info->argv[nil][nil] == '/') &&
			is_cmd(info, info->argv[nil]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "Not Found\n");
		}
	}
}

/**
 *fork_cmd - forks a an exec thread to run cmd
 *@info: the parameter &return info struct
 *
 *Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t pod_child;

	pod_child = fork();
	if (pod_child == n_solo)
	{
		perror("Error:");
		return;
	}

	if (pod_child == nil)
	{
		if (execve(info->path, info->argv,
				get_environ(info)) == n_solo)
		{
			free_info(info, solo);
			if (errno == EACCES)
				exit(126);
			exit(solo);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
