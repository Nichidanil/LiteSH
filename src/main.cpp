#include "LiteSH.hpp"

int main(int argc, char *argv[])
{
  pid_t server_pid;

  char *error;
  void *handle = dlopen ("/home/danil/3course/OC/lab6/lib/libm.so", RTLD_LAZY);
  if (!handle) {
    fputs (dlerror (), stderr);
    exit(EXIT_FAILURE);
  }

  typedef void (*_display)();
  _display display = (_display)dlsym(handle, "display");


  if ((error = dlerror ()) != NULL){
        fprintf (stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

  if (argc > 1)
  {
    if ((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h")) == 0)
    {
      cout << endl;
      cout << " Авторы: Ничипарук Д.В." << endl;
      cout << " Работа c процессами в OC Linux." << endl;
      cout << "----------------------------" << endl;
      cout << "Доступные команды:" << endl;
      cout << "1. SpawnProcess - create process" << endl;
      cout << "2. BackGroundmodeProcess - put the started process in the background" << endl;
      cout << "3. SendSignal - kill signal" << endl;
      cout << "4. Exit - exit program" << endl;
      cout << endl;
    }else if (strcmp(argv[1], "-server") == 0)
   {
      server_pid = net_proc ();
     //SendSignal(server_pid, SIGKILL);
   } else if (strcmp(argv[1], "-client") == 0)
   {
     display ();

     bool isExit = false;

     while (isExit != true)
     {

       int selection;
       char *command = new char[100];

       cout << endl << endl;
       cout << "Command to server: ";
       cin >> command;
       cout << endl << endl;

       cout << "--------------------------" << endl;
       selection = NetWorkClient (command);
       cout << "--------------------------" << endl << endl;

       switch (selection) {
         case 1: {

           char *ProcName = new char[100];
           cout << "Process name: ";
           cin >> ProcName;

           if (SpawnProcess (ProcName) == 1)
           cout << "Failed to create process" << endl;

           delete [] ProcName;
           break;
         }
         case 2: {

           char *ProcName = new char[100];
           cout << "Process name: ";
           cin >> ProcName;

           if (BackGroundmodeProcess (ProcName) == 1)
           cout << "Failed to create BackGroundmodeProcess" << endl;

           delete [] ProcName;
           break;
         }
         case 3: {

           pid_t pid = getpid ();

           if (SendSignal (pid, SIGKILL) == 1)
           cout << "Failed to kill signal" << endl;

           break;
         }
         case 4:
         isExit = true;
         SendSignal (server_pid, SIGKILL);  // завершаем работу сервера
         break;
       }
     }
   } else
    cout << "Invalid argument" << endl;
 }

  dlclose (handle);

  return 0;
}
