#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct UserSession {
  char username[32];
  void (*print_privileges)();
};

void standard_privs() { printf("Privilege Level: Standard User\n"); }

void eleveted_privs() { printf("Privilege Level: Root Administrator\n"); }

int main(int argc, char *argv[]) {
  struct UserSession *session = malloc(sizeof(struct UserSession));
  session->print_privileges = standard_privs;

  strcpy(session->username, argv[1]);

  session->print_privileges();

  free(session);
  return 0;
}
