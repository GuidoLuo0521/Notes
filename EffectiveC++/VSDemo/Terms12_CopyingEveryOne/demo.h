#pragma once

#include "../Common/common.h"

class IObject
{
    virtual void printObject() = 0;
   
};

class Customer : public IObject
{
public:
    Customer(const string& name)
        : m_name(name)
    {
    }

    Customer(const Customer& rhs)
        : m_name(rhs.m_name)
    {
        LogCall(__FUNCTION__);
    }

    Customer& operator= (const Customer& rhs)
    {
        m_name = rhs.m_name;
        LogCall(__FUNCTION__);

        return *this;
    }

    virtual void printObject()
    {
        cout << __FUNCTION__ << " " << m_name;
        PrintNewLine();
    }

    void setName(const string& name)
    {
        m_name = name;
    }


private:
    std::string m_name;
};




//*****************************************************

class PriorityCustomer : public Customer
{
public:
    PriorityCustomer(const int proprity)
        : Customer("Priority")
        , m_priority(proprity)
    {
    }

    PriorityCustomer(const PriorityCustomer& rhs)
        : Customer(rhs)
        , m_priority(rhs.m_priority)
    {
        LogCall(__FUNCTION__);
    }

#if  false
    PriorityCustomer& operator= (const PriorityCustomer& rhs)
    {

        m_priority = rhs.m_priority;
        logCall(__FUNCTION__);

        return *this;
    }

#else
    PriorityCustomer& operator= (const PriorityCustomer& rhs)
    {

        Customer::operator=(rhs);
        m_priority = rhs.m_priority;
        LogCall(__FUNCTION__);

        return *this;
    }

#endif //  false

    
    virtual void printObject()
    {
        Customer::printObject();
        printPriority();
    }

    void printPriority()
    {
        cout << __FUNCTION__ << " " << m_priority;
        PrintNewLine();
    }


private:
    int m_priority;

};




