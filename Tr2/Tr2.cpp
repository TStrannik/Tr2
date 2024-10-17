#pragma region HEADERS
#include <iostream>
#include "SimpleTimer.h"

#include <functional>
#include <vector>
#include <string>

#include <thread>
#include <mutex>

using namespace std;

#pragma region VOIDS
void start() {
    setlocale(LC_ALL, "RU_ru");
    system("color 70\n cls\n");
}

template <typename T> void w (T s) { std::cout << s; }
template <typename T> void wl(T s) { std::cout << s << std::endl; }
void wl() { std::cout << std::endl; }
#pragma endregion VOIDS

#pragma endregion HEADERS
#pragma region DEFS

//#define MUTEX_1
//#define MUTEX_2
#define MUTEX_3
#define BABKA




#ifdef MUTEX_1

mutex mtx;

void print(char ch) 
{
    this_thread::sleep_for(chrono::milliseconds(2000));

    {
        lock_guard <mutex> guard(mtx);

        //mtx.lock();

        for (size_t i = 0; i < 5; i++)
        {
            for (size_t j = 0; j < 10; j++)
            {
                cout << ch;
                this_thread::sleep_for(chrono::milliseconds(20));
            }
            cout << endl;
        }
        cout << endl;

        //mtx.unlock();
    }


    this_thread::sleep_for(chrono::milliseconds(2000));
}

#endif // MUTEX_1

#ifdef MUTEX_2

mutex mtx1;
mutex mtx2;

void Print() {

    mtx1.lock();
        this_thread::sleep_for(chrono::milliseconds(1));
        mtx2.lock();

            for (size_t i = 0; i < 5; i++)
            {
                for (size_t j = 0; j < 10; j++)
                {
                    cout << '*';
                    this_thread::sleep_for(chrono::milliseconds(10));
                }
                cout << endl;
            }
            cout << endl;

        mtx1.unlock();
    mtx2.unlock();
}
void Print2() {
   
    mtx1.lock();
        this_thread::sleep_for(chrono::milliseconds(1));
        mtx2.lock();

            for (size_t i = 0; i < 5; i++)
            {
                for (size_t j = 0; j < 10; j++)
                {
                    cout << '#';
                    this_thread::sleep_for(chrono::milliseconds(10));
                }
                cout << endl;
            }
            cout << endl;

        mtx1.unlock();
    mtx2.unlock();
}


#endif // MUTEX_2



#pragma endregion DEFS



#ifdef MUTEX_3



recursive_mutex rm;
mutex m;



#endif // MUTEX_3





#pragma region int
int main() {
    start();
    SimpleTimer t("main");
    


#ifdef MUTEX_1
    

    thread t1(print, '*');
    thread t2(print, '#');
    thread t3(print, '@');

    t1.join();
    t2.join();
    t3.join();
    

    // print('*');
    // print('#');
    // print('@');


#endif // MUTEX_1

#ifdef MUTEX_2


    thread t1(Print);
    thread t2(Print2);

    t1.join();
    t2.join();

#endif // MUTEX_2

    #ifdef MUTEX_3
#pragma endregion main() {


    rm.lock();
    rm.lock();

    rm.unlock();
    rm.unlock();



#pragma region return 0;
    #endif // MUTEX_3



    //system("pause");
    return 0;
}
#pragma endregion }