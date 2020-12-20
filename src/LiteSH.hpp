#ifndef LITESH_H
#define LITESH_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <dlfcn.h>
#include <unistd.h>

using namespace std;

int NetWorkServer ();
int NetWorkClient (char *command);
pid_t net_proc ();
int SpawnProcess (char *name);
int BackGroundmodeProcess (char *name);
void signal_handler (int signum);
int SignalProcessing ();
int SendSignal (pid_t pid, int signum);


#endif
