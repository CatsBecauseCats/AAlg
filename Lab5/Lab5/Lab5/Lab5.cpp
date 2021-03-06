// Lab5.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include "ringbuffer.h"
#include <thread>
#include <chrono>
using namespace std;
#define GEN_BUFSIZE 20
#define SUM_BUFSIZE 20

typedef unsigned long long int timeType;
/*
 * ����� ����������� ���������� �� ������
 *
*/

template <class T>
void LSD(T* arr, int l, int r)
{
    int k = 256;                                  //0
    for(int i = 0; i < sizeof(T); ++i) {
        int count[k];
        for(int j = 0; j < k; ++j) {
            count[j] = 0;                         //1
        }
        for(int j = l; j < r; ++j) {
            int byte = (arr[j] >> (8 * i)) & 255; //2
            ++count[byte];                        //3
        }
        for(int j = 1; j < k; j++) {
            count[j] += count[j-1];               //4
        }
        T new_arr[r - l];
        for(int j = r - 1; j >= l; --j) {
            int byte = (arr[j] >> (8 * i)) & 255; //5
            int ind = --count[byte] - l;          //6
            new_arr[ind] = arr[j];                //7
        }
        for(int j = l; j < r; j++) {
            arr[j] = new_arr[j - l];              //8
        }
    }
}
template <typename T>
void generateNewData(RingBuffer<T, GEN_BUFSIZE> &buff, timeType sleep)
{
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));

        if(!buff.isFull()) {
            buff.push(rand() % 3);
        }
    }
}
template <typename T>
void sumData(RingBuffer<T, SUM_BUFSIZE> &sumBuff, RingBuffer<T, GEN_BUFSIZE> &buff, timeType sleep, size_t sumCount)
{
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));

        if(buff.getCount() >= sumCount) {
            T sum = 0;
            for(size_t i = 0; i < sumCount; i++) {
                T x;
                buff.pop(x);
                sum += x;
            }
            while(sumBuff.isFull()) {}
            sumBuff.push(sum);
        }
    }
}

template <typename T>
void printData(RingBuffer<T, SUM_BUFSIZE> &sumBuff, timeType sleep)
{
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
//cout << "1 ";
        if(!sumBuff.isEmpty()) {
            T x;
            sumBuff.pop(x);
            //system("sl");
            cout << x << " " << std::flush;// << endl;

            //std::flush = true;
        }
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    RingBuffer<int, GEN_BUFSIZE> generBuff;
    RingBuffer<int, SUM_BUFSIZE> sumBuff;

    std::thread generator(&generateNewData<int>, std::ref(generBuff), 10);
    std::thread summator(&sumData<int>, std::ref(sumBuff), std::ref(generBuff), 20, 2);
    std::thread printator(&printData<int>, std::ref(sumBuff), 1);

    generator.join();
    summator.join();
    printator.join();
	return 0;
}
    /*
    RingBuffer<int, 3> buff;
    buff.print();

    buff.push(1);
    buff.print();

    buff.push(2);
    buff.print();

    buff.push(3);
    buff.print();

    buff.push(4);
    buff.print();

    int x;

    buff.pop(x);
    buff.print();

    buff.push(4);
    buff.print();

    buff.pop(x);
    buff.print();

    buff.pop(x);
    buff.print();

    buff.pop(x);
    buff.print();*/


	/*    int n;
    cin >> n;

    long long *a = new long long [n];

    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    LSD<long long>(a, 0, n);

    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    delete[] a;*/


