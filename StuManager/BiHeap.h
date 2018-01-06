#include<iostream>
#include <math.h>
#include"excp.h"
using namespace std;
template <class T>
class BiHeap{
public:
	BiHeap(int max = 40);
	void Insert(T t);
	T Extract_min();
	T Extract_max();
	T getMax();
	T getMin();
	bool isEmpty(){
		if (curSize < 2){
			return true;
		}
		return false;
	}
	void output(){
		for (register int i = 2; i <= curSize; ++i){
			cout << arr[i] << endl;
		}
	}
	int RightMinPosi();
	int LeftMaxPosi();
	int GetCurSzie(){
		return curSize-1;
	}
	T* GetAll(){
		return arr;
	}
private:
	T *arr;
	int maxSize;
	int curSize;
};
template<class T>
BiHeap<T>::BiHeap(int max = 40){
	arr = new T[max + 2];
	maxSize = max;
	curSize = 1;
}
//��������
template<class T>
void BiHeap<T>::Insert(T t){
	++curSize;
	int h = (int)ceil((log(curSize + 1) / log(2)));
	int tag = curSize >> (h - 2);
	int i = curSize;// �½ڵ�Ҫ���뵽��λ��
	if (tag == 2){
		//������������,������С����
		//�ڲ�֮ǰ���ȿ����ǲ��Ǳ����������нڵ㶼С
		int rmp = RightMinPosi();
		if (curSize != 2 && arr[rmp]<t){
			//���ұ���С�Ľڵ�ŵ���ߵ�����,ֱ�ӷ�����
			arr[curSize] = arr[rmp];

			//�½ڵ�ŵ��ұߵ����ϣ���Ҫ����
			i = rmp;
			while (t>arr[i / 2] && i != 3){
				arr[i] = arr[i / 2];
				i = i / 2;
			}
		}
		else{
			while (t < arr[i / 2] && i != 2){
				arr[i] = arr[i / 2];
				i = i / 2;
			}

		}
	}
	else if (tag == 3){
		//�����������ϣ����������
		//����ǰ���������Ƚ�
		int lmp = LeftMaxPosi();
		if (arr[lmp]>t){
			//��������Ľڵ�ŵ��ұߵ�����,ֱ�ӷ�����
			arr[curSize] = arr[lmp];

			//�½ڵ�ŵ���ߵ����ϣ���Ҫ����
			i = lmp;
			while (t < arr[i / 2] && i != 2){
				arr[i] = arr[i / 2];
				i = i / 2;
			}
		}
		else{
			while (t>arr[i / 2] && i != 3){
				arr[i] = arr[i / 2];
				i = i / 2;
			}
		}
	}
	else {
		cout << "error" << endl;
		return;
	}
	arr[i] = t;
}

//ɾ����С����
template<class T>
T BiHeap<T>::Extract_min(){
	if (curSize <= 1){
		throw new Null();
	}
	if (curSize == 2){
		return arr[curSize--];
	}
	//��������һ������
	T result = arr[2];

	//�жϽڵ������λ��
	int h = (int)ceil((log(curSize + 1) / log(2)));
	int tag = curSize >> (h - 2);
	//���¶����һ�����ж�λ
	//�����һ���������ϣ�������ǰ�Ĺ��
	if (tag == 2){
		T t = arr[curSize--];
		int i = 2;
		int ci = 2 * i;//��¼i�ĺ���
		while (ci <= curSize){
			//ciָ����С�ĺ���
			if (ci<curSize && arr[ci]>arr[ci + 1]){
				++ci;
			}

			//t�ɲ�������i��
			if (t<arr[ci]){//yes
				break;
			}
			else{//no
				arr[i] = arr[ci];
				i = ci;
				ci = i * 2;
			}
		}
		arr[i] = t;

	}
	//�����һ���������ϣ��ó���С��һ���������һ�����ϣ��ٰ���С��һ���ŵ��������Ͽ�ʼ�ع�
	else if (tag == 3){
		int rmp = RightMinPosi();
		T t = arr[rmp];
		arr[rmp] = arr[curSize--];

		int i = 2;
		int ci = 2 * i;//��¼i�ĺ���
		while (ci <= curSize){
			//ciָ����С�ĺ���
			if (ci<curSize && arr[ci]>arr[ci + 1]){
				++ci;
			}

			//t�ɲ�������i��
			if (t<arr[ci]){//yes
				break;
			}
			else{//no
				arr[i] = arr[ci];
				i = ci;
				ci = i * 2;
			}
		}
		arr[i] = t;

	}
	else {
		cout << "error" << endl;
	}

	return result;
}

