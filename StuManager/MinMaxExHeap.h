/********************************************************************
*            MinMaxExHeap.h
*
*  2017年05月09日 星期2
*  Copyright  2017  majin
*  Email:666@majin.xyz
*********************************************************************/
#include"excp.h"
#include<iostream>
#define MAX 0x7FFFFFFF
using namespace std;
template <class T>
class MinMaxExHeap{
public:
	MinMaxExHeap(int max = 40);//初始化一棵交替树
	void Insert(T data);//插入
	T Extract_max();//删除最大元素
	T Extract_min();//删除最小元素
	bool isEmpty(){
		if (currentSize<1){
			return true;
		}
		return false;
	}
	int GetCurSzie(){//得到当前队列的大小
		return currentSize;
	}
	void output(){//便与测试，输出数组
		for (int i = 1; i <= currentSize; i++){
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	T* GetAll(){
		return arr;
	}
private:
	int findMinPosition(int i);//查找第i个节点下面的最小节点，返回节点的位置
	int findMaxPosition(int i);//查找第i个节点下面最大的节点，返回节点的位置
	T *arr;
	int maxSize;
	int currentSize;
};
template<class T>
MinMaxExHeap<T>::MinMaxExHeap(int max = 40){//初始化一棵交替树
	maxSize = max;
	currentSize = 0;
	arr = new T[max + 1];
	arr[0] = T(MAX);
}
template<class T>
void MinMaxExHeap<T>::Insert(T data){//插入

	if (currentSize == maxSize){//堆满了
		throw new OutofBounds();
	}
	currentSize++;
	if (currentSize == 1){//空堆插入
		arr[1] = data;
		return;
	}


	int i = currentSize;
	//判断父亲节点所在的类型
	//得到父节点的层数，判断层数的奇偶
	int h = (int)ceil((log((i / 2) + 1) / log(2)));
	bool f = false;//f为true代表大根
	if (h % 2 == 0){
		f = true;
	}
	if (f && data>arr[i / 2]){//大根层的父亲，data比父亲大,他要和大根层节点比较大小，决定是否上移
		arr[i] = arr[i / 2];
		i = i / 2;
		while ((i != 2 && i != 3) && data > arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else if (f && data <= arr[i / 2]){//大根层的父亲，data比父亲小,他要和小跟层的节点比较大小
		if (data > arr[i / 4]){//若大于小根层的爷爷，那么他放到原位置
			arr[i] = data;
		}
		else{//若小于爷爷，还要上比
			while (i != 1 && data < arr[i / 4]){
				arr[i] = arr[i / 4];
				i = i / 4;
			}
			arr[i] = data;
		}
	}
	else if (!f && data < arr[i / 2]){//小根层的父亲，data小于父亲

		arr[i] = arr[i / 2];
		i = i / 2;
		while (i != 1 && data< arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else {//小根层的父亲，data大于父亲
		if (data < arr[i / 4]){//若小于大根层的爷爷，那么他放到原位置
			arr[i] = data;
		}
		else{//若大于爷爷，还要上比
			while (i != 2 && i != 3 && data > arr[i / 4]){
				arr[i] = arr[i / 4];
				i = i / 4;
			}
			arr[i] = data;
		}
	}
}

template<class T>
T MinMaxExHeap<T>::Extract_max(){//删除最大元素
	if (currentSize == 0){//返回空异常
		throw new Null();
	}
	if (currentSize == 1 || currentSize == 2){//只有一个元素或两个元素
		return arr[currentSize--];
	}

	//有三个以上的元素时
	T result = arr[2] > arr[3] ? arr[2] : arr[3];//最大元素出现在后第二层之中
	int i = arr[2] > arr[3] ? 2 : 3;
	T data = arr[currentSize--];//为最后一个重新分配位置

	while ((int)ceil((log((i)+1) / log(2))) < (int)ceil((log((currentSize)+1) / log(2)))){//到最后一层就停下
		int maxPosition = findMaxPosition(i);//查找他的孩子中的最大节点
		if (maxPosition == 0){
			break;
		}
		if (data>arr[maxPosition]){
			break;
		}
		arr[i] = arr[maxPosition];
		i = maxPosition;
	}


	//判断要插入位置的父亲是大根层还是小根层
	int h = (int)ceil((log((i / 2) + 1) / log(2)));
	bool f = false;//f为true代表大根
	if (h % 2 == 0){
		f = true;
	}

	if (f && data > arr[i / 2]){//大根层的父亲，data比父亲大,他要和大根层节点比较大小，决定是否上移
		arr[i] = arr[i / 2];
		i = i / 2;
		while ((i != 2 && i != 3) && data > arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else if (f && data <= arr[i / 2]){//大根层的父亲，data比父亲小,他要和小跟层的节点比较大小
		if (data > arr[i / 4]){//若大于小根层的爷爷，那么他放到原位置
			arr[i] = data;
		}
		else{//若小于爷爷，还要上比
			while (i != 1 && data < arr[i / 4]){
				arr[i] = arr[i / 4];
				i = i / 4;
			}
			arr[i] = data;
		}
	}
	else if (!f && data < arr[i / 2]){//小根层的父亲，data小于父亲

		arr[i] = arr[i / 2];
		i = i / 2;
		while (i != 1 && data< arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else {//小根层的父亲，data大于父亲
		if (data < arr[i / 4]){//若小于大根层的爷爷，那么他放到原位置
			arr[i] = data;
		}
		else{//若大于爷爷，还要上比
			while (i != 2 && i != 3 && data > arr[i / 4]){
				arr[i] = arr[i / 4];
				i = i / 4;
			}
			arr[i] = data;
		}
	}
	arr[i] = data;
	return result;
}
template<class T>
T MinMaxExHeap<T>::Extract_min(){//删除最小元素
	if (currentSize == 0){//返回空异常
		throw new Null();
	}
	T result = arr[1];//arr[1]就是最小
	if (currentSize == 1){
		currentSize--;
		return result;
	}
	T data = arr[currentSize--];//为最后一个重新分配位置
	int i = 1;
	while ((int)ceil((log((i)+1) / log(2))) < (int)ceil((log((currentSize)+1) / log(2)))){//到最后一层就停下
		int position = findMinPosition(i);
		if (position == 0){
			break;
		}
		if (data < arr[position]){
			break;
		}
		arr[i] = arr[position];
		i = position;
	}

	//判断要出入位置的父亲是大根层还是小根层
	int h = (int)ceil((log((i / 2) + 1) / log(2)));
	bool f = false;//f为true代表大根
	if (h % 2 == 0){
		f = true;
	}

	if (f && data > arr[i / 2]){//大根层的父亲，data比父亲大,他要和大根层节点比较大小，决定是否上移
		arr[i] = arr[i / 2];
		i = i / 2;
		while ((i != 2 && i != 3) && data > arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else if (f && data <= arr[i / 2]){//大根层的父亲，data比父亲小,他要和小跟层的节点比较大小
		if (data > arr[i / 4]){//若大于小根层的爷爷，那么他放到原位置
			arr[i] = data;
		}
		else{//若小于爷爷，还要上比
			while (i != 1 && data < arr[i / 4]){
				arr[i] = arr[i / 4];
				i = i / 4;
			}
			arr[i] = data;
		}
	}
	else if (!f && data < arr[i / 2]){//小根层的父亲，data小于父亲

		arr[i] = arr[i / 2];
		i = i / 2;
		while (i != 1 && data< arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else {//小根层的父亲，data大于父亲
		if (data < arr[i / 4]){//若小于大根层的爷爷，那么他放到原位置
			arr[i] = data;
		}
		else{//若大于爷爷，还要上比
			while (i != 2 && i != 3 && data > arr[i / 4]){
				arr[i] = arr[i / 4];
				i = i / 4;
			}
			arr[i] = data;
		}
	}

	return result;
}


template<class T>
int MinMaxExHeap<T>::findMinPosition(int i){
	if (2 * i > currentSize){//没有下面的节点了
		return 0;
	}
	else if (2 * i <= currentSize && 2 * i + 1 > currentSize){//只有左孩子
		return 2 * i;
	}
	else if (2 * i + 1 <= currentSize && 4 * i > currentSize){//只有两个孩子，没有孙子
		int result = arr[2 * i] < arr[2 * i + 1] ? 2 * i : 2 * i + 1;
		return result;
	}
	else{//现在有孙子了
		int result = arr[2 * i] < arr[2 * i + 1] ? 2 * i : 2 * i + 1;//儿子中的最小
		for (int x = 4 * i; x <= currentSize && x <= 4 * i + 3; x++){
			if (arr[x]<arr[result]){
				result = x;
			}
		}
		return result;
	}
}
template<class T>
int	MinMaxExHeap<T>::findMaxPosition(int i){//查找第i个节点下面最大的节点，返回节点的位置
	if (2 * i > currentSize){//没有下面的节点了
		return 0;
	}
	else if (2 * i <= currentSize && 2 * i + 1 > currentSize){//只有左孩子
		return 2 * i;
	}
	else if (2 * i + 1 <= currentSize && 4 * i > currentSize){//只有两个孩子，没有孙子
		int result = arr[2 * i] > arr[2 * i + 1] ? 2 * i : 2 * i + 1;
		return result;
	}
	else{//现在有孙子了
		int result = arr[2 * i] > arr[2 * i + 1] ? 2 * i : 2 * i + 1;//儿子中的最大
		for (int x = 4 * i; x <= currentSize && x <= 4 * i + 3; x++){//孙子中最大的
			if (arr[x]>arr[result]){
				result = x;
			}
		}
		return result;
	}
}
