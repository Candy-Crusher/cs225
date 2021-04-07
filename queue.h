//
//  queue.h
//  Assignment 1
//
//  Created by Jin Yirou on 2021/4/4.
//

#ifndef queue_h
#define queue_h
#include <iostream>
#include <ctime>
template<class T> class Record
{
public:
    Record(void);
    int status;
    void setid(int number);
    void setname(char *string);
    void setadd(double x, double y);
    void setphone(int number);
    void setWeChat(char *string);
    void setemail(char *string);
    void setprof(int string);
    void setbirth(int number);
    void setagegroup(void);
    void setrisk(int number);
    void settime(time_t t);
    void setpre(Record<T> *pre);
    void setnext(Record<T> *next);
    
    int getid(void);
    char *getname(void);
    double* getadd(void);
    int getphone(void);
    char *getWeChat(void);
    char *getemail(void);
    int getprof(void);
    int getbirth(void);
    int getagegroup(void);
    int getrisk(void);
    time_t gettime(void);
    time_t t_out;
    time_t t_extra;
    time_t t_wait;
    
private:
    int identification;
    char *name;
    double address[2];
    int phone;
    char *WeChat;
    char *email;
    int profession;             //I~VIII
    int birthday;               //8 digits
    int agegroup;
    int riskstatus;             //0~3
    time_t timestamp;
    Record<T> *record_pre;
    Record<T> *record_next;
};

template<class T> Record<T>::Record(void)
{
    identification = 0;
    name = 0;
    address[0] = 0;
    address[1] = 0;
    phone = 0;
    WeChat = 0;
    email = 0;
    profession = -1;           //I~VIII
    birthday = -1;             //8 digits
    riskstatus = -1;           //0~3
    timestamp = -1;
    t_out = -1;
    t_extra = 0;
    t_wait = 0;
    record_pre = this;
    record_next = this;
}

template<class T> class Localq
{
public:
    Localq(int size = 20);
    Record<T> *pop(int index);
    void append(Record<T> *record);
    
    
private:
    int maxsize, minsize;
    int first, last;
    int recordnumber;           //how many registation files in this queue
    Record<T> *array;           //the array contains many records
    void allocate(void);
    void deallocate(void);
};

template<class T> Localq<T>::Localq(int size)
{
    maxsize = size;
    if (size < 20){
        minsize = size;
    }
    else {
        minsize = 20;
    }
    recordnumber = 0;
    first = 0;
    last = -1;
    array = new Record<T>[maxsize];
}

#endif /* queue_h */
