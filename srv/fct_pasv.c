/*
** fct_pasv.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include		<arpa/inet.h>
#include		<netdb.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<string.h>
#include		<sys/socket.h>
#include		<time.h>
#include		<unistd.h>
#include		"ftp.h"

char			*obtain_ipaddr()
{
  char			s[128];
  struct hostent	*host;
  struct in_addr	**adr;
  char			*ipaddr;

  ipaddr = NULL;
  if (!gethostname(s, 256))
    if ((host = gethostbyname(s)) != NULL)
      for (adr = (struct in_addr **)host->h_addr_list; *adr; adr++)
	ipaddr = strdup(inet_ntoa(**adr));
  return (ipaddr);
}

void			fct_pasv(char __UNUSED__ *cmd, client_ftp_t *client_ftp, ftp_t __UNUSED__ *ftp)
{
  int			client_sin_len;
  struct sockaddr_in    client_sin;
  char			*ipaddr;

  ipaddr = obtain_ipaddr();
  while (1)
    {
      srand(time(0));
      ftp->port1 = rand() % 255;
      ftp->port2 = rand() % 255;
      if (open_new_socket(client_ftp, ftp) == 1)
	break;
    }
  ipaddr = seek_addr(ipaddr, ftp->port1, ftp->port2);
  ipaddr = create_real_mess(ipaddr);
  client_sin_len = sizeof(client_sin);
  send(client_ftp->cs, ipaddr, strlen(ipaddr), 0);
#ifndef alpha
  client_ftp->cs_data = accept(ftp->s_data, (struct sockaddr *)&client_sin, (socklen_t *) &client_sin_len);
#else
  client_ftp->cs_data = accept(ftp->s_data, (struct sockaddr *)&client_sin, &client_sin_len);
#endif
  return;
}
