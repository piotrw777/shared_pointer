#include <iostream>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <time.h>

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
void print(vector<shared_ptr<T> >  vec) {
     for(int k = 0; k < vec.size(); k++) {
        cout << k + 1 << ". " << *(vec[k]);
    }
}

typedef vector<shared_ptr<Person> > vecPer;

//**************************************************************************
int main()
{
    const int ile_osob = 10;

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

    vsn = vss = vsa = vec_all;

    cout << "Use count = " << (vec_all[0]).use_count() << endl;

    cout << "VEC_ALL:\n";
    print(vec_all);
    cout << "Sortowanie po wieku...\n";

    auto compare_age = [](shared_ptr<Person> p1, shared_ptr<Person> p2) {return p1->get_age() <= p2->get_age();};
    sort(vsa.begin(), vsa.end(), compare_age);

    cout << "Po sortowaniu: \n";
    print(vsa);
    cout << "VEC_ALL:\n";
    print(vec_all);




}

