#include <iostream>
#include <chrono>
#include <ratio>
#include <condition_variable>

#include "ThreadPool.h"
#include "Queen.h"

using namespace std;
using namespace std::chrono;

int main(void)
{
    int len = 15;
    cout<<"solve queen length: "<<len<<endl;

#if    0
    /*
    ���̵߳ݹ�N�ʺ�15���ʺ��Լ28��
    */

    //��ó�ʼʱ�䡣
    auto timePoint1 = time_point_cast<duration<int,std::ratio<1>>>(system_clock::now());
    int rst[30];
    //�����ʺ���
    Queen queen(len,rst);
    //�ӵ�0�е�0�п�ʼ�ݹ�
    queen.solve(0);
    //��ӡ������
    cout<<queen.getResultCnt()<<endl;
    //��ý���ʱ��
    auto timePoint2 = time_point_cast<duration<int,std::ratio<1>>>(system_clock::now());
    cout<<timePoint2.time_since_epoch().count()-timePoint1.time_since_epoch().count()<<endl;
#else

    /*
    ���̵߳ݹ�N�ʺ�15�ʺ�Լ8��
    */
    
    //��ȡʱ��
    auto timePoint1 = time_point_cast<duration<int, std::ratio<1>>>(system_clock::now());
    //�����̳߳�
    ThreadPool pool;
    //���ûʺ����
    pool.setQueueCnt(len);
    //�����̸߳������������̡߳�
    pool.runAllThread(4);

    pool.join();

    auto timePoint2 = time_point_cast<duration<int, std::ratio<1>>>(system_clock::now());
    cout << timePoint2.time_since_epoch().count() - timePoint1.time_since_epoch().count() << endl;
#endif

    system("pause");
    return 0;
}
