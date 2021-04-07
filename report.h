//
//  report.h
//  Assignment 1
//
//  Created by Wu Xiaoshan on 2021/4/7.
//

#ifndef report_h
#define report_h
#include <iostream>
#include <ctime>
template<class T> class Report
{
public:
    Report(void);
    
    void setprof(int string);
    void setage(int age);
    void setrisk(int number);
    void setwait(time_t t);
    int getprof(void);
    int getage(void);
    int getrisk(void);
    time_t getwait(void);
    
    
private:
    int profession;             //I~VIII
    int agegroup;
    int riskstatus;             //0~3
    time_t wait;
};

template<class T> Report<T>::Report(void)
{
    profession = -1;           //I~VIII
    riskstatus = -1;           //0~3
    agegroup = -1;
    wait = 0;
}

template<class T> class Reportq
{
public:
    Reportq(int size = 1000);
    void append(Record<T> *R);
    void display(void);
    
    
private:
    int maxsize, minsize;
    int reportnumber;           //how many registation files in this queue
    Report<T> *array;           //the array contains many records
    void allocate(void);
    void deallocate(void);
};

template<class T> Reportq<T>::Reportq(int size)
{
    maxsize = size;
    if (size < 20){
        minsize = size;
    }
    else {
        minsize = 20;
    }
    reportnumber = 0;
    array = new Report<T>[maxsize];
}

#endif /* reportq_h */
