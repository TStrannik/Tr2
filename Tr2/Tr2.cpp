#pragma region HEADERS
#include <iostream>
#include <sstream>
#include "SimpleTimer.h"

#include <functional>
#include <vector>
#include <string>

#include <thread>
#include <mutex>
#include <semaphore>
#include <atomic>
#include <future>
#include <condition_variable>

using namespace std;

#pragma region syntax

template <typename T> void w (T s) { std::cout << s; }
template <typename T> void wl(T s) { std::cout << s << std::endl; }
void wl() { std::cout << std::endl; }

inline void ttsleep(float t) { this_thread::sleep_for(chrono::milliseconds((int)(t * 1000))); }

#pragma endregion sugar

#pragma endregion HEADERS
#pragma region DEFINES

    #pragma region THEMES 

        #pragma region THREADS_
        // ( ) https://rekovalev.site/multithreading-3-cpp/
        // ( ) https://learntutorials.net/ru/cplusplus/topic/9840/фьючерсы-и-обещания
                        
            #pragma region MUTEX_
                //#define MUTEX_1   // (+) [mutex] S.C... 
                //#define MUTEX_2   // (+) [lock_guard] S.C...
                //#define MUTEX_3   // (+) [reqursive_mutex] S.C...
                //#define MUTEX_4   // (+) [unique_lock] S.C...

                //#define MUTEX_5   // (+) [mutex][lock\unlock] https://www.youtube.com/watch?v=gO6ck1CuuDE
                //#define MUTEX_6   // ( )  https://www.youtube.com/watch?v=VhhsmgIRFsE
            #pragma endregion mutex, reqursive_mutex, lock_guard, unique_lock

            #pragma region SEMAPHORE_
                //#define SEMAPHORE_1 // (+) https://www.basicexamples.com/example/cpp/std-binary-semaphore
                //#define SEMAPHORE_2 // (+) https://rekovalev.site/multithreading-3-cpp/#sem

                //#define SEMAPHORE_10 // (+) training
            #pragma endregion binary_semaphore, counting_semaphore

            #pragma region SYNC-ASYNC_
                //#define ASYNC_1  // (+) [future][async]
                //#define ASYNC_2  // (+) [promise]
                //#define ASYNC_3  // (+) [future][async]
                //#define ASYNC_4  // (+) [future][async]
            #pragma endregion furure, async, promise

            #pragma region POSIX_
                //#define POSIX_1  // (+) []
            #pragma endregion pthread,

            #pragma region BARRIERS_
                //#define BARRIERS_1  // ()
            #pragma endregion 

            #pragma region ATOMIC_
                //#define AROMIC_1  // ()
            #pragma endregion 

            #pragma region CRITSECTION_
                //#define CRITSECTION_1   // ( )
            #pragma endregion 

        #pragma endregion mutex, semaphore, atomic, sync-async, POSIX

        #pragma region CODE_OPTIMISATION_
        // ( ) https://habr.com/ru/companies/vk/articles/279449/
        
                // ...
                
                // ...

        #pragma endregion 

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

            #endif // SEMAPHORE_1

            #ifdef SEMAPHORE_2
counting_semaphore<3> sem(3);

void worker(int id)
{
    sem.acquire();

    cout << (stringstream() << "Поток " << id << " работает\n").str() << endl;
    ttsleep(4);
    cout << (stringstream() << "Поток " << id << " закончил\n").str();

    sem.release();
}
            #endif // SEMAPHORE_2

            #ifdef SEMAPHORE_10

counting_semaphore <2> sem(2);

void op1(vector <int>& vec, string& res) {
    sem.acquire();
    for (auto i : vec) if (i % 10 == 0) { w("op1 "); res += (to_string(i) + " "); ttsleep(0.1); }
    wl();
    sem.release();
}
void op2(vector <int>& vec, string& res) {
    sem.acquire();
    for (auto i : vec) if (i % 5 == 0) { w("op2 "); res += (to_string(i) + " "); ttsleep(0.1); }
    wl();
    sem.release();
}
void op3(vector <int>& vec, string& res) {
    sem.acquire();
    for (auto i : vec) if (i % 3 == 0) { w("op3 "); res += (to_string(i) + " "); ttsleep(0.1); }
    wl();
    sem.release();
}

            #endif // SEMAPHORE_10

        #pragma endregion SEMAPHORE_

        #pragma region SYNC-ASYNC_

            #ifdef ASYNC_1

            int threadFunction()
            {
                wl("threadFunction start ");
                ttsleep(1);
                wl("threadFunction ready ");
                return 42;
            }

            #endif // ASYNC_1
 
            #ifdef ASYNC_3
