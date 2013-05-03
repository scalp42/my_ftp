/*
** client.h for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#ifndef __FTP_CLIENT__
#define __FTP_CLIENT__

#include	<sys/socket.h>

#define	USER	"USER %s\n"
#define	PASS	"PASS %s\n"
#define	CD	"CWD %s\n"
#define __UNUSED__ __attribute__ ((unused))

int		gl_s;

typedef struct	option_s
{
  char		*cmd;
  int		len;
  void		(*f)();
}		option_t;

typedef	struct	client_ftp_s
{
  int		s;
  int		s_data;
  int		port;
  char		*pwd;
  char		*ipaddr;
  int		port1;
  int		port2;
  int		to_die;
}		client_ftp_t;

char		*get_next_line(int fd);
void		init_userpass(client_ftp_t *client_ftp);
void		check_line(client_ftp_t *client_ftp, char *line, int first);
void		clean_buff(char *buff, int nb_read);
void		init_client_connection(client_ftp_t *client_ftp, char **av);
void		check_line(client_ftp_t *client_ftp, char *line, int first);
void		check_option(client_ftp_t *client_ftp, char *line);
void		init_pwd(client_ftp_t *client_ftp);
void		open_data_connection(client_ftp_t *client_ftp);
void		receiv_ls(client_ftp_t *client_ftp);
void		retr_opt(client_ftp_t *client_ftp, char *line);
void		open_new_data_connection(client_ftp_t *client_ftp);
void		stor_opt(client_ftp_t *client_ftp, char *cmd);
ssize_t		xsend(int s, const void *msg, size_t len, int flags);
ssize_t		xrecv(int s, void *buf, size_t len, int flags);
int		xread(int id_open, void *buffer, int nbytes);

#ifdef sun4
char		*strdup(const char *s1);
void		bzero(void *s, size_t n);
#endif

#endif
