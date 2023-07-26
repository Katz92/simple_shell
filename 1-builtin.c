#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */

int _myexit(info_t *info)
{
	int check_exit;

	if (info->argv[solo]) /* If there is an exit arguement */
	{
		check_exit = _erratoi(info->argv[solo]);
		if (check_exit == n_solo)
		{
			info->status = duo;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[solo]);
			_eputchar('\n');
			return (solo);
		}
		info->err_num = _erratoi(info->argv[solo]);
		return (-2);
	}
	info->err_num = n_solo;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int _mycd(info_t *info)
{
	int chdirectory;
	char *s, *directory, buffer[1024];

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[solo])
	{
		directory = _getenv(info, "HOME=");
		if (!directory)
			chdirectory = /* TODO: what should this be? */
				chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
		else
			chdirectory = chdir(directory);
	}
	else if (_strcmp(info->argv[solo], "-") == nil)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (solo);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirectory = /* TODO: what should this be? */
			chdir((directory = _getenv(info, "OLDPWD=")) ? directory : "/");
	}
	else
		chdirectory = chdir(info->argv[solo]);
	if (chdirectory == n_solo)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[solo]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (nil);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int _myhelp(info_t *info)
{
	char **arguments_array;

	arguments_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (nil)
		_puts(*arguments_array); /* temp att_unused workaround */
	return (nil);
}
