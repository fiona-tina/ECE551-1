#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

//construct a linked list to store all the information of children processes
struct node {
  int pid;
  char * exeName;
  char pstates[15];
  int flag;
  struct node * next;
};
typedef struct node node;

void insertPid(pid_t childpid, char * name, node *& head) {
  node * p = new node;
  node * cur = head;
  p->flag = 0;
  p->pid = childpid;
  p->exeName = name;
  memcpy(p->pstates, "running", strlen("running") + 1);
  p->next = NULL;

  if (head->next == NULL) {  //empty list
    head->next = p;
  }

  else {  //find the end and link the new node
    while (cur->next != NULL)
      cur = cur->next;
    cur->next = p;
  }
}
node * searchPid(char * ProcessID, node *& head) {
  int PID = atoi(ProcessID);
  node * cur = head;
  while (cur != NULL && cur->pid != PID) {
    cur = cur->next;
  }

  if (cur != NULL) {
    return cur;  //target PID exists in the linked list
  }
  else {
    printf("Please check the pid\n");
    return NULL;  //PID is not found in the linked list
  }
}
void checkStatus(node *& head) {
  if (head->next != NULL) {
    node * temp = head->next;
    while (temp != NULL) {
      if ((waitpid(temp->pid, NULL, WNOHANG)) && (!temp->flag) &&
          strcmp(temp->pstates, "terminated")) {
        temp->flag = 1;
        printf("%d completed\n", temp->pid);
        memcpy(temp->pstates, "completed", strlen("completed"));
      }
      temp = temp->next;
    }
  }
}

void bgkill(node *& cur) {
  kill(cur->pid, SIGTERM);
  memcpy(cur->pstates, "terminated", strlen("terminated"));
}

void bgstop(node *& cur) {
  kill(cur->pid, SIGSTOP);
  memcpy(cur->pstates, "stopped", strlen("stopped"));
}

void bgrestart(node *& cur) {
  kill(cur->pid, SIGCONT);
  memcpy(cur->pstates, "running", strlen("running"));
}

//-------------------------------------------------------------------------------------------------
int main() {
  pid_t pid = 0;
  node * head = new node;
  head->pid = 0;
  head->flag = 0;
  head->exeName = NULL;
  memcpy(head->pstates, "aaa", strlen("aaa"));
  head->next = NULL;

  while (1) {
    char * input = NULL;
    char prompt[] = "BP >";
    char * cmd = NULL;
    char * name = NULL;
    char * argv[10];
    for (int i = 0; i < 10; i++) {
      argv[i] = NULL;
    }
    char * ProcessID = NULL;

    //user input prompt
    input = readline(prompt);

    //check whether any children process completed
    checkStatus(head);

    //split the input string
    cmd = strtok(input, " ");
    //----------------------------------------------------------------------------------------------
    if (!strcmp(cmd, "bg")) {
      for (int i = 0; i < 10; ++i) {
        argv[i] = strtok(NULL, " ");
      }
      name = argv[0];

      pid = fork();

      //child process
      if (pid == 0) {
        if (execvp(name, argv) < 0 || (!name)) {
          printf("error\n");
          exit(1);
        }
      }
      //parent process, store the information of child in the linked list
      else {
        insertPid(pid, name, head);
      }
    }

    //----------------------------------------------------------------------------------------------
    else if (!strcmp(cmd, "bgkill")) {
      ProcessID = strtok(NULL, " ");
      node * cur = searchPid(ProcessID, head);
      if (cur != NULL) {
        bgkill(cur);
        printf("%d killed\n", cur->pid);
      }
    }

    //----------------------------------------------------------------------------------------------
    else if (!strcmp(cmd, "bglist")) {
      int check = 0;
      //empty list
      if (head->next == NULL) {
        printf("No process\n");
      }
      //non-empty list
      else {
        node * temp = head->next;
        while (temp != NULL) {
          if (!strcmp(temp->pstates, "running") || !strcmp(temp->pstates, "stopped")) {
            printf("%d: %s\n", temp->pid, temp->exeName);
            check = 1;
          }
          temp = temp->next;
        }
        if (check == 0)
          printf("All processes are terminated\n");
      }
    }

    //----------------------------------------------------------------------------------------------
    else if (!strcmp(cmd, "bgstate")) {
      ProcessID = strtok(NULL, " ");
      node * cur = searchPid(ProcessID, head);
      if (cur != NULL)
        printf("%d: %s %s\n", cur->pid, cur->exeName, cur->pstates);
    }

    //----------------------------------------------------------------------------------------------
    else if (!strcmp(cmd, "bgstop")) {
      ProcessID = strtok(NULL, " ");
      node * cur = searchPid(ProcessID, head);

      if (cur) {  //target pid exists in the list
        if (!strcmp(cur->pstates, "running")) {
          bgstop(cur);
          printf("%d stopped\n", cur->pid);
        }
        else
          printf("Process is not running, thus cannot be stopped\n");
      }
    }

    //----------------------------------------------------------------------------------------------
    else if (!strcmp(cmd, "bgrestart")) {
      ProcessID = strtok(NULL, " ");
      node * cur = searchPid(ProcessID, head);

      if (cur) {  //target pid exists in the list
        if (!strcmp(cur->pstates, "stopped")) {
          bgrestart(cur);
          printf("%d restarted\n", cur->pid);
        }
        else
          printf("Process is not stopped, thus cannot be restarted\n");
      }
    }

    //----------------------------------------------------------------------------------------------
    else if (!strcmp(cmd, "exit")) {
      if (head->next != NULL) {
        node * temp = head->next;
        //kill all non-terminated processes
        while (temp != NULL) {
          if (!strcmp(temp->pstates, "running") || !strcmp(temp->pstates, "stopped")) {
            bgkill(temp);
            printf("%d killed\n", temp->pid);
          }
          temp = temp->next;
        }
      }
      break;
    }

    else
      printf("Do not support this command, please input again\n");

    checkStatus(head);
  }
  return 0;
}
