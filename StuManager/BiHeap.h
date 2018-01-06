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
//插入数据
template<class T>
void BiHeap<T>::Insert(T t){
	++curSize;
	int h = (int)ceil((log(curSize + 1) / log(2)));
	int tag = curSize >> (h - 2);
	int i = curSize;// 新节点要插入到的位置
	if (tag == 2){
		//插在左子树上,左子树小根堆
		//在插之前，先看看是不是比右树的所有节点都小
		int rmp = RightMinPosi();
		if (curSize != 2 && arr[rmp]<t){
			//把右边最小的节点放到左边的树上,直接放下面
			arr[curSize] = arr[rmp];

			//新节点放到右边的树上，需要插入
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
		//插在右子树上，右树大根堆
		//插入前，和左最大比较
		int lmp = LeftMaxPosi();
		if (arr[lmp]>t){
			//把左边最大的节点放到右边的树上,直接放下面
			arr[curSize] = arr[lmp];

			//新节点放到左边的树上，需要插入
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

//删除最小数据
template<class T>
T BiHeap<T>::Extract_min(){
	if (curSize <= 1){
		throw new Null();
	}
	if (curSize == 2){
		return arr[curSize--];
	}
	//下面右树一定存在
	T result = arr[2];

	//判断节点的左右位置
	int h = (int)ceil((log(curSize + 1) / log(2)));
	int tag = curSize >> (h - 2);
	//重新对最后一个进行定位
	//当最后一个在左树上，按照以前的规矩
	if (tag == 2){
		T t = arr[curSize--];
		int i = 2;
		int ci = 2 * i;//记录i的孩子
		while (ci <= curSize){
			//ci指向最小的孩子
			if (ci<curSize && arr[ci]>arr[ci + 1]){
				++ci;
			}

			//t可不可以在i处
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
	//当最后一个在右树上，拿出最小的一个，把最后一个放上，再把最小的一个放到左树定上开始重构
	else if (tag == 3){
		int rmp = RightMinPosi();
		T t = arr[rmp];
		arr[rmp] = arr[curSize--];

		int i = 2;
		int ci = 2 * i;//记录i的孩子
		while (ci <= curSize){
			//ci指向最小的孩子
			if (ci<curSize && arr[ci]>arr[ci + 1]){
				++ci;
			}

			//t可不可以在i处
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

//删除最大数据
template<class T>
T BiHeap<T>::Extract_max(){
	if (curSize <= 1){
		throw new Null();
	}
	if (curSize == 2){
		return arr[curSize--];
	}
	//下面右树一定存在
	T result = arr[3];

	//判断节点的左右位置
	int h = (int)ceil((log(curSize + 1) / log(2)));
	int tag = curSize >> (h - 2);
	//重新对最后一个进行定位
	//当最后一个在右树上，按照以前的规矩
	if (tag == 3){
		T t = arr[curSize--];
		int i = 3;
		int ci = 2 * i;//记录i的孩子
		while (ci <= curSize){
			//ci指向最大的孩子
			if (ci<curSize && arr[ci]<arr[ci + 1]){
				++ci;
			}

			//t可不可以在i处
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
	//当最后一个在左树上，拿出最大的一个，把最后一个放上，再把最大的一个放到右树定上开始重构
	else if (tag == 2){
		int lmp = LeftMaxPosi();
		T t = arr[lmp];
		arr[lmp] = arr[curSize--];

		int i = 3;
		int ci = 2 * i;//记录i的孩子
		while (ci <= curSize){
			//ci指向最大的孩子
			if (ci<curSize && arr[ci]<arr[ci + 1]){
				++ci;
			}

			//t可不可以在i处
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


//查找右子树中的最小节点的位置,简化右子树最底层的最小节点
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

//查找左子树中的最大节点的位置
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
		//右树一定存在,返回右树的顶部节点
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

