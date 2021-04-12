//
//  queue.h
//  Assignment 1
//
//  Created by Jin Yirou on 2021/4/4.
//

#ifndef RQR_h
#define RQR_h
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility> // pair
using namespace std; 


//************************************************Queue.h*******************************************/
//
//  queue.h
//  Assignment 1
//
//  Created by Jin Yirou on 2021/4/4.
//


#include <iostream>
#include <ctime>


class Hospital;
class Record
{
public:
    Record(void);
    ~Record();
    int status;
    int withdrawflag;//0:no withdraw; 1:withdrawn
    int t_appointed;
    Hospital* hospital;
    void setid(int number);
    void setname(const char *string);
    void setadd(double x, double y);
    void setphone(int number);
    void setWeChat(const char *string);
    void setemail(const char *string);
    void setprof(int string);
    void setbirth(int number);
    void setagegroup(void);
    void setrisk(int number);
    void settime(int t);
    void setleft(Record *pre);
    void setright(Record *next);
    
    int getid(void);
    
    const char *getname(void);
    double* getadd(void);
    int getphone(void);
    const char *getWeChat(void);
    const char *getemail(void);
    int getprof(void);
    int getbirth(void);
    int getagegroup(void);
    int getrisk(void);
    int gettime(void);
    int t_out;
    int t_extra;

    int degree;            // 度数
    Record *left;    // 左兄弟
    Record *right;    // 右兄弟
    Record *child;    // 第一个孩子节点
    Record *parent;    // 父节点
    bool marked;        // 是否被删除第一个孩子
    int ddl;
    
private:
    int identification;
    const char *name;
    double address[2];
    int phone;
    const char *WeChat;
    const char *email;
    int profession;             //I~VIII
    int birthday;               //8 digits
    int agegroup;
    int riskstatus;             //0~3
    int t_in;
};

Record::Record(void)
{
    t_appointed = 0;
    degree = 0;
    marked = false;
    left   = this;
    right  = this;
    parent = NULL;
    child  = NULL;
    ddl=0;
    status = -1;
    withdrawflag = 0;
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
    t_out = -1;
    t_extra = 0;
    t_in = 0;
}
class Localq
{
public:
    Localq(int size = 20);
    ~Localq();
    Record *pop();
    void append(Record *record);
    int recordnumber; 
private:
    int maxsize, minsize;
    int first, last;
              //how many registation files in this queue
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




//*******************************************************************************************/

//************************************************f.h*******************************************/

class FibHeap {
    private:
        
        int maxDegree;      // 最大度
        Record **cons;    // 最大度的内存区域

    public:
        int keyNum;         // 堆中节点的总数
        FibHeap();
        ~FibHeap();
        Record *min;    // 最小节点(某个最小堆的根节点)
        bool compare(Record *node1, Record *node2);
        //
        Record* extractMin();
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
        void withdrawFibHeap(Record *record);
        //find record through id
        Record* find(Record* root,int id);
        // 将node堆结点加入root结点之前(循环链表中)
        void addNode(Record *node, Record *root);
        // 打印"斐波那契堆"
        void print(Record *node, vector<string>* v1, vector<string>* v2, vector<string>* v3,
                vector<string>* v4, vector<string>* v5, vector<string>* v6);
        void printM(Record *node, int* RegisterNumber, int* WaitNumber, int* WaitTime, int* WithdrawNumber);
    private:
        // 将node从双链表移除
        void removeNode(Record *node);
        
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
        // 将斐波那契堆中节点node的值增加为key
        void increase(Record *node);
        
        
};
//*******************************************************************************************/



//**********************************************************************************************

class Hospital{
    public:
    Hospital();
    ~Hospital();
    int id;
    int max_app;//maxsize of appointments
    int max_com;//maxsize of complements
    int status;//0: appointed not full; 1: appointed full
    void setlocation(double x, double y);
    double *getlocation();
    int getnum_app();
    void append(int index, Record   *node);//index=0: appointed; index=1: completed 
    void complete(int T);
    void withdraw(Record *node);
    Record  **appointed;//array of pointers to appointed records. 
    Record  **completed;//array of pointers to completed records.
    int num_com;//number of completed records. 


    private:
    double location[2];
    int num_app;//number of appointed records.
    void allocate(void);
    void deallocate(void);
};

void Appoint(FibHeap *Fib, Hospital *H1, Hospital *H2, Hospital *H3, int T);



//********************************************report*******************************************//
void write_csv(string filename, vector<pair<string, vector<string>>> dataset);
void WeeklyReport(FibHeap* F, Hospital* H1, Hospital* H2, Hospital* H3);
void WOneRecord(Record* record, vector<string>* v1, vector<string>* v2, vector<string>* v3,
                vector<string>* v4, vector<string>* v5, vector<string>* v6);
void MonthlyReport(FibHeap* F, Hospital* H1, Hospital* H2, Hospital* H3);


//********************************************read***************************************//
void CountLine(string filename);
void ReadRecord(string filename ,int line_n, Localq* Q);

#endif 