//ɾ���������
template<class T>
T BiHeap<T>::Extract_max(){
	if (curSize <= 1){
		throw new Null();
	}
	if (curSize == 2){
		return arr[curSize--];
	}
	//��������һ������
	T result = arr[3];

	//�жϽڵ������λ��
	int h = (int)ceil((log(curSize + 1) / log(2)));
	int tag = curSize >> (h - 2);
	//���¶����һ�����ж�λ
	//�����һ���������ϣ�������ǰ�Ĺ��
	if (tag == 3){
		T t = arr[curSize--];
		int i = 3;
		int ci = 2 * i;//��¼i�ĺ���
		while (ci <= curSize){
			//ciָ�����ĺ���
			if (ci<curSize && arr[ci]<arr[ci + 1]){
				++ci;
			}

			//t�ɲ�������i��
			if (t>arr[ci]){//yes
				break;
			}
			else{//no
				arr[i] = arr[ci];
				i = ci;
				ci = i * 2;
			}
		}
		arr[i] = t;

	}
	//�����һ���������ϣ��ó�����һ���������һ�����ϣ��ٰ�����һ���ŵ��������Ͽ�ʼ�ع�
	else if (tag == 2){
		int lmp = LeftMaxPosi();
		T t = arr[lmp];
		arr[lmp] = arr[curSize--];

		int i = 3;
		int ci = 2 * i;//��¼i�ĺ���
		while (ci <= curSize){
			//ciָ�����ĺ���
			if (ci<curSize && arr[ci]<arr[ci + 1]){
				++ci;
			}

			//t�ɲ�������i��
			if (t>arr[ci]){//yes
				break;
			}
			else{//no
				arr[i] = arr[ci];
				i = ci;
				ci = i * 2;
			}
		}
		arr[i] = t;

	}
	else {
		cout << "error" << endl;
	}

	return result;
}


//�����������е���С�ڵ��λ��,����������ײ����С�ڵ�
template<class T>
int BiHeap<T>::RightMinPosi(){
	int h = (int)ceil((log(curSize + 1) / log(2)));
	int tag = curSize >> (h - 2);
	int f = curSize / 2;
	int start;
	int end;
	int minPosi;
	if (tag == 3){
		f = curSize;
		start = 3 * (1 << (int)ceil((log(f + 1) / log(2)))) / 4 - 1;
		end = (1 << (int)ceil((log(f + 1) / log(2)))) - 1;
		minPosi = start + 1;
		for (register int i = start + 1; i <= end && i <= curSize; ++i){
			if (arr[minPosi] > arr[i]){
				minPosi = i;
			}
		}
	}
	else if (tag == 2){
		start = 3 * (1 << (int)ceil((log(f + 1) / log(2)))) / 4 - 1;
		end = (1 << (int)ceil((log(f + 1) / log(2)))) - 1;
		minPosi = start + 1;
		for (register int i = start + 1; i <= end; ++i){
			if (arr[minPosi] > arr[i]){
				minPosi = i;
			}
		}
	}
	return minPosi;
}

//�����������е����ڵ��λ��
template<class T>
int BiHeap<T>::LeftMaxPosi(){

	int start = (1 << (int)(ceil(log(curSize + 1) / log(2)) - 1)) - 1;
	int end = 3 * (1 << (int)(ceil(log(curSize + 1) / log(2)))) / 4 - 1;
	int maxPosi = start + 1;
	for (register int i = start + 1; i <= end && i <= curSize; ++i){
		if (arr[maxPosi]<arr[i]){
			maxPosi = i;
		}
	}
	return maxPosi;
}

template<class T>
T BiHeap<T>::getMax(){
	if (curSize <= 1){
		throw new Null();
	}
	else if (curSize < 3){
		return arr[curSize];
	}
	else{
		//����һ������,���������Ķ����ڵ�
		return arr[3];
	}
}

template<class T>
T BiHeap<T>::getMin(){
	if (curSize <= 1){
		throw new Null();
	}
	return arr[2];
}

