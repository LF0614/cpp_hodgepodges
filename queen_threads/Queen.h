#ifndef QUEEN_H
#define QUEEN_H

class Queen
{
public:
    Queen(int len,int* result);
    //���������
    void solve(int col);
    //��ȡ�����
    int getResultCnt();
private:
    //�жϻʺ�λ���Ƿ�Ϸ�
    bool isEffective(int row,int col);
    //Ҫ���N�ʺ����ⳤ��
    static int length;
    //�ж��ٽ�
    int resultCnt;
    //�洢�ⷨ������ָ�루һ���߳�ʹ��һ�黺�棩
    int* resultRow;
};

#endif // QUEUE_H
