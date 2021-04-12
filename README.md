# RQR Medical Treatment System

## CS225 Pramming Assignment 1

### Copyright: Baoyi He, Xiao Wang, Xiaoshan Wu, Yirou Jin

### 2021/4/11

## Description

This is a registration, queueing and reporting system for mass medical treatment (such as vaccination)
implemented in C++. We provide RQR.cpp, RQR.h and an input file RecordData.csv, which contains 128
records. When you run RQR.cpp, the system require you to set an 8 bit simulate start date (like 20210410)
and a simulate number of days. After that, you can use our six functions by inputing integer:

0: quit
1: Simulate one half day
2: Simulate n half days
3: Update one patient
4: Withdraw one patient
5: Get a weekly report
6: Get a monthly report

## Interpretion of Code

We have 3 hospital and 1 center in total. Each patient have 3 status: waiting, appointed and treated.

For function 1, we use T as a counter of half days, random the number of patients and which hospital they'd go.
The patients from each hospital will be sent to center and appointed by priority. (Priority: High risk patients always have lowest priority, medium risk patients will be appointed 2 weeks later, no/low risk patients' priority is based on profession, agegroup and waiting time in order).

Function 2 is n repeatation of function 1.

Function 5 can only be used after at least 14 half days. When using function 4, a WeeklyReport.csv will be genertated containing the ID, Status, RiskLevel, Profession, AgeGroup and WaitingTime(in half day). You can change the file's name if you want to reserve more than one week's report, but the new generated file would always named WeeklyReport.csv.

Function 6 can only be used after at least 60 half days. When using function 6, the register number, the waiting number, the appointed number, the average waiting day and the withdraw number in the last 30 days will appear in the ternimal.
