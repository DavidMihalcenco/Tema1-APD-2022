#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

struct thread_param{
  int ids;
  int nrfiles;
  int nreduceri;
  int nrmapperi;
  int tip_thread;
  pthread_mutex_t *mutex;
  pthread_barrier_t *barrier;
  ifstream *file;
  vector<vector<int>> numbers;
  vector<vector<int>>* all_list;
};

double getNPower(int n, int m);