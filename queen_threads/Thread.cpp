#include <iostream>
#include "Thread.h"
#include "ThreadPool.h"
#include "Queen.h"

using namespace std;


const unsigned int Thread::MaxLength = 30;

bool Thread::isStarted = false;
std::mutex Thread::mutex;
std::condition_variable Thread::condition;

Thread::Thread(ThreadPool* pool,int QueueCnt,int id)
    :pool(pool),
    id(id),
    thread(new std::thread(std::bind(&Thread::run,this))),
    queueCnt(QueueCnt),
    resultCnt(0)
{
    //thread->join();
}

Thread::~Thread()
{

}


void Thread::startAllThread()
{
    //���������߳�
    {
        unique_lock<std::mutex> lock(mutex);
        isStarted = true;
        condition.notify_all();
    }
}

void Thread::join()
{
    thread->join();
}

void Thread::run()
{
    //�����ȴ�����
    {
        unique_lock<std::mutex> lock(mutex);
        if(!isStarted)
        {
            condition.wait(lock);
        }
    }
    resultCnt = 0;
    for(int i=0;i<queueCnt;i++)
    {
        if((pool->getThreadCount()) && i%pool->getThreadCount() == id)
        {
            int resultRow[MaxLength];
            //��һ���ʺ�λ��
            resultRow[0] = i;
            Queen queen(queueCnt,resultRow);
            //�ӵڶ��п�ʼ���㣬0Ϊ��һ�С�
            queen.solve(1);
            resultCnt += queen.getResultCnt();
        }
    }
    pool->completOneThread();

}

void Thread::sleepSeconds(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}


std::thread::id Thread::getNowThreadId()
{
    return std::this_thread::get_id();
}


int Thread::getResultCnt()
{
    return resultCnt;
}
