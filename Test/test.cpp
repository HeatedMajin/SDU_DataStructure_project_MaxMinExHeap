#include<iostream>
using namespace std;

#include "biqueue.h"
int main(){
	BiPrioQueue<int> bqueue(50);
	cout << "�����Ԫ��1~39" << endl;
	for (int index = 1; index < 40; index++){
		bqueue.inQueue(index);
		bqueue.output();
	}
	cout << "1~39����СԪ�س���" << endl;
	for (int index = 1; index < 40; index++){
		cout << "ȡ����СԪ�أ�"<<bqueue.deQueue_min()<<endl;
		bqueue.output();
	}

	BiPrioQueue<int> bbqueue(50);
	cout << "���²���Ԫ��1~39" << endl;
	for (int index = 1; index < 40; index++){
		bbqueue.inQueue(index);
	}
	cout << "1~39�����Ԫ�س���" << endl;
	for (int index = 1; index < 40; index++){
		cout<<"ȡ�����Ԫ��"<<bbqueue.deQueue_max()<<endl;
		bbqueue.output();
	}
	system("pause");
	return 0;
}