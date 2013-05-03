/*
** client.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<signal.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"client.h"

void	to_quit()
{
  xsend(gl_s, "QUIT\n", 5, 0);
  printf("Ftp exited\n");
  close(gl_s);
  exit(1);
}

/* struct hostent        *h; */
/*   struct in_addr        addr; */

/* if (!(h = gethostbyname(argv[1]))) */
/*     { */
/*       my_putstr("host not found\n"); */
/*       exit(1); */
/*     } */
/*   bcopy(h->h_addr, &addr, sizeof(addr)); */
/*     inet_ntoa(addr) */

int	main(int ac, char **av)
{
  char			*line;
  char			buffer[1024];
  client_ftp_t		client_ftp;
  int			i;

  if (ac == 3)
    init_client_connection(&client_ftp, av);
  else
    return (0);
  client_ftp.to_die = 0;
  init_userpass(&client_ftp);
  bzero(buffer, 1024);
  i = xrecv(client_ftp.s, buffer, 1023, 0);
  clean_buff(buffer, i);
  if (strncmp(buffer, "230", 3) !=  0)
    {
      close(client_ftp.s);
      exit(1);
    }
  printf("%s\n", buffer);
  init_pwd(&client_ftp);
  signal(SIGINT, to_quit);
  write(1, "ftp-client> ", 12);
  while ((line = get_next_line(0)))
    {
      check_option(&client_ftp, line);
      free(line);
      if (client_ftp.to_die == 1)
	break;
      write(1, "ftp-client> ", 12);
    }
  close(client_ftp.s);
  return (0);
}
