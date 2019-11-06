#include <pthread.h>
#include <string.h>

#include <fstream>
#include <iostream>
using namespace std;

ifstream if1;
ofstream of1, of2;

void* even_string(void* v) {
  // cout << "[EVEN THREAD] " << (char*) v << endl;
  cout << (char*) v << endl;
  of1 << (char*) v << endl;

  pthread_exit(EXIT_SUCCESS);
}

void* odd_string(void* v) {
  // cout << "[ODD THREAD] " << (char*) v << endl;
  cout << (char*) v << endl;
  of2 << (char*) v << endl;

  pthread_exit(EXIT_SUCCESS);
}


int main(int argv, char* argc[]) {
  pthread_t thread1, thread2;
  pthread_attr_t attr;
  string line, *l_p = &line;

  if1.open("/home/dan/Desktop/lab5/INFO.txt");
  of1.open("/home/dan/Desktop/lab5/LOG1.txt");
  of2.open("/home/dan/Desktop/lab5/LOG2.txt");

  if(if1.is_open() && of1.is_open() && of1.is_open())
    cout << "File openning... Success" << endl;
  else {
      cout << "ERROR" << endl;
      if1.close();
      of1.close();
      of2.close();
      return 0;
  }

  pthread_attr_init(&attr);

  for(int i = 0; getline(if1, line); i++) {
    if(i%2 == 0) {
        pthread_create(&thread1, &attr, even_string, (void*) line.c_str());
        pthread_join(thread1, NULL);
    }
    else {
      pthread_create(&thread2, &attr, odd_string, (void*) line.c_str());
      pthread_join(thread2, NULL);
    }
  }

  if1.close();
  of1.close();
  of2.close();
}
