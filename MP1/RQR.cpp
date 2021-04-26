//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//
//  queue.cpp
//  Assignment 1
//
//  Created by Jin Yirou on 2021/4/4.
//

#include "RQR.h"
#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <typeinfo>
#include <string>
#include <sstream>
#include <fstream>
using namespace std; 

//ATTENTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
static int line_start = 1;
static int t_start = 20210410;
static int T = 1;
static int S_T;
static int RowCount=0;
//ATTENTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void withdraw(Record* record, FibHeap* F, Hospital* H1, Hospital* H2, Hospital* H3){
    record->withdrawflag = 1;
    switch(record->status){
        case 2:
            cout << "Already treated, cannot withdraw" << endl;
            break;
        case 1:
            cout << "withdraw1"<<endl;
            cout << record->getid() <<endl;
            record->hospital->withdraw(record);
            cout << "withdraw2"<<endl;
            record->status = 0;
            cout << record->getid() <<endl;
            F->addlocal(F->min,record);
            
            cout << "withdraw3"<<endl;
            break;
        case 0:
            F->withdrawFibHeap(record);
            break;
        case -1:
            cout << "Cannot withdraw within half day" << endl;
            break;
        default:
            cout << "No such status" << endl;
    }

} 

Record::~Record(){}

int Record::getid(void)
{
    return identification;
}


const char *Record::getname(void)
{
    return name;
}

double* Record::getadd(void)
{
    return address;
}

int Record::getphone(void)
{
    return phone;
}

const char *Record::getWeChat(void)
{
    return WeChat;
}

const char *Record::getemail(void)
{
    return email;
}

int Record::getprof(void)
{
    return profession;
}

int Record::getbirth(void)
{
    return birthday;
}

int Record::getagegroup(void)
{
    return agegroup;
}

int Record::getrisk(void)
{
    return riskstatus;
}

int Record::gettime(void)
{
    return t_in;
}


void Record::setid(int number)
{
    identification = number;
    return;
}

void Record::setname(const char *string)
{
    name = string;
    return ;
}

void Record::setadd(double x, double y)
{
    address[0] = x;
    address[1] = y;
    return ;
}

void Record::setphone(int number)
{
    phone = number;
    return ;
}

void Record::setWeChat(const char *string)
{
    WeChat = string;
    return ;
}

void Record::setemail(const char *string)
{
    email = string;
    return ;
}

void Record::setprof(int number)
{
    profession = number;
    return ;
}

void Record::setbirth(int number)
{
    birthday = number;
    return ;
}

void Record::setagegroup(void)
{
    int birth = birthday/10000;
    int dif = t_start/10000-birth;
    if (dif <= 12) {
        agegroup = 0;               //children
    } else if (dif > 12 && dif <= 18) {
        agegroup = 1;               //adolescents
    } else if (dif > 18 && dif <= 35) {
        agegroup = 2;               //young adults
    } else if (dif > 35 && dif <= 50) {
        agegroup = 3;               //adults
    } else if (dif > 50 && dif <= 65) {
        agegroup = 4;               //seniors
    } else if (dif > 65 && dif <= 75) {
        agegroup = 5;               //elderly people
    } else if (dif > 75) {
        agegroup = 6;               //old people
    }
    return ;
}

void Record::setrisk(int number)
{
    riskstatus = number;
    return ;
}

void Record::settime(int t)
{
    t_in = t;
    //cout << "time now is" << t << endl;
    return ;
}

void Record::setleft(Record *pre)
{
    left = pre;
    return ;
}

void Record::setright(Record *next)
{
    right = next;
    return ;
}



Localq::~Localq(){
    delete[] array;
}

Record *Localq::pop()
{
    if(recordnumber==0){
        return NULL;
    }
    for(int i = first + 1; i <= last; i++){
        array[i]->status = 0;
    }
    int a = first+1;
    first = last;
    recordnumber = 0;
    return array[a];
}

void Localq::append(Record *record)
{
    last++;
     
    record->settime(T);

    record->setagegroup();
    if(record->getrisk() == 2){
        record->settime(record->gettime() + 60);
        record->t_extra += 60;
    }
    if (first == last - 1)
    {
        record->setleft(record);
        record->setright(record);
    } else {
        /* cout << "array[0] is " << array[0]->getid() <<endl;
        cout << "array[1] is " << array[1]->getid() <<endl; */
        record->setleft(array[last-1]);
        record->setright(array[first+1]);
        /* cout << "(record->left)->getid()" << endl;
        cout << (record->left)->getid() << endl;
        cout << "(record->right)->getid()" << endl;
        cout << (record->right)->getid() << endl;  */
        (array[last-1])->setright(record);
        (array[first+1])->setleft(record);
    }
    
    if (recordnumber == maxsize) {
        allocate();
    }
    
    recordnumber++;
    array[last] = record;  
    return;
}


