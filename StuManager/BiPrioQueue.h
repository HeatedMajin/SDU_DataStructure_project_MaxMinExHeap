/********************************************************************
*            BiPrioQueue.h
*
*  2017年05月09日 星期2
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
	void inQueue(T data);//进入队列
	T deQueue_max();//最大元素出队列
	T deQueue_min();//最小元素出队列
	T getMax();//获取最大元素，但是不出队列
	T getMin();//获取最小元素，但是不出队列
	bool isEmpty(){//返回队列是不是空
		return dheap && dheap->isEmpty();
	}

	int GetCurSize(){//得到当前队列的大小
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
void BiPrioQueue<T>::inQueue(T data){//进入队列
	dheap->Insert(data);
}
template<class T>
T BiPrioQueue<T>::deQueue_min(){//最小的元素出队列
	return dheap->Extract_min();
}

template<class T>
T BiPrioQueue<T>::deQueue_max(){//最小的元素出队列
	return dheap->Extract_max();
}
template<class T>
T BiPrioQueue<T>::getMax(){//获取最小元素
	return dheap->getMax();
}

template<class T>
T BiPrioQueue<T>::getMin(){//获取最大元素
	return dheap->getMin();
}