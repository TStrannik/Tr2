#pragma region HEADERS
#include <iostream>
#include "SimpleTimer.h"

#include <functional>
#include <vector>
#include <string>

#include <thread>
#include <mutex>
#include <semaphore>



using namespace std;

#pragma region syntax

void start() {
    setlocale(LC_ALL, "RU_ru");
    system("color 70\n cls\n");
}

template <typename T> void w (T s) { std::cout << s; }
template <typename T> void wl(T s) { std::cout << s << std::endl; }
void wl() { std::cout << std::endl; }

inline void ttsleep(float t) { this_thread::sleep_for(chrono::milliseconds((int)(t * 1000))); }

#pragma endregion sugar

#pragma endregion HEADERS
#pragma region DEFINES

    #pragma region THREADS

                        // ( ) https://rekovalev.site/multithreading-3-cpp/
        #pragma region MUTEX_
            //#define MUTEX_1   // (+) SimpleCode
            //#define MUTEX_2   // (+) SimpleCode
            //#define MUTEX_3   // (+) SimpleCode
            //#define MUTEX_4   // (+) SimpleCode

            //#define MUTEX_5   // (+) https://www.youtube.com/watch?v=gO6ck1CuuDE
            //#define MUTEX_6   // ( ) https://www.youtube.com/watch?v=VhhsmgIRFsE
#pragma endregion mutex, reqursive_mutex, lock_guard, unique_lock mutex

        #pragma region SEMAPHORE_
            //#define SEMAPHORE_1 // (+) https://www.basicexamples.com/example/cpp/std-binary-semaphore
            #define SEMAPHORE_2 // ( )
        #pragma endregion binary_semaphore, counting_semaphore

    #pragma endregion 



    #pragma region voids

        #pragma region MUTEX_

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

            #ifdef MUTEX_3

static int C = 10;      // Number of calls
recursive_mutex rm;

void Foo(int a, int C) {

    rm.lock(); C++;

    w(a); w(" ");
    ttsleep(0.3);
    if (a <= 1) {
        wl();
        C--; rm.unlock();
        return;
    }
    a--;
    Foo(a, C);

    C--; rm.unlock();

}

            #endif // MUTEX_3

            #ifdef MUTEX_4

mutex mtx;

void Print(char ch) {

    unique_lock <mutex> ulock(mtx, defer_lock);

    ttsleep(2);

    //unique_lock <mutex> ulock(mtx);

    ulock.lock();


    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            w(ch);
            ttsleep(0.01);
        }
        wl();
    }
    wl();


    ulock.unlock();


    ttsleep(2);

}




            #endif

            #ifdef MUTEX_5


void foo(int& num, mutex& mtx) {

    while (1)
    {
        mtx.lock();
            num += 2;
            w("Foo: "); wl(num);
        mtx.unlock();

        ttsleep(0.05);
    }
}


void bar(int& num, mutex& mtx) {

    while (1)
    {
        mtx.lock();
            num -= 2;
            w("Bar: "); wl(num);
        mtx.unlock();

        ttsleep(0.05);
    }
}


            #endif // MUTEX_5

        #pragma endregion MUTEX_

        #pragma region SEMAPHORE_
            #ifdef SEMAPHORE_1

binary_semaphore semaphore(1);

void printThreadId(int id) {
    semaphore.acquire();                         // Attempt to acquire the semaphore

    w("Thread ["); w(id); w("]\tID: "); w(this_thread::get_id()); wl("\tis executing");

    semaphore.release();                         // Release the semaphore
}

            #endif SEMAPHORE_1

        #pragma endregion SEMAPHORE_

    #pragma endregion voids

#pragma endregion DEFS





#ifdef SEMAPHORE_2



#endif // SEMAPHORE_2






#pragma region int
int main() {
    start();
    SimpleTimer t("main");
    
#pragma region MUTEX_
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

    thread t1(Foo, 10, C);
    thread t2(Foo, 10, C);

    t1.join();
    t2.join();

    wl(); wl(C);

#endif // MUTEX_3

#ifdef MUTEX_4


    thread t1(Print, '#');
    thread t2(Print, '@');

    t1.join();
    t2.join();


#endif 

#ifdef MUTEX_5


    int num = 10;
    mutex mtx;

    thread t1(foo, ref(num), ref(mtx));
    thread t2(bar, ref(num), ref(mtx));

    t1.join();
    t2.join();


#endif // MUTEX_5 

#pragma endregion MUTEX_

#pragma region SEMAPHORE_
#ifdef SEMAPHORE_1


    thread t1(printThreadId, 1);
    thread t2(printThreadId, 2);
    thread t3(printThreadId, 3);

    t1.join();
    t2.join();
    t3.join();


#endif SEMAPHORE_1

#pragma endregion SEMAPHORE_
    
#pragma endregion main() {




#ifdef SEMAPHORE_2

    counting_semaphore<5> sem(0);

    sem.release();  // Increment the semaphore count by 1
    sem.release(2); // Increment the semaphore count by 2

    w("Semaphore count: "); wl(sem.available());


#endif // SEMAPHORE_2




#pragma region return 0;
    



    //system("pause");
    return 0;
}
#pragma endregion }