void Localq::allocate(void)
{
    int newsize = 2 * maxsize;
    Record **newarray = new Record *[newsize];
    for (int i = 0; i < recordnumber; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = array[pos];
    }
    delete[] array;
    array = newarray;
    maxsize = newsize;
    last = recordnumber -1;
    return;
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

/*
 * 构造函数
 */

FibHeap::FibHeap()
{
    keyNum = 0;
    maxDegree = 0;
    min = NULL;
    cons = NULL;
}

/*
 * 析构函数
 */

FibHeap::~FibHeap()
{
}
//0 1优先级大于2 
//1 1优先级小于2
bool FibHeap::compare(Record *node1, Record *node2)
{
    if(node1->ddl==1&&node2->ddl!=1){
        return 0;
    }
    if(node1->ddl!=0&&node2->ddl==1){
        return 1;
    }
    if(node1->getrisk()==3 && node2->getrisk()!=3){
       
        return 1;
    }
    if(node1->getrisk()!=3&& node2->getrisk()==3){
        
        return 0;
    }
    if(node1->getprof()<node2->getprof()){
        
        return 0;
    }
    if(node1->getprof()>node2->getprof()){
        
        return 1;
    }else{
        if(node1->getagegroup()<node2->getagegroup()){
           
            return 0;
        }
        if(node1->getagegroup()>node2->getagegroup()){
           
            return 1;
        }else{
            if(node1->gettime()<=node2->gettime()){
               
                return 0;
            }else{
               
                return 1;
            }

        }
    }
}

Record* FibHeap::extractMin()
{
    Record *p = min;
    if (p == p->right){
        min = NULL;
    }else{
        removeNode(p);
        min = p->right;
       
    }
    p->left = p->right = p;
    
    return p;
}

void FibHeap::removeNode(Record *node)
{
    node->left->right = node->right; 
    
    node->right->left = node->left;
}
/*
 * 将node堆结点加入root结点之前(循环链表中)
 *   a …… root
 *   a …… node …… root
*/

void FibHeap::addNode(Record *node, Record *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

Record* FibHeap:: removeMin()
{
    Record *result;
    
    Record *child = NULL;
    Record *m = min;
    // 将min每一个儿子(儿子和儿子的兄弟)都添加到"斐波那契堆的根链表"中
    while (m->child != NULL)
    {
        child = m->child;
        removeNode(child);
        if (child->right == child)
            m->child = NULL;
        else
            m->child = child->right;

        addNode(child, min);
        child->parent = NULL;
    }
    
    result=min;
    // 将m从根链表中移除
    removeNode(m);
    // 若m是堆中唯一节点，则设置堆的最小节点为NULL；
    // 否则，设置堆的最小节点为一个非空节点(m->right)，然后再进行调节。
    
    if (m->right == m)
        min = NULL;
    else
    {
        min = m->right;
        consolidate();
    }
    keyNum--;
    result->right =result;
    result->left=result;
    return result;
}


void FibHeap::addlocal(Record *a,Record *b)
{
    
    if(b==NULL){
        return;
    }
    int counter = 1;
    
    Record* j = b->left;
    
    while(j!=b){
        counter++;
        b=b->right;
       
    }
    b=b->right;
    
    if(a==NULL){
        this->min=b;
        
    }else{
        Record *tmp;   
        tmp            = a->right;
        a->right       = b->right;
        b->right->left = a;
        b->right       = tmp;
        tmp->left      = b;
    }
    this->keyNum+=counter;
    
    consolidate();
    
    
}
/*
 * 在最小堆root中查找id的节点
 */

Record* FibHeap::search(Record *root, int id)
{
    Record *t = root;    // 临时节点
    Record *p = NULL;    // 要查找的节点

    if (root==NULL)
        return root;

    do
    {
        if (t->getid() == id)
        {
            p = t;
            break;
        }
        else
        {
            if ((p = search(t->child, id)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);

    return p;
}
//0 1优先级大于2 
//1 1优先级小于2
void FibHeap::consolidate()
{
    int i, d, D;
    Record *x, *y, *tmp;

    makeCons();//开辟哈希所用空间
    D = maxDegree + 1;
    
    for (i = 0; i < D; i++)
        cons[i] = NULL;
    
    // 合并相同度的根节点，使每个度数的树唯一
    while (min != NULL)
    {   
        
        x = extractMin();                // 取出堆中的最小树(最小节点所在的树)
       
        d = x->degree;                    // 获取最小树的度数
        // cons[d] != NULL，意味着有两棵树(x和y)的"度数"相同。
        while (cons[d] != NULL)
        {
            
            y = cons[d];                // y是"与x的度数相同的树"
            if (compare(x,y)==1)        // 保证x的键值比y小
                swap(x, y);
            link(y, x);    // 将y链接到x中
            cons[d] = NULL;
            d++;
        }
        cons[d] = x;
        
    }
    
    min = NULL;

    // 将cons中的结点重新加到根表中
    for (i=0; i<D; i++)
    {
        if (cons[i] != NULL)
        {
            if (min == NULL)
                min = cons[i];
            else
            {
                //0 1优先级大于2 
                //1 1优先级小于2
                addNode(cons[i], min);
                if (compare(cons[i], min)==0)
                    min = cons[i];
            }
        }
    }
    
    
}
/*
 * 创建consolidate所需空间
 */

void FibHeap::makeCons()
{
    int old = maxDegree;

    // 计算log2(keyNum)，"+1"意味着向上取整！
    // ex. log2(13) = 3，向上取整为3+1=4。
    maxDegree = (log(keyNum)/log(2.0)) + 1;
    if (old >= maxDegree)
        return ;

    // 因为度为maxDegree可能被合并，所以要maxDegree+1
    cons = (Record **)realloc(cons,
            sizeof(FibHeap *) * (maxDegree + 1));
}
/*
 * 将node链接到root根结点
 */

void FibHeap::link(Record* node, Record* root)
{
    // 将node从双链表中移除
    removeNode(node);
    // 将node设为root的孩子
    if (root->child == NULL)
        root->child = node;
    else
        addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = false;
}

void FibHeap::cascadingCut(Record *node)
{
    Record *parent = node->parent;
    if (parent != NULL)
    {
        if (node->marked == false)
            node->marked = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}
/*
 * 将node从父节点parent的子链接中剥离出来，
 * 并使node成为"堆的根链表"中的一员。
 */

void FibHeap::cut(Record *node, Record *parent)
{
    removeNode(node);
    renewDegree(parent, node->degree);
    // node没有兄弟
    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->marked = false;
    // 将"node所在树"添加到"根链表"中
    addNode(node, min);
}
/*
 * 修改度数
 */

void FibHeap::renewDegree(Record *parent, int degree)
{
    parent->degree -= degree;
    if (parent-> parent != NULL)
        renewDegree(parent->parent, degree);
}
/*
 * 将斐波那契堆中节点node的值减少为key
 */
//0 1优先级大于2 
//1 1优先级小于2

void FibHeap::decrease(Record *node)
{
    Record *parent;

    if (min==NULL ||node==NULL)
        return ;
    parent = node->parent;
    if (parent!=NULL && compare(node,parent)==0 )
    {
        // 将node从父节点parent中剥离出来，并将node添加到根链表中
        cut(node, parent);
        cascadingCut(parent);
    }

    // 更新最小节点
    if (compare(node,min)==0)
        min = node;
}
/* 
 * 将斐波那契堆中节点node的值增加为key
 */

void FibHeap::increase(Record *node)
{
    Record *child, *parent, *right;

    if (min==NULL ||node==NULL) 
        return ;
    // 将node每一个儿子(不包括孙子,重孙,...)都添加到"斐波那契堆的根链表"中
    while (node->child != NULL)
    {
        child = node->child;
        removeNode(child);               // 将child从node的子链表中删除
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        addNode(child, min);       // 将child添加到根链表中
        child->parent = NULL;
    }
    node->degree = 0;
    

    // 如果node不在根链表中，
    //     则将node从父节点parent的子链接中剥离出来，
    //     并使node成为"堆的根链表"中的一员，
    //     然后进行"级联剪切"
    // 否则，则判断是否需要更新堆的最小节点
    parent = node->parent;
    if(parent != NULL)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    else if(min == node)
    {
        right = node->right;
        while(right != node)
        {
            if(compare(node,right)==1 )
                min = right;
            right = right->right;
        }
    }
}

void FibHeap::updateprofession(Record *node, int newprof)
{
    if(newprof < node->getprof()){
        node->setprof(newprof);
        decrease(node);
    }
    
    return;
}


void FibHeap::updateRisk(Record *node, int newrisk)
{
    if(newrisk < node->getrisk()){
        node->setrisk(newrisk);
        decrease(node);
    }
    return;
}

void FibHeap::print(Record *node, vector<string>* v1, vector<string>* v2, vector<string>* v3,
                vector<string>* v4, vector<string>* v5, vector<string>* v6)
{
    Record *start=node;

    if (node==NULL)
        return ;
    do
    {
        WOneRecord(node,v1,v2,v3,v4,v5,v6);
        print(node->child, v1,v2,v3,v4,v5,v6);
        node = node->right;
    } while(node != start);
    
}


void FibHeap::printM(Record *node, int* RegisterNumber, int* WaitNumber, int* WaitTime, int* WithdrawNumber)
{
    Record *start=node;

    if (node==NULL)
        return ;
    do
    {
        if(T - 60 < node->gettime()){
            (*RegisterNumber)++;
            (*WaitNumber)++;
            int t = T - node->gettime() + node->t_extra;
            (*WaitTime) += t;
            if(node->withdrawflag == 1){
                (*WithdrawNumber)++;
            }
        }
        printM(node->child, RegisterNumber, WaitNumber, WaitTime, WithdrawNumber);
        node = node->right;
    } while(node != start);
    
}



void FibHeap::withdrawFibHeap(Record *record)
{
    record->settime(record->gettime() + 28);
    record->t_extra += 28;
    increase(record);
    return;
}
Record* FibHeap::find(Record* root,int id)
{
    Record *t = root;    // 临时节点
    Record *p = NULL;    // 要查找的节点

    if (root==NULL)
        return root;

    do
    {
        if (t-> getid() == id)
        {
            p = t;
            break;
        } 
        else
        {
            if ((p = find(t->child, id)) != NULL) 
                break;
        }    
        t = t->right;
    } while (t != root);

    return p;

}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Hospital::Hospital()
{
    id=0;
    max_app = 16;//two days, each day 8 operations.
    max_com = 16;
    status = 0;
    location[0] = 0;
    location[1] = 0;
    num_app = 0;
    num_com = 0;
    appointed = new Record * [max_app];
    completed = new Record * [max_com];
}

Hospital::~Hospital(){
    delete [] appointed;
    delete [] completed;
}

void Hospital::setlocation(double x, double y){
    location[0]=x;
    location[1]=y;
}

double *Hospital::getlocation(){
    return location;
}

int Hospital::getnum_app(){
    return num_app;
}

void Hospital::append(int index, Record   *node){
    if (!index){//index=0 for appointed, index=1 for completed.
        appointed[num_app] = node;
        ++num_app;
        if (num_app == max_app){
            status = 1;//appointed is full, unable to append.
        }
        return;
    }
    if (num_com == max_com)
        allocate();
    completed[num_com] = node;
    ++num_com;
    return;
}

void Hospital::complete(int T){
    
    if (num_app == 0){ return; }
    int now = T;
    int num_new = 0;
    
    Record **newarray = new Record * [max_app];
    
    for (int i = 0; i < num_app; i++ ){
        if (appointed[i] -> t_out <= now){//if now the appointed time has passed, the operation has completed.
            appointed[i] -> status = 2;
            append(1,appointed[i]);
        }
        else{
            newarray[num_new] = appointed[i];//otherwise he is still waiting for thr operation.
            num_new++;
        }
    }
 
    
    delete[] appointed;
    
    appointed = newarray;
    num_app = num_new;
      
    return;
}

void Hospital::withdraw(Record *node){
    int num_new = 0;
    node->settime(node->gettime() + 28);
    node->t_extra += 28;
    Record **newarray = new Record * [max_app];
    for (int i = 0; i < num_app; i++){
        if ( ! (node->getid() == appointed[i]->getid())){
            newarray[num_new] = appointed[i];
            num_new++;
        }
    }
    delete[] appointed;
    appointed = newarray;
    num_app = num_new;
}

void Hospital::allocate(void)
{
    int newsize = 2 * max_com;
    Record **newarray = new Record * [newsize];
    for (int i = 0; i < num_com; ++i)
    {
        newarray[i] = completed[i];
    }
    delete[] completed;
    completed = newarray;
    max_com = newsize;
    return;
}

void Hospital::deallocate()
{
    int newsize = max_com / 2;
    Record **newarray = new Record * [newsize];
    for (int i = 0; i < num_com; ++i)
    {
        newarray[i] = completed[i];
    }
    delete[] completed;
    completed = newarray;
    max_com = newsize;
    return;
}

void Appoint(FibHeap *Fib, Hospital *H1, Hospital *H2, Hospital *H3, int T){
    Hospital *H[3] = {H1, H2, H3};
    while ( ! H1->status || ! H2->status || ! H3->status){//if any of the three hospital is not full.
        if (Fib->keyNum == 0){
            return;
        }
        //cout << Fib->removeMin()->getid() << endl;
        Record *patient=Fib->removeMin();//pop the record with the highest priority from fibheap.
        //cout << "removed"<<Fib->keyNum << endl;
        if (patient->withdrawflag  && patient->gettime() < T){
            Fib->addlocal(Fib->min, patient);
            return;
        }
        double x=patient->getadd()[0];
        double y=patient->getadd()[1];
       
        double distance_1=(x-H1->getlocation()[0])*(x-H1->getlocation()[0])+(y-H1->getlocation()[1])*(y-H1->getlocation()[1]);
        double distance_2=(x-H2->getlocation()[0])*(x-H2->getlocation()[0])+(y-H2->getlocation()[1])*(y-H2->getlocation()[1]);
        double distance_3=(x-H3->getlocation()[0])*(x-H3->getlocation()[0])+(y-H3->getlocation()[1])*(y-H3->getlocation()[1]);
        int max,medium,min;
        if (distance_1 < distance_2){//compare and identify the order of the hospitals according to the distance from the hospital to the address.
            if (distance_2 < distance_3){
                max = 3;
                medium = 2;
                min = 1;
            }
            else {
                max = 2;
                if (distance_1 < distance_3){
                    medium = 3;
                    min = 1;
                }
                else{
                    medium = 1;
                    min = 3;
                }
            }
        }
        
        else {
            if (distance_1 < distance_3){
                max = 3;
                medium = 1;
                min = 2;
            }
            else {
                max = 1;
                if (distance_2 < distance_3){
                    medium = 3;
                    min = 2;
                    }
                else {
                    medium = 2;
                    min = 3;
                }
            }
        }
        Hospital *target;//check from the nearest hospital.
        if (! H[min-1]->status){
            target = H[min-1];
        }
        else if (! H[medium-1]->status){
            target = H[medium-1];
        }
        else {
            target = H[max-1];
        }
        target->append(0,patient);//add the patient to the appointed array of the hospital
        /*time_t now = time(0);
        tm *ltm = localtime(&now);
        ltm->tm_hour = 8;//reset the time from 8 am sharp (the first operation of a day)
        ltm->tm_min = 0;
        ltm->tm_sec = 0;
        time_t time = mktime(ltm);//convert back to time_t
        if (target->getnum_app() < 5){//if the operation is scheduled on the first day
            time += 24*3600;
            patient->t_out = time + 1*(target->getnum_app());
        }
        else {//otherwise it is scheduled on the second day.
            time += 48*3600;
            patient->t_out = time + 1*(target->getnum_app()-5);
        }
        */
        patient->t_out = T + ( target -> getnum_app() ) / 4 + 1;
        patient->t_appointed = T;
        patient->status=1;//set the status of the patient to appointed.
        patient->hospital=target;//set the status of the patient to the target hospital.
    }
    return;
}
/*
int main()
{
    
    Record R1;
    R1.setid(1);
    R1.setadd(1,1);
    R1.setbirth(20010630);
    R1.setprof(4);
    R1.setrisk(0);
    cout << "R1.status1" << endl;
    cout << R1.status << endl;
    Record R2;
    R2.setid(2);
    R2.setadd(1,0);
    R2.setbirth(20010630);
    R2.setprof(2);
    R2.setrisk(0);
    Record R3;
    R3.setid(3);
    R3.setadd(0,1);
    R3.setbirth(20090401);
    R3.setprof(2);
    R3.setrisk(0);
    Localq  Local1;
    Local1.append(&R1);
    cout << "R1.status2" << endl;
    cout << R1.status << endl;
    Local1.append(&R2);
    Local1.append(&R3);
    FibHeap center1;
    center1.addlocal(center1.min,Local1.pop());
   
    cout << "R1.status3" << endl;
    cout << R1.status << endl;
    
    Hospital H1;
    H1.id = 1;
    H1.setlocation(0,0);
    Hospital H2;
    H2.id = 2;
    H2.setlocation(1,0);
    Hospital H3;
    H3.id = 3;
    H3.setlocation(-1,0);
    
    //Appoint(&center1, &H1, &H2, &H3);
    
    cout << "*****************************REPORT TEST******************************" << endl;
    WeeklyReport(&center1,&H1,&H2,&H3);
    
    /* cout << "TEST FOR APPOINT:" <<endl;
    H2.withdraw(&R1);
    cout << H2.appointed[0]->getid() << endl;
    cout << H2.getnum_app() << endl;
    //cout << H2.appointed[1]->getid() << endl; 
    
    
    //cout << (R2.t_out) << endl;
    //cout << (R3.t_out) << endl;
    
}
*/

//*****************************************************************report********************************************//

void write_csv(string filename, vector<pair<string, vector<string>>> dataset){
    // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    //   as pair<string, vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size
    
    // Create an output filestream object
    ofstream myFile(filename);
    // Send column names to the stream
    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";
    // Send data to the stream
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }    
    // Close the file
    myFile.close();
}

void WeeklyReport(FibHeap* F, Hospital* H1, Hospital* H2, Hospital* H3){
    // Make six vectors
    vector<string> vec1;
    vector<string> vec2;
    vector<string> vec3;
    vector<string> vec4;
    vector<string> vec5;
    vector<string> vec6;
    //record FibHeap
    F->print(F->min,&vec1,&vec2,&vec3,&vec4,&vec5,&vec6);
    //record H1
    for(int i = 0; i < H1->getnum_app() ; i++){
        WOneRecord(H1->appointed[i],&vec1,&vec2,&vec3,&vec4,&vec5,&vec6);
    };
    //record H2
    for(int i = 0; i < H2->getnum_app() ; i++){
        WOneRecord(H2->appointed[i],&vec1,&vec2,&vec3,&vec4,&vec5,&vec6);
    };
    //record H3
    for(int i = 0; i < H3->getnum_app() ; i++){
        WOneRecord(H3->appointed[i],&vec1,&vec2,&vec3,&vec4,&vec5,&vec6);
    };
    
    for (int i =0; i < H1->num_com; i++ ){
        if (H1->completed[i]->t_out >= T - 14 ){
            WOneRecord(H1->completed[i],&vec1,&vec2,&vec3,&vec4,&vec5,&vec6);
        }
    }

    for (int i =0; i < H2->num_com; i++ ){
        if (H2->completed[i]->t_out >= T - 14 ){
            WOneRecord(H2->completed[i],&vec1,&vec2,&vec3,&vec4,&vec5,&vec6);
        }
    }

    for (int i =0; i < H3->num_com; i++ ){
        if (H3->completed[i]->t_out >= T - 14 ){
            WOneRecord(H3->completed[i],&vec1,&vec2,&vec3,&vec4,&vec5,&vec6);
        }
    }

     // Wrap into a vector
    vector<pair<string, vector<string>>> vals = {{"ID", vec1}, {"Status", vec2}, {"RiskLevel", vec3},{"Profession", vec4}, {"AgeGroup", vec5}, {"WaitingTime(in half day)", vec6}};
    // Write the vector to CSV
    write_csv("WeeklyReport.csv", vals);
}


void WOneRecord(Record* record, vector<string>* v1, vector<string>* v2, vector<string>* v3,
                vector<string>* v4, vector<string>* v5, vector<string>* v6){
                    string id = to_string(record->getid());
                    v1->push_back(id);
                    string wt;
                    switch(record->status){
                        case -1:
                            v2->push_back("waiting");
                            wt = to_string((double) (T - record->gettime() + record->t_extra)/2);
                            v6->push_back(wt);
                            break;
                        case 0:
                            v2->push_back("waiting");
                            wt = to_string((T - record->gettime() + record->t_extra));
                            v6->push_back(wt);
                            break;
                        case 1:
                            v2->push_back("appointed");
                            wt = to_string((T - record->gettime() + record->t_extra));
                            v6->push_back(wt);
                            break;
                        case 2:
                            v2->push_back("completed");
                            wt = to_string((record->t_out - record->gettime() + record->t_extra));
                            v6->push_back(wt);
                            break;
                    }
                    switch(record->getrisk()){
                        case 0:
                            v3->push_back("no risk");
                            break;
                        case 1:
                            v3->push_back("low risk");
                            break;
                        case 2:
                            v3->push_back("medium risk");
                            break;
                        case 3:
                            v3->push_back("high risk");
                            break;
                    }
                    switch(record->getprof()){
                        case 1:
                            v4->push_back("1");
                            break;
                        case 2:
                            v4->push_back("2");
                            break;
                        case 3:
                            v4->push_back("3");
                            break;
                        case 4:
                            v4->push_back("4");
                            break;
                        case 5:
                            v4->push_back("5");
                            break;
                        case 6:
                            v4->push_back("6");
                            break;
                        case 7:
                            v4->push_back("7");
                            break;
                        case 8:
                            v4->push_back("8");
                            break;
                    }
                    switch(record->getagegroup()){
                        case 0:
                            v5->push_back("children (<= 12 years)");
                            break;
                        case 1:
                            v5->push_back("adolescents (<= 18 years)");
                            break;
                        case 2:
                            v5->push_back("young adults (<= 35 years)");
                            break;
                        case 3:
                            v5->push_back("adults (<= 50 years)");
                            break;
                        case 4:
                            v5->push_back("seniors (<= 65 years)");
                            break;
                        case 5:
                            v5->push_back("elderly people (<= 75 years)");
                            break;
                        case 6:
                            v5->push_back("old people (> 75 years)");
                            break;
                    }                    
                }


//****************************************************************read************************************************//
void CountLine(string filename){
    string s; 
    ifstream in(filename);

    while(!in.eof()) {
        getline(in, s);
        RowCount ++;
    }
    in.close();
    return;

}
void ReadRecord(string filename ,int line_n, Localq* Q){
    ifstream fp(filename); //定义声明一个ifstream对象，指定文件路径
    string line;
    for(int i = 1; i < line_start; i++){
        getline(fp,line); //跳过已读行
    }
    if(line_start + line_n > RowCount){
        cout << "Required records beyond provided" << endl;
        return;
    }
    line_start = line_start + line_n;
    cout << "line start now is:  " << line_start << endl;
    int j = 1;
    while((getline(fp,line)) && (j <= line_n)){
        
        j++;
        Record *record = new Record;      
        
        string number;
        string number2;
        istringstream readstr(line); //string数据流化

        //将一行数据按'，'分割
        //csv格式 id, name, address_x, address_y, phone, Wechat, email, profession, brithday, riskstatus, T
        //id
        getline(readstr,number,','); //读取数据
        record->setid(atoi(number.c_str())); 
        //name
        getline(readstr,number,','); //读取数据
        record->setname(number.c_str());
        //address
        getline(readstr,number,','); //读取数据
        getline(readstr,number2,','); //读取数据
        record->setadd(atol(number.c_str()),atol(number2.c_str()));
        //phone
        getline(readstr,number,','); //读取数据
        record->setphone(atoi(number.c_str()));
        //Wechat
        getline(readstr,number,','); //读取数据
        record->setWeChat(number.c_str());
        //email
        getline(readstr,number,','); //读取数据
        record->setemail(number.c_str());
        //profession
        getline(readstr,number,','); //读取数据
        record->setprof(atoi(number.c_str()));
        //birthday
        getline(readstr,number,','); //读取数据
        record->setbirth(atoi(number.c_str()));
        //risk
        getline(readstr,number,','); //读取数据
        record->setrisk(atoi(number.c_str()));
        //T
        getline(readstr,number,','); //读取数据
        record->settime(atoi(number.c_str()));
        //cout << "the id is " << record->getid()<< endl;
        Q->append(record); 
        //delete record;
    }
}

//**************************************************MonthlyReport************************//
//register_num wait_num appoint_num avg_waiting_time withdraw_num
void MonthlyReport(FibHeap* F, Hospital* H1, Hospital* H2, Hospital* H3){
    int register_num = 0;
    int wait_num = 0;
    int appoint_num = H1->getnum_app() + H2->getnum_app() + H3->getnum_app();
    int waiting_time = 0;
    int withdraw_num = 0;
    F->printM(F->min, &register_num, &wait_num, &waiting_time, &withdraw_num);
    //record H1
    for(int i = 0; i < H1->getnum_app() ; i++){
        if(T - 60 <= H1->appointed[i]->t_appointed){
            register_num++;
            int t = T - H1->appointed[i]->gettime() + H1->appointed[i]->t_extra;
            waiting_time += t;
            if(H1->appointed[i]->withdrawflag == 1){
                withdraw_num++;
            }
        }  
    };
    //record H2
    for(int i = 0; i < H2->getnum_app() ; i++){
        if(T - 60 <= H2->appointed[i]->t_appointed){
            register_num++;
            int t = T - H2->appointed[i]->gettime() + H2->appointed[i]->t_extra;
            waiting_time += t;
            if(H2->appointed[i]->withdrawflag == 1){
                withdraw_num++;
            }
        }  
    };
    //record H3
    for(int i = 0; i < H3->getnum_app() ; i++){
        if(T - 60 <= H3->appointed[i]->t_appointed){
            register_num++;
            int t = T - H3->appointed[i]->gettime() + H3->appointed[i]->t_extra;
            waiting_time += t;
            if(H3->appointed[i]->withdrawflag == 1){
                withdraw_num++;
            }
        }  
    };
    for (int i =0; i < H1->num_com; i++ ){
        if(T - 60 <= H1->completed[i]->t_appointed){
            register_num++;
            int t = H1->completed[i]->t_out - H1->completed[i]->gettime() + H1->completed[i]->t_extra;
            waiting_time += t;
            appoint_num++;
        }
    }

    for (int i =0; i < H2->num_com; i++ ){
        if(T - 60 <= H2->completed[i]->t_appointed){
            register_num++;
            int t = H2->completed[i]->t_out - H2->completed[i]->gettime() + H2->completed[i]->t_extra;
            waiting_time += t;
            appoint_num++;
        }
    }

    for (int i =0; i < H3->num_com; i++ ){
        if(T - 60 <= H3->completed[i]->t_appointed){
            register_num++;
            int t = H3->completed[i]->t_out - H3->completed[i]->gettime() + H3->completed[i]->t_extra;
            waiting_time += t;
            appoint_num++;
        }
    }
    cout << "The register number in the last 30 days is:" << register_num << endl;
    cout << "The waiting number in the last 30 days is:" << wait_num << endl;
    cout << "The appointed number in the last 30 days is:" << appoint_num << endl;
    cout << "The average waiting day in the last 30 days is:" << waiting_time/register_num/2 << endl;
    cout << "The withdraw number in the last 30 days is:" << withdraw_num << endl;
};


//***************************************************main**********************************************//

int main()
{
    CountLine("RecordData.csv");
    //Build 3 local queues:
    Localq  Local1(50);
    Localq  Local2(50);
    Localq  Local3(50);

    //Build 1 center:
    FibHeap Center;

    //Build 3 hospitals:
    Hospital H1;
    H1.id = 1;
    H1.setlocation(0,0);
    Hospital H2;
    H2.id = 2;
    H2.setlocation(35,21);
    Hospital H3;
    H3.id = 3;
    H3.setlocation(-37,-45);


    //Simulation starts here
    cout << "Welcome to our system" << endl;
    cout << "Please enter simulating start time (e.g. 20010101 for 2001/01/01)" << endl;
    cin >> t_start ;  //Undo : 如果输入的不符合规定怎么办
    cout << "Please enter how many days you would like to simulate:" << endl;
    cin >> S_T;
    S_T *= 2;
    
    int op;
    do
    {   
        do
        {
            
            cout << "Please choose an operation: " << endl;
            cout << "0: quit" << endl;
            cout << "1: Simulate one half day" << endl;
            cout << "2: Simulate n half days" << endl;
            cout << "3: Update one patient" << endl;
            cout << "4: Withdraw one patient" << endl;
            cout << "5: Get a weekly report: " << endl;
            cout << "6: Get a monthly report: " << endl;
            cin >> op ;
        }
        while ((op < 0) || (op > 6));   //let user choose until operation is valid
        switch(op)
        {   //quit
            case 0: return(0);
            //Simulate one half day
            case 1:
            {
                //1. 读取一个csv里的所有数据到Local里
                int num_reg = rand() % 5 + 1;
                
                int local_q = rand() % 3 + 1;
                
                switch(local_q){
                    case 1:
                        ReadRecord("RecordData.csv", num_reg, &Local1);
                        break;
                    case 2:
                        ReadRecord("RecordData.csv", num_reg, &Local2);
                        break;
                    case 3:
                        ReadRecord("RecordData.csv", num_reg, &Local3);
                        break;
                }
               
                //2. 将Local里所有数据送到center
                Center.addlocal(Center.min, Local1.pop());
                
                Center.addlocal(Center.min, Local2.pop());
                
                Center.addlocal(Center.min, Local3.pop());

                //3. 将center数据送去appointed
                H1.complete(T);
                H2.complete(T);
                H3.complete(T); 

                Appoint(&Center, &H1, &H2, &H3, T);

                //update the half day                
                T ++;   
                break;
            }
            //Simulate n half days
            case 2:
            {
                cout << "Please enter n:" << endl;
                int half;
                cin >> half;
                //for every half day, run in while loop one time
                while( half > 0 ){
                    //1. 读取一个csv里的所有数据到Local里
                    int num_reg = rand() % 5 + 1;
                    cout << "the number is: " << num_reg << endl;
                    int local_q = rand() % 3 + 1;
                    cout << "the local is: " << local_q << endl;
                    switch(local_q){
                        case 1:
                            ReadRecord("RecordData.csv", num_reg, &Local1);
                            break;
                        case 2:
                            ReadRecord("RecordData.csv", num_reg, &Local2);
                            break;
                        case 3:
                            ReadRecord("RecordData.csv", num_reg, &Local3);
                            break;
                    }
                    
                    //2. 将Local里所有数据送到center
                    Center.addlocal(Center.min, Local1.pop());
                    Center.addlocal(Center.min, Local2.pop());
                    Center.addlocal(Center.min, Local3.pop());
                    

                    //3. 将center数据送去appointed
                    H1.complete(T);
                    H2.complete(T);
                    H3.complete(T);
                    Appoint(&Center, &H1, &H2, &H3, T);
                    //update time               
                    T ++;   
                    half--;
                }
                break;
            }
            //3: Update one patient
            case 3:
            {
                //get the patient's id
                cout << "Please enter the id of the patient:" << endl;
                int tempid;
                cin >>tempid;
                int op3;
                //find if he or her is waiting, if is waiting, return the pointer of Record; if not, return NULL 
                Record* node=Center.find(Center.min,tempid);
                if(node==NULL){
                    cout << "The patient is not in queue or has already been appointed." << endl;
                    break;
                }                
               do{
                    cout << "Please choose what you want to update: " << endl;
                    cout << "0: profession";
                    cout << "1: risk level" << endl;
                    cin  >> op3;
                }
                while((op3 < 0) || (op3 > 1));
                switch(op3)
                {
                    case 0:
                    {   
                        cout << "prof1" <<endl;
                        cout << node->getprof() <<endl;
                        cout << "Please enter new profession number (1 to 8):" << endl;
                        int newprof;
                        cin >> newprof;
                        Center.updateprofession(node, newprof);
                        cout << "prof2" <<endl;
                        cout << node->getprof() <<endl;
                        break;
                    }
                    case 1:
                    {
                        cout << "Please enter new risk level (0 to 3):" << endl;
                        int newrisk;
                        cin >> newrisk;
                        Center.updateRisk(node, newrisk);
                        break;
                    }
                }               
                break;
            }
            //Withdraw one patient
            case 4:
            {
                cout << "Please enter the patient's id" << endl;
                int withdraw_id = 0;
                Record* withdraw_record;
                cin >> withdraw_id ;
                withdraw_record = Center.find(Center.min,withdraw_id);
                if(withdraw_record == NULL){
                    for  (int i = 0; i < H1.getnum_app(); i++){
                        if (H1.appointed[i]->getid() == withdraw_id){
                            withdraw_record = H1.appointed[i];
                            break;
                        }
                    }
                    if (withdraw_record == NULL){
                        for  (int i = 0; i < H2.getnum_app(); i++){
                            if (H2.appointed[i]->getid() == withdraw_id){
                                withdraw_record = H2.appointed[i];
                                break;
                            }
                        }
                    }
                    if (withdraw_record == NULL){
                        for  (int i = 0; i < H3.getnum_app(); i++){
                            if (H3.appointed[i]->getid() == withdraw_id){
                                withdraw_record = H3.appointed[i];
                                break;
                            }
                        }
                    }

                }
                if (withdraw_record == NULL){
                    cout << "This person has not registered or has been treated." << endl;
                    break;
                }          
                withdraw(withdraw_record, &Center, &H1, &H2, &H3);
                cout<<"withdraw5"<<endl;
                break;
            }
            case 5:
            {
                if(T <= 13){
                    cout << "No weekly report now" << endl;
                };
                cout << "WeeklyReport.csv has been created." << endl;
                WeeklyReport(&Center, &H1, &H2, &H3);
                break;
            }
            case 6:
            {
                if(T <= 59){
                    cout << "No monthly report now" << endl;
                };
                cout << "The monthly report are as followed:" << endl;
                MonthlyReport(&Center, &H1, &H2, &H3);
                break;
            }               
            //default: return(0);
        }
    }
    while (op != 0 && T <= S_T);
    cout << "Simulation ends successfully!"<<endl;
    return 0;
};

