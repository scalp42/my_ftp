/*
** stick_addr.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<string.h>
#include	"ftp.h"

char		*stick_addr(char *ipaddr, char *port1, char *port2, int len)
{
  ipaddr = strcat(ipaddr, ",");
  ipaddr = strcat(ipaddr, port1);
  ipaddr = strcat(ipaddr, ",");
  ipaddr = strcat(ipaddr, port2);
  ipaddr[len - 1] = '\0';
  return (ipaddr);
}
