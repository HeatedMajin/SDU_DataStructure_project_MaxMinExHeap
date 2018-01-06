#include<iostream>
using namespace std;

#include "biqueue.h"
int main(){
	BiPrioQueue<int> bqueue(50);
	cout << "插入从元素1~39" << endl;
	for (int index = 1; index < 40; index++){
		bqueue.inQueue(index);
		bqueue.output();
	}
	cout << "1~39以最小元素出堆" << endl;
	for (int index = 1; index < 40; index++){
		cout << "取出最小元素："<<bqueue.deQueue_min()<<endl;
		bqueue.output();
	}

	BiPrioQueue<int> bbqueue(50);
	cout << "重新插入元素1~39" << endl;
	for (int index = 1; index < 40; index++){
		bbqueue.inQueue(index);
	}
	cout << "1~39以最大元素出堆" << endl;
	for (int index = 1; index < 40; index++){
		cout<<"取出最大元素"<<bbqueue.deQueue_max()<<endl;
		bbqueue.output();
	}
	system("pause");
	return 0;
}