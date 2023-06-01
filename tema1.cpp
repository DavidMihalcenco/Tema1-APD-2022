#include "helper.hpp"

void *f(void *arg) {
  ifstream myfile;
  string line;
  string line1;
  thread_param threads = *(thread_param*)arg;

  if (threads.tip_thread == 0){
    while(!threads.file->eof()){
        pthread_mutex_lock(threads.mutex);
        getline(*threads.file,line);
        if(line.empty()){
          pthread_mutex_unlock(threads.mutex);
          break;
        }
        pthread_mutex_unlock(threads.mutex);
        ifstream myfile1(line);
        if (myfile1.is_open()){
          getline(myfile1,line1);
          while ( getline (myfile1,line1) ){ 

            int nr = stoi(line1);
            int nrreduceri = threads.nreduceri + 1;

            for(int i = 2 ; i <= nrreduceri ; i++){
              double nrcalc = getNPower(i,nr);

              if(pow(round(nrcalc),i) == nr){ 
                threads.numbers.at(i-2).push_back(nr);
              }

            }
          }
          myfile1.close();
        }
      line.assign("");
    }
    (threads.all_list)[threads.ids] = threads.numbers;
  }

  pthread_barrier_wait(threads.barrier);

  if (threads.tip_thread == 1){
    vector<int> aux;
    int indlist = threads.ids - threads.nrmapperi;

    for(int i = 0; i < threads.nrmapperi; i++){ 
      for(int k = 0; k < threads.all_list[i].at(indlist).size(); k++){
        threads.numbers[indlist].push_back(threads.all_list[i].at(indlist).at(k));

      }
      for(int k = 0; k < threads.numbers[indlist].size(); k++){
        if(find(aux.begin(), aux.end(), threads.numbers[indlist].at(k)) == aux.end()){
          aux.push_back(threads.numbers[indlist].at(k));
        }
      }
    }
    ofstream MyFile("out" + to_string(indlist+2) + ".txt");
    MyFile << aux.size();
    MyFile.close();
  }

  pthread_exit(NULL);
}

int main(int argc, char** argv) {

  pthread_mutex_t mutex;
  pthread_barrier_t barrier;

  int nr_mapperi = stoi(argv[1]);
  int nr_reduceri = stoi(argv[2]);
  int nr_thr = nr_mapperi + nr_reduceri;

  thread_param *thread = (thread_param*)calloc(nr_thr,sizeof(thread_param));

  string line; 
  ifstream myfile;
  myfile.open(argv[3]);
  getline (myfile,line);
  int nr_files = stoi(line);

  pthread_t threads[nr_thr];
  int error;
  long id;
  void *status;
  long ids[nr_thr];
  vector<vector<int>> vec;
  vector<int> v1;

  for(int i = 0 ; i < nr_reduceri; i++){
    vec.push_back(v1);
  }

  pthread_mutex_init(&mutex, NULL);
  pthread_barrier_init(&barrier, NULL, nr_thr);
  vector<vector<int>>* all_lists = (vector<vector<int>>*)calloc(nr_mapperi,sizeof(vector<vector<int>>));

  for (id = 0; id < nr_thr; id++) {
    thread[id].ids = id;
    thread[id].mutex = &mutex;
    thread[id].barrier = &barrier;
    thread[id].file = &myfile;
    thread[id].nrfiles = nr_files;
    thread[id].nreduceri = nr_reduceri;
    thread[id].nrmapperi = nr_mapperi;
    thread[id].numbers = vec;
    thread[id].all_list = all_lists;

    if(id < nr_mapperi){
      thread[id].tip_thread = 0;
    } else {
      thread[id].tip_thread = 1;
    }

    error = pthread_create(&threads[id], NULL, f, thread + id);

    if (error) {
        printf("Eroare la crearea thread-ului %ld\n", id);
        exit(-1);
    }

  }

  for (id = 0; id < nr_thr; id++) {
    error = pthread_join(threads[id], &status);

    if (error) {
        printf("Eroare la asteptarea thread-ului %ld\n", id);
        exit(-1);
    }

  }

  pthread_mutex_destroy(&mutex);
  pthread_barrier_destroy(&barrier);
  myfile.close();
}


