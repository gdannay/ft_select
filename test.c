#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <termios.h>

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


/*int              main(int ac, char **av, char **env)
  {
  char           *name_term;
  struct termios *term = NULL;

  (void)ac;
  (void)av;
  (void)env;
  if ((name_term = getenv("TERM")) == NULL)
  return (-1);
  if (tgetent(NULL, name_term) == ERR)
  return (-1);
// remplis la structure termios des possibilités du terminal.
if (tcgetattr(0, term) == -1)
return (-1);
}*/

/*int     main()
  {
  const char *name;
  char  *bp;
  char  *term;
  int   height;
  int   width;

  bp = malloc(sizeof(*bp));
  name = "TERM";
  if ((term = getenv(name)) == NULL)
  return (1);
  printf("My terminal is %s.\n", term);
  tgetent(bp, term);
  height = tgetnum ("li");
  width = tgetnum ("co");
  printf("H : %d\nL : %d\n", height, width);
  free(bp);
  return (0);
  }*/

#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

int ft_getch()
{

	int buf = 0;
	struct termios old = {0};
	if (tcgetattr(0, &old) < 0)
		perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0)
		perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0)
		perror ("read()");
	return (buf);
}

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int main()
{
	int	car;
//	printf("\033[4mCe test lala.\033[0m");
	while((car = ft_getch()) != 32)
	{
		if (car == 27) {
			ft_getch();
			if ((car = ft_getch()) == 'A')
				dprintf(1, "UP");
			else if (car == 'B')
				dprintf(1, "DOWN");
			else if (car == 'C')
				dprintf(1, "RIGHT");
			else if (car == 'D')
				dprintf(1, "LEFT");
			}
		}

	char buf[1024];
	  char buf2[30];
	  char *ap = buf2;
	  char *clearstr, *cm, *standstr, *stendstr;

	  tgetent(buf, getenv("TERM"));

	  clearstr = tgetstr("cl", &ap);
	  cm = tgetstr("cr", &ap);
	  char *sc = tgetstr("sc", &ap);
	  char *rc = tgetstr("cr", &ap);
	  char *us = tgetstr("us", &ap);
	  char *ue = tgetstr("ue", &ap);
	  int	li = tgetnum("li");
	  int	co = tgetnum("co");
	  standstr = tgetstr("so", &ap);
	  stendstr = tgetstr("se", &ap);

	tputs(sc, 1, &ft_putchar);
	tputs(standstr, 1, &ft_putchar);
	tputs("Hello, ", 1, &ft_putchar);
	tputs("world\n lalalala", 1, &ft_putchar);
	tputs(stendstr, 1, &ft_putchar);
	tputs(tgoto(rc, 0, 0), 1, &ft_putchar);
	tputs("LALALALALAL\n", 1 , &ft_putchar);
	return (0);
}

