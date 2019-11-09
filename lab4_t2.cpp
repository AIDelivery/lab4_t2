#include <pthread.h>
#include <string.h>

#include <fstream>
#include <iostream>
using namespace std;

ifstream if1;
ofstream of1, of2;

void* string_to2files(void* v) {
  string line = (string) (char*) v;
  bool is_even = line[0] == 'e' ? true : false;

  line = line.substr(1, line.length());

  if(is_even) {
    cout << "[EVEN THREAD] " << line << endl;
    of1 << line << endl;
  }
  else {
    cout << "[ODD_ THREAD] " << line << endl;
    of2 << line << endl;
  }

  pthread_exit(EXIT_SUCCESS);
}


int main(int argv, char* argc[]) {
  pthread_t thread1, thread2;
  pthread_attr_t attr;
  string line, *l_p = &line;

  if1.open("./INFO.txt");
  of1.open("./LOG1.txt");
  of2.open("./LOG2.txt");

  if(if1.is_open() && of1.is_open() && of1.is_open())
    cout << "File openning... Success" << endl;
  else {
      cout << "ERROR while opening files" << endl;
      if1.close();
      of1.close();
      of2.close();
      return 1;
  }

  pthread_attr_init(&attr);

  for(int i = 0; getline(if1, line); i++) {
    if(i%2 == 0) {
      line = 'e' + line;
      pthread_create(&thread1, &attr, string_to2files, (void*) line.c_str());
      pthread_join(thread1, NULL);
    }
    else {
      line = 'o' + line;
      pthread_create(&thread2, &attr, string_to2files, (void*) line.c_str());
      pthread_join(thread2, NULL);
    }
  }

  if1.close();
  of1.close();
  of2.close();
}
