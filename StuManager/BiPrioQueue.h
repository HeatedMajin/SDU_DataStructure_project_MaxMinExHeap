/********************************************************************
*            BiPrioQueue.h
*
*  2017��05��09�� ����2
*  Copyright  2017  majin
*  Email:666@majin.xyz
*********************************************************************/

//#include"MinMaxExHeap.h"
#include"BiHeap.h"
template<class T>
class BiPrioQueue{
public:
	BiPrioQueue(int max = 40){
		dheap = new BiHeap<T>(max);
	};
	void inQueue(T data);//�������
	T deQueue_max();//���Ԫ�س�����
	T deQueue_min();//��СԪ�س�����
	T getMax();//��ȡ���Ԫ�أ����ǲ�������
	T getMin();//��ȡ��СԪ�أ����ǲ�������
	bool isEmpty(){//���ض����ǲ��ǿ�
		return dheap && dheap->isEmpty();
	}

	int GetCurSize(){//�õ���ǰ���еĴ�С
		return dheap->GetCurSzie();
	}
	T* GetAll(){
		return dheap->GetAll();
	}
private:
	//MinMaxExHeap<T> *dheap;
	BiHeap<T> *dheap;
};


template<class T>
void BiPrioQueue<T>::inQueue(T data){//�������
	dheap->Insert(data);
}
template<class T>
T BiPrioQueue<T>::deQueue_min(){//��С��Ԫ�س�����
	return dheap->Extract_min();
}

template<class T>
T BiPrioQueue<T>::deQueue_max(){//��С��Ԫ�س�����
	return dheap->Extract_max();
}
template<class T>
T BiPrioQueue<T>::getMax(){//��ȡ��СԪ��
	return dheap->getMax();
}

template<class T>
T BiPrioQueue<T>::getMin(){//��ȡ���Ԫ��
	return dheap->getMin();
}