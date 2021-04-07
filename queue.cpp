//
//  queue.cpp
//  Assignment 1
//
//  Created by Jin Yirou on 2021/4/4.
//

#include "queue.h"
#include <iostream>
#include <ctime>


template<class T> int Record<T>::getid(void)
{
    return identification;
}


template<class T> char *Record<T>::getname(void)
{
    return name;
}

template<class T> double* Record<T>::getadd(void)
{
    return address;
}

template<class T> int Record<T>::getphone(void)
{
    return phone;
}

template<class T> char *Record<T>::getWeChat(void)
{
    return WeChat;
}

template<class T> char *Record<T>::getemail(void)
{
    return email;
}

template<class T> int Record<T>::getprof(void)
{
    return profession;
}

template<class T> int Record<T>::getbirth(void)
{
    return birthday;
}

template<class T> int Record<T>::getagegroup(void)
{
    return agegroup;
}

template<class T> int Record<T>::getrisk(void)
{
    return riskstatus;
}

template<class T> time_t Record<T>::gettime(void)
{
    return timestamp;
}


template<class T> void Record<T>::setid(int number)
{
    identification = number;
    return;
}

template<class T> void Record<T>::setname(char *string)
{
    name = string;
    return ;
}

template<class T> void Record<T>::setadd(double x, double y)
{
    address[0] = x;
    address[1] = y;
    return ;
}

template<class T> void Record<T>::setphone(int number)
{
    phone = number;
    return ;
}

template<class T> void Record<T>::setWeChat(char *string)
{
    WeChat = string;
    return ;
}

template<class T> void Record<T>::setemail(char *string)
{
    email = string;
    return ;
}

template<class T> void Record<T>::setprof(int number)
{
    profession = number;
    return ;
}

template<class T> void Record<T>::setbirth(int number)
{
    birthday = number;
    return ;
}

template<class T> void Record<T>::setagegroup(void)
{
    int birth = birthday/10000;
    tm *time =localtime(&timestamp) ;
    int dif = (1900+time->tm_year)-birth;
    if (dif <= 12) {
        agegroup = 0;               //children
    } else if (12 < dif <= 18) {
        agegroup = 1;               //adolescents
    } else if (18 < dif <= 35) {
        agegroup = 2;               //young adults
    } else if (35 < dif <= 50) {
        agegroup = 3;               //adults
    } else if (50 < dif <= 65) {
        agegroup = 4;               //seniors
    } else if (65 < dif <= 75) {
        agegroup = 5;               //elderly people
    } else if (dif > 75) {
        agegroup = 6;               //old people
    }
    return ;
}

template<class T> void Record<T>::setrisk(int number)
{
    riskstatus = number;
    return ;
}

template<class T> void Record<T>::settime(time_t t)
{
    timestamp = t;
    return ;
}

template<class T> void Record<T>::setpre(Record<T> *pre)
{
    record_pre = pre;
    return ;
}

template<class T> void Record<T>::setnext(Record<T> *next)
{
    record_next = next;
    return ;
}





template<class T> Record<T> *Localq<T>::pop(int index)
{
    first++;
    return array[first];
}

template<class T> void Localq<T>::append(Record<T> *record)
{
    last++;
    Record<T> new_record;
    (*record).setpre(array[last-1]);
    (*array[last-1]).setnext(&record);
    if (recordnumber == maxsize) {
        allocate();
    }
    recordnumber++;
    array[last] = &record;
    return;
}


template<class T> void Localq<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < recordnumber; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = array[pos];
    }
    delete[] array;
    array = newarray;
    maxsize = newsize;
    first = 0;
    last = recordnumber -1;
    return;
}
