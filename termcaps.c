#include "main.h"

/* Use this variable to remember original terminal attributes. */

struct termios saved_attributes;

void
reset_input_mode (void)
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void
set_input_mode (void)
{
  struct termios tattr;
  char *name;

  /* Make sure stdin is a terminal. */
  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
    }

  /* Save the terminal attributes so we can restore them later. */
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);

  /* Set the funny terminal modes. */
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

void	interrogate_terminal(void)
{
}

void	init_terminal_data (void)
{
  char *termtype = getenv ("TERM");
  int success;

  if (termtype == 0)
    fprintf(stderr, "Specify a terminal type with `setenv TERM <yourtype>'.\n");

  success = tgetent (term_buffer, termtype);
  if (success < 0)
    fprintf(stderr,"Could not access the termcap data base.\n");
  if (success == 0)
    fprintf(stderr,"Terminal type `%s' is not defined.\n", termtype);
}
