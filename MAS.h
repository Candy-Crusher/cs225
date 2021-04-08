//
//  queue.h
//  Assignment 1
//
//  Created by Jin Yirou on 2021/4/4.
//

#ifndef MAS_h
#define MAS_h
#include <iostream>
#include <ctime>


//************************************************Queue.h*******************************************/
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
class Record
{
public:
    Record(void);
    int status;
    int monthflag;
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
    void setleft(Record *pre);
    void setright(Record *next);
    
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

    int degree;            // 度数
    Record *left;    // 左兄弟
    Record *right;    // 右兄弟
    Record *child;    // 第一个孩子节点
    Record *parent;    // 父节点
    bool marked;        // 是否被删除第一个孩子

    
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
};

Record::Record(void)
{
    degree = 0;
    marked = false;
    left   = this;
    right  = this;
    parent = NULL;
    child  = NULL;

    status = -1;
    monthflag = 1;
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
}

class Localq
{
public:
    Localq(int size = 20);
    Record *pop();
    void append(Record *record);
    
    
private:
    int maxsize, minsize;
    int first, last;
    int recordnumber;           //how many registation files in this queue
    Record **array;           //the array contains many records
    void allocate(void);
};

Localq::Localq(int size)
{
    maxsize = size;
    if (size < 20){
        minsize = size;
    }
    else {
        minsize = 20;
    }
    recordnumber = 0;
    first = -1;
    last = -1;
    array = new Record *[maxsize];
}

#endif /* queue_h */


//*******************************************************************************************/

//************************************************f.h*******************************************/

class FibHeap {
    private:
        int keyNum;         // 堆中节点的总数
        int maxDegree;      // 最大度
        Record **cons;    // 最大度的内存区域

    public:
        FibHeap();
        ~FibHeap();
        Record *min;    // 最小节点(某个最小堆的根节点)
        bool compare(Record *node1, Record *node2);
        // 移除斐波那契堆中的最小节点
        Record* removeMin();
        // 将双向链表a连接到root
        void addlocal(Record *a,Record *b);
         // 合并斐波那契堆的根链表中左右相同度数的树
        void consolidate();

        Record* search(Record *root, int id);
        // 更新斐波那契堆的节点node的键值为key
        void updateprofession(Record*node,int newprof);
        void updateRisk(Record*node, int newrisk);
    private:
        // 将node从双链表移除
        void removeNode(Record *node);
        // 将node堆结点加入root结点之前(循环链表中)
        void addNode(Record *node, Record *root);
         // 创建consolidate所需空间
        void makeCons();
        // 将node链接到root根结点
        void link(Record* node, Record* root);
        // 对节点node进行"级联剪切"
        void cascadingCut(Record *node) ;
        // 将node从父节点parent的子链接中剥离出来，并使node成为"堆的根链表"中的一员。
        void cut(Record *node, Record *parent);
        // 修改度数
        void renewDegree(Record *parent, int degree);
        // 将斐波那契堆中节点node的值减少为key
        void decrease(Record *node);
        
};
//*******************************************************************************************/

#endif