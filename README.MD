# APD Tema 1: Map-Reduce
## David Mihalcenco 331CB

### Implementare Tema
	**Structura unui thred**
    int  ids; - Id-ul thradului
	int  nrfiles; - Numarul de fisiere
	int  nreduceri; - Numarul de reduceri
	int  nrmapperi; - Numarul de mapperi
	int  tip_thread; - Tipul thradului
	pthread_mutex_t *mutex; - Mutexul 
	pthread_barrier_t *barrier; - Bariera
	ifstream *file; - Fisierul din care citesc
	vector<vector<int>> numbers; - Vec de vec cu numerele pentru puteri
	vector<vector<int>>* all_list; - Toate numerele din fisiere
**Main**
	- Primesc numarul de mapperi si numarul de reduceri, care ii salvez in variabilele corespunzatoare, si mai jos le adaug in structura fiecarui thread. 
	- Aflu numarul total de threduri. 
	- Din fisier citesc numarul de fisiere, la fel il salvez in structura. 
	- Pentru fiecare thread creez vectori goi, pentru a salva mai tarziu numerele in ei.
	- Creez bariera si mutex, care le trimit in structura.
	- Si all_lists care este de tip vector<vector<int>>*, pentru a salva numerele formatate de mapperi corespunzator.
	- Creez thredurile.
	- Si le dau join la fiecare.
	- La sfarsit distrug bariera si mutexul.
**Functia f**
	Mapper
	- Verific tipul threadului daca este 0 atunci e mapper daca 1 e reducer.
	- Daca e de tip mapper incep sa citesc fisierele din fisierul principal, pana dau de EndOfFile.
	- Atunci cand citesc denumirea unui fisier, il deschid, si citesc cate o linie din fisier, cu ajutorul functie getNPower, aflu numarul ridicat la puterea i sa dea numarul citit din fisier, in for verific daca numarul dat de functia geNPower este intreg. Daca da atunci il bag in vec de vec pe pozita i-2 adica daca exista un nr la puterea 2 sa dea 81 atunci il bag in vectorul 0.
	- Thredurile vor lua fisiere atat timp cat ele mai sunt adica alt thred nu lucreaza cu ele. Asta se datoreaza folosirii mutexului la citirea fisierului.
	- Dupa ce am verificat pentru fiecare numar, adaug rezultatul adica vec de vec in all_list  la pozitia id-ului thredului pentru ca mai departe sa am salvate toate formatarile mapperilor.
	Reducer
	- Dupa ce s-au executat toate operatiile de tip map, asta se datoreaza barierei care nu da voie thredurilor sa treaca mai departe, incep operatiile de reduce.
	- Extrag din all_list unde se afla listele tuturor mapperilor,listele de puteri, si le bag threads.numbers, de ex din fiecare lista a mapperilor extrag numerele care sunt puterea lui 2 si le bag intr-o singura lista. Dupa ce am facut asta pentru fiecare putere, scriu in fisierul de output marimea vectorului creeat la moment.
**getNPower**
	- Folosesc o cautare binara, pentru a afla un numar care ridicat la puterea power imi da numarul pe care il verific.