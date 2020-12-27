/*
Korzystamy z klasy Person (name/surname/age).

1) Tworzymy wektor (vec_all), w którym umieœcimy 1000 losowo wygenerowanych osób.

2) Tworzymy 3 wektory, do których kopiujemy osoby z wektora vec_all.
vec_sort_surname
vec_sort_name
vec_sort_age

3) Sortujemy osoby w wektorach vec_sort_X.

Sortowanie ka¿dego wektora ma siê odbyæ w osobnych w¹tkach.
(czyli potrzebne s¹ nam 3 w¹tki).

4) Po zakoñczeniu sortowania, wypisujemy po 10 osób z ka¿dego wektora w celu sprawdzenia, czy dane s¹ posortowane poprawnie.

Uwaga:
- w celu nie duplikowania danych, osoby w wektorach maj¹ byc przetrzymywane przy pomocy std::shared_ptr
- ref_count powinien wynosiæ 4 (poniewa¿ dane s¹ wspó³dzielone w 4 wektorach).


*/
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <time.h>

#define M 10
using namespace std;

class Person {

private:
    string name;
    string surname;
    int age;

public:
    string get_name() {return name;}
    string get_surname() {return surname;}
	int get_age() {return age;}

	Person(string name,string surname,int age): name(name), surname(surname), age(age)  {};

    Person() = default;
    friend ostream& operator<<(ostream& s,const Person & p);
};

ostream& operator<<(ostream& s,const Person & p) {
    s << p.name << " " << p.surname << " lat " << p.age << "\n";
    return s;
}

array<string, M> rand_names = {{"Adam","Bartek", "Cezary", "Darek", "Ewaryst", "Franek", "Grzegorz", "Henryk", "Idzi", "Janusz"}};
array<string, M> rand_surnames = {{"Kowalski", "Nowak", "Malinowski", "Wyszkowski", "Budzinski", "Lewandowski", "Zajac", "Wilk", "Wielki", "Czaj"}};

Person get_random() {
    int k = rand() % 10;
    int l = rand() % 10;
    int w = rand() % 90 + 10;

    return Person(rand_names[k], rand_surnames[l], w);
}

template<typename T>
void print(T t) {
    for(const auto &i: t) cout << i;
}
int main()
{
    cout << "Hello world!" << endl;

    return 0;
}



//Person::Person(): name("Jan"), surname("Kowalski"), age(65) {};


/*
int main() {
    srand(time(0));


    Person Me("Piotr", "Wasilewski", 32);
    cout << Me;


    Person random_person;
    for(int k = 0; k < M; k++) {
        random_person=get_random();
        cout << k+1 << ". " <<random_person;
    }


    array<Person, 10> grupa;
    for(auto &p: grupa) {
        p=get_random();
    }
    cout << "\nWylosowane osoby:\n\n";
    for_each(grupa.begin(), grupa.end(), [](const Person &p){cout << p;});

    //rosnco wzgledem nazwiska
    sort(grupa.begin(), grupa.end(), [](Person &p1, Person &p2 ){return p1.get_surname() <= p2.get_surname(); });
    cout << "\nrosnaco wzgledem nazwiska:\n";
    print(grupa);

    //rosnco wzgledem imienia
    sort(grupa.begin(), grupa.end(), [](Person &p1, Person &p2 ){return p1.get_name() <= p2.get_name(); });
    cout << "\nrosnaco wzgledem imienia:\n";
    print(grupa);

    //rosnco wzgledem wieku
    sort(grupa.begin(), grupa.end(), [](Person &p1, Person &p2 ){return p1.get_age() <= p2.get_age(); });
    cout << "\nrosnaco wzgledem wieku:\n";
    print(grupa);

    //malejaco wzgledem nazwiska
    sort(grupa.begin(), grupa.end(), [](Person &p1, Person &p2 ){return p1.get_surname() >= p2.get_surname(); });
    cout << "\nmalejaco wzgledem nazwiska:\n";
    print(grupa);

    //malejaco wzgledem imienia
    sort(grupa.begin(), grupa.end(), [](Person &p1, Person &p2 ){return p1.get_name() >= p2.get_name(); });
    cout << "\nmalejaco wzgledem imienia:\n";
    print(grupa);

    //malejaco wzgledem wieku
    sort(grupa.begin(), grupa.end(), [](Person &p1, Person &p2 ){return p1.get_age() >= p2.get_age(); });
    cout << "\nmalejaco wzgledem wieku:\n";
    print(grupa);

}
*/
