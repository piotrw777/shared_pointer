#include <iostream>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <time.h>
#include <thread>

using namespace std;

struct Random_Person {
};

class Person {

private:
    string name;
    string surname;
    int age;

    static constexpr int M = 10;
    static const array<string, M> rand_names;
    static const array<string, M> rand_surnames;
    static const int min_age = 10;
    static const int max_age = 99;

public:
    string get_name() {return name;}
    string get_surname() {return surname;}
	int get_age() {return age;}

	Person(string name,string surname,int age): name(name), surname(surname), age(age)  {};
    Person() = default;
    Person(Random_Person);

    friend ostream& operator<<(ostream& s,const Person & p);
    friend Person get_random();
};

const array<string, Person::M> Person::rand_names = {{"Adam","Bartek", "Cezary", "Darek", "Ewaryst", "Franek", "Grzegorz", "Henryk", "Idzi", "Janusz"}};
const array<string, Person::M> Person::rand_surnames = {{"Kowalski", "Nowak", "Malinowski", "Wyszkowski", "Budzinski", "Lewandowski", "Zajac", "Wilk", "Wielki", "Czaj"}};

Person get_random() {

    static const int min_age = 10;
    static const int max_age = 99;

    int k = rand() % Person::M;
    int l = rand() % Person::M;
    int w = rand() % (max_age-min_age+1) + min_age;

    return Person(Person::rand_names[k], Person::rand_surnames[l], w);
}
ostream& operator<<(ostream& s,const Person & p) {
    s <<p.name << " " << p.surname << " lat " << p.age << "\n";
    return s;
}
Person::Person(Random_Person) {
    //cout << "Dziala konstruktor losowy\n";
    int k = rand() % M;
    int l = rand() % M;
    int w = rand() % (max_age-min_age+1) + min_age;
    name = rand_names[k];
    surname = rand_surnames[l];
    age = w;
}
template<typename T>
void print(T t) {
    for(int k = 0; k < t.size(); k++) {
        cout << k + 1 << ". " << t[k];
    }
}

template<typename T>
void print(vector<shared_ptr<T> >  vec, size_t N = 0) {

     size_t ile = (N == 0 ? vec.size() : min(N, vec.size()));
     for(int k = 0; k < ile; k++) {
        cout << k + 1 << ". " << *(vec[k]);
    }
}

typedef vector<shared_ptr<Person> > vecPer;
typedef  int (Person::*Per_Mem_Fun_int)();
typedef  string (Person::*Per_Mem_Fun_str)();
    //Per_Mem_Fun_int wsk_do_get_age = Person::get_age;
    //Per_Mem_Fun_str wsk_do_get_name = Person::get_name;
    //Per_Mem_Fun_str wsk_do_get_surname = Person::get_surname;

template<typename T, typename F >
void person_sort(vector<shared_ptr<T> > &vec, F f) {
    auto compare = [f](shared_ptr<T> p1, shared_ptr<T> p2) {return ((*p1).*f)() < ((*p2).*f)();};
    sort(vec.begin(), vec.end(), compare);
}

//**************************************************************************
int main()
{
    const int ile_osob = 1000;

    srand(time(0));

    vecPer vec_all(ile_osob);
    vecPer vec_sort_name(ile_osob);
    vecPer vec_sort_surname(ile_osob);
    vecPer vec_sort_age(ile_osob);

    vecPer & vsn = vec_sort_name;
    vecPer & vss = vec_sort_surname;
    vecPer & vsa = vec_sort_age;

    for(int k = 0; k < ile_osob; k++) {
        vec_all[k] = make_shared<Person>(Random_Person{});
    }

    vsa = vss = vsn = vec_all;

    cout << "Use count = " << (vec_all[0]).use_count() << endl;

    cout << "Wylosowane osoby: VEC_ALL:\n";
    print(vec_all, 30);

    auto sort_name = [] (vecPer & vec) {cout << "Watek 1" << endl;person_sort(vec,&Person::get_name);};
    auto sort_surname = [] (vecPer & vec) {cout << "Watek 2" << endl;person_sort(vec,&Person::get_surname);};
    auto sort_age = [] (vecPer & vec) {cout << "Watek 3" << endl;person_sort(vec,&Person::get_age);};

    const int thr_number = 3;
    thread thr[thr_number];
    thr[0] = thread(sort_name, ref(vsn));
    thr[1] = thread(sort_surname, ref(vss));
    thr[2] = thread(sort_age, ref(vsa));

    for(int k = 0; k < thr_number; k++) {
        thr[k].join();
    }

    cout << "\nSortowanie po imieniu...\n";
    print(vsn, 10);

    cout << "\nSortowanie po nazwisku...\n";
    print(vss, 10);

    cout << "\nSortowanie po wieku...\n";
    print(vsa, 10);

}
