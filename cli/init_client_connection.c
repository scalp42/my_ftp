/*
** init_client_connection.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<sys/types.h>
#include	<netdb.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<stdlib.h>
#include	<strings.h>
#include	<stdio.h>
#include	"client.h"

void		init_client_connection(client_ftp_t *client_ftp, char **av)
{
  struct sockaddr_in	sin;
  struct hostent	*h;
  struct in_addr	addr;

  if ((client_ftp->s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
      printf("Problem in socket open\n");
      exit(1);
    }
  gl_s = client_ftp->s;
  client_ftp->port = atoi(av[2]);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(client_ftp->port);
  if (!(h = gethostbyname(av[1])))
    {
      puts("host not found\n");
      exit(1);
    }
  bcopy(h->h_addr, &addr, sizeof(addr));
  sin.sin_addr.s_addr = inet_addr(inet_ntoa(addr));
  connect(client_ftp->s, (struct sockaddr *)&sin, sizeof (struct sockaddr_in));
  printf("Connected to %s %d\n", inet_ntoa(sin.sin_addr), client_ftp->port);
}