int func() { ttsleep(3); return 41; }
            #endif // ASYNC_3


        #pragma endregion 



    #pragma endregion methods for lessons

#pragma endregion DEFS


#ifdef POSIX_1
#endif // POSIX_1            

//===============================================================================


timed_mutex tmtx;



void Foo(char c) {

    if (tmtx.try_lock_for(std::chrono::milliseconds(5)))
    {
        for (size_t i = 0; i < 5; i++)
        {
            for (size_t j = 0; j < 5; j++)
            {
                w(c);
                ttsleep(.1);
            }
            wl();
        }
        wl();

        tmtx.unlock();
    } 
     else {  }

}



#pragma region int
int main() {
    setlocale(LC_ALL, "RU_ru");
    system("color 70\n cls\n");

    SimpleTimer t("main");



    #pragma region THREADS_

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


            #endif // SEMAPHORE_1

            #ifdef SEMAPHORE_2

        thread threads[10];

        for (size_t i = 0; i < 10; ++i) {
            threads[i] = thread(worker, i + 1);
            //ttsleep(0.5);
        }

        for (auto& t : threads)
            t.join();
            #endif // SEMAPHORE_2

            #ifdef SEMAPHORE_10
        vector <string> vout = { "", "", "" };

        vector vec = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50,
                        55, 60, 65, 70, 75, 80, 85, 90, 95, 100 };


        thread t1(op1, ref(vec), ref(vout.at(0)));
        ttsleep(0.1);
        thread t2(op2, ref(vec), ref(vout.at(1)));
        ttsleep(0.1);
        thread t3(op3, ref(vec), ref(vout.at(2)));

        t1.join();
        t2.join();
        t3.join();


        w(vout.at(0)); w(" "); wl();
        w(vout.at(1)); w(" "); wl();
        w(vout.at(2)); w(" "); wl();
            #endif // SEMAPHORE_10

    #pragma endregion SEMAPHORE_

        #pragma region SYNC-ASYNC

            #ifdef ASYNC_1

    future <int> asyncFuture = async(threadFunction);           // Запуск асинхронной задачи
    
    
    wl("main start ");
    ttsleep(4);
    wl("main ready ");
    
    
    int result = asyncFuture.get();
    w("Result: "); wl(result);
    
            #endif // ASYNC_1
    
            #ifdef ASYNC_2
    
    
    auto prom1 = std::promise <string>();
    auto prom2 = std::promise <int>();
    
    auto t1 = thread([&] {
        prom1.set_value("Gavka");
        prom2.set_value(41);
        });
    
    future <string> futr1 = prom1.get_future();
    auto futr2 = prom2.get_future();
    
    thread t2 = thread([&] {
        wl(futr1.get());
        wl(futr2.get());
        });
    
    
    t1.join();
    t2.join();


            #endif // ASYNC_2

            #ifdef ASYNC_3


    //std::future <int>
    /*auto futr1 = async(func);
    w("Результат: "); wl(futr1.get());*/
    
    w("Результат: "); wl(async(func).get());


            #endif // ASYNC_3

            #ifdef ASYNC_4

    future <void> asFut1 =
    async(launch::async, []() {
    for (int i = 0; i < 15; i++) { wl("1"); ttsleep(0.1); }
    });
    
    future <void> asFut2 =
    async(launch::async, []() {
    for (int i = 0; i < 15; i++) { wl("2"); ttsleep(0.1); }
    });

            #endif // ASYNC_4

        #pragma endregion SYNC-ASYNC

    #pragma endregion THREADS_


    
#pragma endregion main() {

    thread t1(Foo, '#');
    thread t2(Foo, '@');
    thread t3(Foo, '%');

    t1.join();
    t2.join();
    t3.join();

#pragma region return 0;
    



    //system("pause");
    return 0;
}
#pragma endregion }

