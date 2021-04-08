//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//
//  queue.cpp
//  Assignment 1
//
//  Created by Jin Yirou on 2021/4/4.
//

#include "MAS.h"
#include <iostream>
#include <ctime>
#include <bits/stdc++.h>


int Record::getid(void)
{
    return identification;
}


char *Record::getname(void)
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

char *Record::getWeChat(void)
{
    return WeChat;
}

char *Record::getemail(void)
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

time_t Record::gettime(void)
{
    return timestamp;
}


void Record::setid(int number)
{
    identification = number;
    return;
}

void Record::setname(char *string)
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

void Record::setWeChat(char *string)
{
    WeChat = string;
    return ;
}

void Record::setemail(char *string)
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

void Record::setrisk(int number)
{
    riskstatus = number;
    return ;
}

void Record::settime(time_t t)
{
    timestamp = t;
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





Record *Localq::pop()
{
    int a = first+1;
    first = last;
    return &array[a];
}

void Localq::append(Record *record)
{
    last++;
    record->settime(time(0));
    record->setagegroup();
    if (first == last - 1)
    {
        record->setleft(record);
        record->setright(record);
    } else {
        record->setleft(array[last-1]);
        record->setright(array[first+1]);
        (array[last-1])->setright(record);
        (array[first+1])->setleft(record);
    }
    
    if (recordnumber == maxsize) {
        allocate();
    }
    
    recordnumber++;
    array[last] = record;
    std::cout << "(record->left->right)->getid()" << std::endl;
    std::cout << (record->left->right)->getid() << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    //std::cout << record->getid() << std::endl;
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


#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
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
    result=m;
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

    delete m;
    return result;
}


void FibHeap::addlocal(Record *a,Record *b)
{
    int counter = 1;
    std::cout << "b->getid()" << std::endl;
    std::cout << b->getid() << std::endl;
    Record* j = b->left;
    std::cout << "j->getid()" << std::endl;
    std::cout << j->getid() << std::endl;
    while(j!=b){
        counter++;
        b=b->right;
        std::cout << b->getid() << std::endl;
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
        x = min;                // 取出堆中的最小树(最小节点所在的树)
        d = x->degree;                    // 获取最小树的度数
        // cons[d] != NULL，意味着有两棵树(x和y)的"度数"相同。
        while (cons[d] != NULL)
        {
            y = cons[d];                // y是"与x的度数相同的树"
            if (compare(x,y)==1)        // 保证x的键值比y小
                std::swap(x, y);

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












#include <iostream>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <typeinfo>

using namespace std;

int main()
{
    
    Record R1;
    R1.setid(1);
    R1.setadd(1,1);
    R1.setbirth(20010630);
    R1.setprof(1);
    R1.setrisk(0);
    Record R2;
    R2.setid(2);
    R2.setadd(1,0);
    R2.setbirth(20010630);
    R2.setprof(2);
    R2.setrisk(0);
    Record R3;
    R3.setid(3);
    R3.setadd(0,1);
    R3.setbirth(20100630);
    R3.setprof(1);
    R3.setrisk(0);
    Localq  Local1;
    Local1.append(&R1);
    Local1.append(&R2);
    Local1.append(&R3);
    std::cout << (R2.right)->getid() << std::endl;

    FibHeap center1;
    //center1.addlocal(center1.min,Local1.pop());
    std::cout << "Min is :" << std::endl;
    std::cout<< (center1.min)->getid()<< endl;
}

