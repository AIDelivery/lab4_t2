#include <pthread.h>
#include <string.h>

#include <iostream>
using namespace std;

void* div_by_thread(void* p) {

}

int main(int argv, char* argc[]) {
  pthread_t thread1, thread2;
  FILE *fi, *fo1, *fo2;
  pthread_attr_t attr;

  string* cur_str = new string();

  fi = fopen("INFO.txt", "r");
  // fo1 = fopen("LOG1.txt", "w");
  // fo2 = fopen("LOG2.txt", "w");

  if(!fi || !fo1 || !fo2) {
    cout << "ERROR";
    return 0;
  }

  pthread_attr_init(&attr);
  pthread_create(&thread1, &attr, div_by_thread, (void*) cur_str);

  char c;
  while((c = fgetc(fi)) != EOF)
    cout << c;
}
