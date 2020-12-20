#include "LiteSH.hpp"

int NetWorkServer ()
{
  struct sockaddr_in server, client;
  int sock = socket (AF_INET, SOCK_STREAM, 0); // создание сокета

  if (sock < 0)
  {
    perror ("socket");
    exit (1);
  }
//Допускает повторное использование локального адреса
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (struct sockaddr*)&server, sizeof(server)) < 0)
    perror("setsockopt(SO_REUSEADDR) failed");

  // структура для сервера
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
  server.sin_port = htons (2019); // порт сервера

  if (bind (sock, (struct sockaddr*)&server, sizeof(server)) < 0) // связка с сокетом
  {
    perror ("bind");
    exit (2);
  }

  listen (sock, 5); // размер очереди

  while (1)
  {
    int newsock, size;
    socklen_t clnlen = sizeof(client);
    char buf[255] = "";

    newsock = accept (sock, (struct sockaddr*)&client, &clnlen); // появление нового клиента
    if (newsock < 0)
    {
      perror ("accept");
      exit (3);
    }
    cout << "New client: " << inet_ntoa (client.sin_addr) << endl;

    while ((size = recv (newsock, buf, sizeof(buf), 0)) != 0) // пока получаем от клиента
    {
      if (strcmp(buf, "SpawnProcess") == 0) {
        strcpy(buf, "1");
        send(newsock, buf, sizeof(buf), 0); // отправляем эхо
      } else if (strcmp(buf, "BackGroundmodeProcess") == 0) {
        strcpy(buf, "2");
        send(newsock, buf, sizeof(buf), 0);
      } else if (strcmp(buf, "SendSignal") == 0) {
        strcpy(buf, "3");
        send(newsock, buf, sizeof(buf), 0);
      } else if (strcmp(buf, "Exit") == 0) {
        strcpy(buf, "4");
        send(newsock, buf, sizeof(buf), 0);
      } else {
        strcpy(buf, "Unknown command");
        send(newsock, buf, sizeof(buf), 0);
      }
    }
  close (newsock);
  }

  close (sock);

  return 0;
}

int NetWorkClient (char *command)
{
  // структура для сокета
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons (2019);
  server.sin_addr.s_addr = inet_addr ("127.0.0.1");

  int sock = socket (AF_INET, SOCK_STREAM, 0); // создаем сокет

  if (sock < 0)
  {
    perror ("socket");
    exit (1);
  }

  if (connect (sock, (struct sockaddr*)&server, sizeof(server)) < 0) // соединяемся с сервером
  {
    perror ("connect");
    exit (2);
  }

  // отправка сообщения
  char buf[255] = "";
  send (sock, command, sizeof(buf), 0);
  recv (sock, buf, sizeof(buf), 0);
  cout << "Received from server: " << buf << endl;

  close (sock);

  int selection = atoll (buf);
  return selection;
}

pid_t net_proc()
{
  pid_t pid;
  int v;

  switch (pid = fork()) {
    case -1:
      perror("fork");
      return -1;
    case 0:
      cout << "PIDserver: " << getpid () << endl;
      NetWorkServer();

  }
  wait(&v);
  return pid;
}

int SpawnProcess (char *name)
{
  pid_t pid;
  int rv;
  char *arg[] = { name, 0 };
  switch (pid = fork ())
  {
    case -1:
      perror ("fork"); /* произошла ошибка */
      exit (1); /*выход из родительского процесса*/
    case 0:
      cout << "PID1: " << getpid () << endl;
      cout << "PPID1: " << getppid () << endl;
      execvp (arg[0], arg);
    default:
      cout << "PID2: " << getpid () << endl;
      cout << "PPID2: " << getppid () << endl;
      wait (&rv);
    }

    return 0;
}

int BackGroundmodeProcess (char *name)
{
  pid_t pid;
  char *arg[] = { name, 0 };

switch (pid = fork()) //создаем дочерний процесс
  {
  case -1:
    perror ("fork"); /* произошла ошибка */
    exit (1); /*выход из родительского процесса*/
  case 0:
                          //создаём новый сеанс, чтобы не зависеть от родителя
    if (setsid () < 0)  // (генерируем уникальный индекс процесса)
      exit (1);

    cout << "PID1: " << getpid () << endl;
    cout << "PPID1: " << getppid () << endl;

    if (chdir ("/") < 0) // переходим в корень диска
      exit (1);
    close (STDIN_FILENO); //закрываем доступ к стандартным потокам ввода-вывода
    close (STDOUT_FILENO);
    close (STDERR_FILENO);
    execv (arg[0], arg);
  default:
    cout << "PID2: " << getpid () << endl;
    cout << "PPID2: " << getppid () << endl;
  }

  return 0;
}

void signal_handler( int signum ) {
   cout << "Interrupt signal is (" << signum << ").\n";
   signal (SIGINT, signal_handler);
}

int SendSignal (pid_t pid, int signum)
{

  if (kill (pid, signum) == -1)
    return -1;

  return 0;
}
