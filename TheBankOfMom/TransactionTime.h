// Name        : TransactionTime.h
// Author      : Alyssa Risius
// Email	   : alrisius1@dmacc.edu
// Date        : 12/10/2024

#ifndef TRANSACTIONTIME_H_
#define TRANSACTIONTIME_H_

#include <string>
#include <sstream>
#include <ctime>
using namespace std;

struct TransactionTime
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    // method to set current time
    void SetCurrentTime() {
        time_t now = time(0);
        tm localTime;

        localtime_s(&localTime, &now);

        year = localTime.tm_year + 1900;
        month = localTime.tm_mon + 1;
        day = localTime.tm_mday;
        hour = localTime.tm_hour;
        minute = localTime.tm_min;
        second = localTime.tm_sec;
    }

    // method to put date and time into a readable string
    string ToString() const {
        stringstream ss;
        ss << year << "-"
            << (month < 10 ? "0" : "") << month << "-"
            << (day < 10 ? "0" : "") << day << " "
            << (hour < 10 ? "0" : "") << hour << ":"
            << (minute < 10 ? "0" : "") << minute << ":"
            << (second < 10 ? "0" : "") << second;
        return ss.str();
    }
};

#endif
