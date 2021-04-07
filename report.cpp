//
//  report.cpp
//  Assignment 1
//
//  Created by Jin Yirou on 2021/4/4.
//

#include "report.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

template<class T> void Report<T>::setprof(int string)
{
    profession = string;
    return ;
}

template<class T> void Report<T>::setage(int age)
{
    agegroup = age;
    return ;
}
template<class T> void Report<T>::setrisk(int number)
{
    riskstatus = number;
    return ;
}

template<class T> void Report<T>::setwait(time_t t)
{
    wait = t;
    return ;
}

template<class T> int Report<T>::getprof(void)
{
    return profession;
}

template<class T> int Report<T>::getage(void)
{
    return agegroup;
}

template<class T> int Report<T>::getrisk(void)
{
    return riskstatus;
}

template<class T> time_t Report<T>::getwait(void)
{
    return wait;
}

template<class T> void Reportq<T>::append(Record<T> *R)
{
    last++;
    Report<T> new_report;
    new_report.setprof(R->getprof());
    new_report.setagegroup(R->getagegroup());
    new_report.setrisk(R->getrisk());
    time_t time_wait = R->t_out - R->timestamp + R->t_extra;
    new_report.setwait(time_wait);
    if (reportnumber == maxsize) {
        allocate();
    }
    reportnumber++;
    array[last] = &new_report;
    return;
}

template<class T> void Reportq<T>::display(void)
{
    ofstream p;
    p.open("output.csv",ios::out|ios::trunc);                //打开文件路径
    //p<<"Number"<<","<<"Profession"<<","<<"Risk"<<","<<"AgeGroup"<< "," << "WaitTime" << endl;    //输入内容，注意要用逗号，隔开
    for(int i = 0; i < reportnumber; i++){
        p<< i+1 <<","<< array[i]->profession<<","<<array[i]->riskstatus<<","<<array[i]->agegroup<< "," << array[i]-> wait << endl;
    }
    p.close();
}


template<class T> void Reportq<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < reportnumber; ++i)
    {
        newarray[i] = array[i];
    }
    delete[] array;
    array = newarray;
    maxsize = newsize;
    return;
}

template<class T> void Reportq<T>::deallocate(void)
{
    delete[] array;
}
