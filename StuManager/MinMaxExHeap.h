/********************************************************************
*            MinMaxExHeap.h
*
*  2017��05��09�� ����2
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
	MinMaxExHeap(int max = 40);//��ʼ��һ�ý�����
	void Insert(T data);//����
	T Extract_max();//ɾ�����Ԫ��
	T Extract_min();//ɾ����СԪ��
	bool isEmpty(){
		if (currentSize<1){
			return true;
		}
		return false;
	}
	int GetCurSzie(){//�õ���ǰ���еĴ�С
		return currentSize;
	}
	void output(){//������ԣ��������
		for (int i = 1; i <= currentSize; i++){
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	T* GetAll(){
		return arr;
	}
private:
	int findMinPosition(int i);//���ҵ�i���ڵ��������С�ڵ㣬���ؽڵ��λ��
	int findMaxPosition(int i);//���ҵ�i���ڵ��������Ľڵ㣬���ؽڵ��λ��
	T *arr;
	int maxSize;
	int currentSize;
};
template<class T>
MinMaxExHeap<T>::MinMaxExHeap(int max = 40){//��ʼ��һ�ý�����
	maxSize = max;
	currentSize = 0;
	arr = new T[max + 1];
	arr[0] = T(MAX);
}
template<class T>
void MinMaxExHeap<T>::Insert(T data){//����

	if (currentSize == maxSize){//������
		throw new OutofBounds();
	}
	currentSize++;
	if (currentSize == 1){//�նѲ���
		arr[1] = data;
		return;
	}


	int i = currentSize;
	//�жϸ��׽ڵ����ڵ�����
	//�õ����ڵ�Ĳ������жϲ�������ż
	int h = (int)ceil((log((i / 2) + 1) / log(2)));
	bool f = false;//fΪtrue������
	if (h % 2 == 0){
		f = true;
	}
	if (f && data>arr[i / 2]){//�����ĸ��ף�data�ȸ��״�,��Ҫ�ʹ����ڵ�Ƚϴ�С�������Ƿ�����
		arr[i] = arr[i / 2];
		i = i / 2;
		while ((i != 2 && i != 3) && data > arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else if (f && data <= arr[i / 2]){//�����ĸ��ף�data�ȸ���С,��Ҫ��С����Ľڵ�Ƚϴ�С
		if (data > arr[i / 4]){//������С�����үү����ô���ŵ�ԭλ��
			arr[i] = data;
		}
		else{//��С��үү����Ҫ�ϱ�
			while (i != 1 && data < arr[i / 4]){
				arr[i] = arr[i / 4];
				i = i / 4;
			}
			arr[i] = data;
		}
	}
	else if (!f && data < arr[i / 2]){//С����ĸ��ף�dataС�ڸ���

		arr[i] = arr[i / 2];
		i = i / 2;
		while (i != 1 && data< arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else {//С����ĸ��ף�data���ڸ���
		if (data < arr[i / 4]){//��С�ڴ�����үү����ô���ŵ�ԭλ��
			arr[i] = data;
		}
		else{//������үү����Ҫ�ϱ�
			while (i != 2 && i != 3 && data > arr[i / 4]){
				arr[i] = arr[i / 4];
				i = i / 4;
			}
			arr[i] = data;
		}
	}
}

template<class T>
T MinMaxExHeap<T>::Extract_max(){//ɾ�����Ԫ��
	if (currentSize == 0){//���ؿ��쳣
		throw new Null();
	}
	if (currentSize == 1 || currentSize == 2){//ֻ��һ��Ԫ�ػ�����Ԫ��
		return arr[currentSize--];
	}

	//���������ϵ�Ԫ��ʱ
	T result = arr[2] > arr[3] ? arr[2] : arr[3];//���Ԫ�س����ں�ڶ���֮��
	int i = arr[2] > arr[3] ? 2 : 3;
	T data = arr[currentSize--];//Ϊ���һ�����·���λ��

	while ((int)ceil((log((i)+1) / log(2))) < (int)ceil((log((currentSize)+1) / log(2)))){//�����һ���ͣ��
		int maxPosition = findMaxPosition(i);//�������ĺ����е����ڵ�
		if (maxPosition == 0){
			break;
		}
		if (data>arr[maxPosition]){
			break;
		}
		arr[i] = arr[maxPosition];
		i = maxPosition;
	}


	//�ж�Ҫ����λ�õĸ����Ǵ���㻹��С����
	int h = (int)ceil((log((i / 2) + 1) / log(2)));
	bool f = false;//fΪtrue������
	if (h % 2 == 0){
		f = true;
	}

	if (f && data > arr[i / 2]){//�����ĸ��ף�data�ȸ��״�,��Ҫ�ʹ����ڵ�Ƚϴ�С�������Ƿ�����
		arr[i] = arr[i / 2];
		i = i / 2;
		while ((i != 2 && i != 3) && data > arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else if (f && data <= arr[i / 2]){//�����ĸ��ף�data�ȸ���С,��Ҫ��С����Ľڵ�Ƚϴ�С
		if (data > arr[i / 4]){//������С�����үү����ô���ŵ�ԭλ��
			arr[i] = data;
		}
		else{//��С��үү����Ҫ�ϱ�
			while (i != 1 && data < arr[i / 4]){
				arr[i] = arr[i / 4];
				i = i / 4;
			}
			arr[i] = data;
		}
	}
	else if (!f && data < arr[i / 2]){//С����ĸ��ף�dataС�ڸ���

		arr[i] = arr[i / 2];
		i = i / 2;
		while (i != 1 && data< arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else {//С����ĸ��ף�data���ڸ���
		if (data < arr[i / 4]){//��С�ڴ�����үү����ô���ŵ�ԭλ��
			arr[i] = data;
		}
		else{//������үү����Ҫ�ϱ�
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
T MinMaxExHeap<T>::Extract_min(){//ɾ����СԪ��
	if (currentSize == 0){//���ؿ��쳣
		throw new Null();
	}
	T result = arr[1];//arr[1]������С
	if (currentSize == 1){
		currentSize--;
		return result;
	}
	T data = arr[currentSize--];//Ϊ���һ�����·���λ��
	int i = 1;
	while ((int)ceil((log((i)+1) / log(2))) < (int)ceil((log((currentSize)+1) / log(2)))){//�����һ���ͣ��
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

	//�ж�Ҫ����λ�õĸ����Ǵ���㻹��С����
	int h = (int)ceil((log((i / 2) + 1) / log(2)));
	bool f = false;//fΪtrue������
	if (h % 2 == 0){
		f = true;
	}

	if (f && data > arr[i / 2]){//�����ĸ��ף�data�ȸ��״�,��Ҫ�ʹ����ڵ�Ƚϴ�С�������Ƿ�����
		arr[i] = arr[i / 2];
		i = i / 2;
		while ((i != 2 && i != 3) && data > arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else if (f && data <= arr[i / 2]){//�����ĸ��ף�data�ȸ���С,��Ҫ��С����Ľڵ�Ƚϴ�С
		if (data > arr[i / 4]){//������С�����үү����ô���ŵ�ԭλ��
			arr[i] = data;
		}
		else{//��С��үү����Ҫ�ϱ�
			while (i != 1 && data < arr[i / 4]){
				arr[i] = arr[i / 4];
				i = i / 4;
			}
			arr[i] = data;
		}
	}
	else if (!f && data < arr[i / 2]){//С����ĸ��ף�dataС�ڸ���

		arr[i] = arr[i / 2];
		i = i / 2;
		while (i != 1 && data< arr[i / 4]){
			arr[i] = arr[i / 4];
			i = i / 4;
		}
		arr[i] = data;
	}
	else {//С����ĸ��ף�data���ڸ���
		if (data < arr[i / 4]){//��С�ڴ�����үү����ô���ŵ�ԭλ��
			arr[i] = data;
		}
		else{//������үү����Ҫ�ϱ�
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
	if (2 * i > currentSize){//û������Ľڵ���
		return 0;
	}
	else if (2 * i <= currentSize && 2 * i + 1 > currentSize){//ֻ������
		return 2 * i;
	}
	else if (2 * i + 1 <= currentSize && 4 * i > currentSize){//ֻ���������ӣ�û������
		int result = arr[2 * i] < arr[2 * i + 1] ? 2 * i : 2 * i + 1;
		return result;
	}
	else{//������������
		int result = arr[2 * i] < arr[2 * i + 1] ? 2 * i : 2 * i + 1;//�����е���С
		for (int x = 4 * i; x <= currentSize && x <= 4 * i + 3; x++){
			if (arr[x]<arr[result]){
				result = x;
			}
		}
		return result;
	}
}
template<class T>
int	MinMaxExHeap<T>::findMaxPosition(int i){//���ҵ�i���ڵ��������Ľڵ㣬���ؽڵ��λ��
	if (2 * i > currentSize){//û������Ľڵ���
		return 0;
	}
	else if (2 * i <= currentSize && 2 * i + 1 > currentSize){//ֻ������
		return 2 * i;
	}
	else if (2 * i + 1 <= currentSize && 4 * i > currentSize){//ֻ���������ӣ�û������
		int result = arr[2 * i] > arr[2 * i + 1] ? 2 * i : 2 * i + 1;
		return result;
	}
	else{//������������
		int result = arr[2 * i] > arr[2 * i + 1] ? 2 * i : 2 * i + 1;//�����е����
		for (int x = 4 * i; x <= currentSize && x <= 4 * i + 3; x++){//����������
			if (arr[x]>arr[result]){
				result = x;
			}
		}
		return result;
	}
}
