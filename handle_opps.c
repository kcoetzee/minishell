#include "main.h"

t_command	*append_file(t_command *list, int *old_fd)
{
	int			new_fd[2];
	int			status;
	int			pid;
	t_command	*file;

	close(old_fd[1]);
	debug("APPEND FILE LAUNCHED...>>...");
	if (list->next)
		file = list->next;
	else
	{
		debug(list->file_name);
		debug("FORMATTING ERROR: No file name specified");
		exit(1);
	}
	if(pipe(new_fd) < 0)
	{
		debug("PIPE ERROR IN APPEND_FILE");
		exit(1);
	}
	if ((pid = fork()) == 0) //child process
	{
		close(new_fd[0]);//close read end of pipe (about to wtite)
		new_fd[1] = open(file->file_name, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		dup2(old_fd[0], 0);//DUPLICATE STDIN
		dup2(new_fd[1], 1); //DUPLICATING STDOUT
		fprintf(stderr, "OPENING FILE %s INTO FD-> %d\n", file->file_name,new_fd[0]);
		dup2(new_fd[0], old_fd[0]);
		launch_program(list);
	}
	else //PARENT process
	{
		while((pid = wait(&status)) != -1)
			fprintf(stderr, "APPEND FILE PROCESS %d exit with %d\n", pid, WEXITSTATUS(status));
		fprintf(stderr, "ASSIGNING OLD FD TO NEW READ FD: %d\n", old_fd[0]);
		close(new_fd[0]);
		close(new_fd[1]);
	}
	if (file->next)
		return(file->next);
	else
		return(file);
}

t_command	*write_file(t_command *list, int old_fd[])
{
	int			new_fd[2];
	int			status;
	int			pid;
	t_command	*file;

	debug("WRITE FILE LAUNCHED...>...");
	close(old_fd[1]); //closing write end of the old read pipe
	if (list->next)
		file = list->next;
	else
	{
		debug(list->file_name);
		debug("FORMATTING ERROR: No file name specified");
		exit(1);
	}
	if ((pid = fork()) == 0) //child process
	{
		close(new_fd[0]);//closing read of pipe im about to write into
		new_fd[1] = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		dup2(old_fd[0], 0);//DUPLICATING STDIN
		dup2(new_fd[1], 1);//DUPLICATING STDOUT
		old_fd[0] = new_fd[0];
		launch_program(list);
	}
	else //PARENT process
	{
		while((pid = wait(&status)) != -1)
			fprintf(stderr, "process %d exit with %d\n", pid, WEXITSTATUS(status));
		close(new_fd[0]);
		close(new_fd[1]);
	}
	if (file->next)
		return(file->next);
	else
		return(file);
}

t_command	*read_file(t_command *list, int old_fd[])
{
	int			new_fd;
	int			status;
	int			pid;
	t_command 	*file;

	close(old_fd[0]);
	if (list->next)
		file = list->next;
	else
	{
		debug(list->file_name);
		debug("FORMATTING ERROR: No file name name specified");
		exit(1);
	}
	if ((new_fd = open(file->file_name, O_RDONLY)) < 0)
	{
		debug("FILE CANNOT BE OPENED OR DOES NOT EXIST");
		exit(1);
	}
	close(new_fd);
	list->args = (t_args*)e_malloc(sizeof(t_args));
	list->args->str = ft_strdup(file->file_name);
	if((pid = fork()) == 0) //CHILD PROCESS
		launch_program(list);
	else //PARENTS
	{
		while((pid = wait(&status)) != -1)
			fprintf(stderr, "process %d exit with %d\n", pid, WEXITSTATUS(status));
	}
	if (file->next)
		return(file->next);
	else
		return(file);
}

t_command	*handle_opps(t_command *list, int *old_fd)
{
	if (ft_strcmp(list->terminator, ">") == 0)
		list = write_file(list, old_fd);
	else if (ft_strcmp(list->terminator, "<") == 0)
		list = read_file(list, old_fd);
	else if (ft_strcmp(list->terminator, ">>") == 0)
		list = append_file(list, old_fd);
	//possible recursion loop for multiple opperators in a sequence
	//if (is_opp_str(list->terminator))
	//	handle_opps(l)
	fprintf(stderr, "LIST RETURNED FROM handle_opps: [%s]\n", list->file_name);
	return(list);
}
