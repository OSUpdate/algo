#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define SIZE 30000

struct data{
	int id;
	int year;
	char *title;
	char *genres;
};

void countingsort(struct data [],int, int ); // ��� ����

void insertT(struct data *, int, int);	//Ÿ��Ʋ�� �����ϴ� ��������
void insertY(struct data *, int, int);	//������ �����ϴ� ���� ����

void swap(struct data*, struct data*);

void mergeSortY(struct data *, int, int);	//������ �����ϴ� �պ�����
void mergeY(struct data *, int, int, int);	//������ �����ϴ� �պ�����
void mergeSortT(struct data *, int, int);	//Ÿ��Ʋ�� �����ϴ� �պ�����
void mergeT(struct data *, int, int, int);	//Ÿ��Ʋ�� �����ϴ� �պ�����

void quickSortT(struct data [], int, int);	//Ÿ��Ʋ�� �����ϴ� ������
void quickSortY(struct data[], int, int);	//������ �����ϴ� ������

void rxsort(struct data*, int , int , int, int ); //������� ���������� ������� ���

//���� ������
void heapifyY(struct data [], int );
void downheapY(struct data[], int, int);
void heapY(struct data [], int size);
//Ÿ��Ʋ ������
void heapifyT(struct data[], int);
void downheapT(struct data[], int, int);
void heapT(struct data[], int size);

int count; //�о�� �����͵��� ���� ��
struct data temp[SIZE]; //�պ� ���Ŀ� ���̴� �迭

//���Ľ� ����
void swap(struct data *arr1, struct data *arr2) {
	struct data temp;
	temp = *arr1;
	*arr1 = *arr2;
	*arr2 = temp;
}
//��� ����
//size ������ �迭 ��

void countingsort(struct data array[],int size, int asc) {
	int counts[2016];

	int i, j;
	struct data *temp = (struct data*)malloc(size * sizeof(struct data));
	
	memset(counts,0,sizeof(counts));
	//�������� ���� ī��Ʈ�մϴ�.
	for(i = 0;i<size; i++){
		counts[array[i].year ]++;
	}
	// �������� ���մϴ�.
	if (asc) {
		for (i = 1; i <= 2015; i++) {
			counts[i] = counts[i - 1] + counts[i];
		}
	}
	else {
		for (i = 2014; i >= 0; i--) {
			counts[i] = counts[i + 1] + counts[i];
		}
	}
	//�������� �̿��� �����մϴ�.
	for(j=size-1;j >= 0; j--){
		temp[counts[array[j].year] -1 ] = array[j]; 
		counts[array[j].year] -=1;
	}
	memcpy(array, temp, size * sizeof(struct data));



}
//��� ����
// k ��� 10���� �� ��� 10
// p �ִ� �ڸ���
void rxsort(struct data *array, int size, int p, int k, int asc) {
	int *counts; // Ư�� �ڸ����� ���ڵ��� ī��Ʈ
		
	struct data *temp;// ���ĵ� �迭�� ���� �ӽ� ���
	int index, pval, i, j, n;
	if ((counts = (int*)malloc(k * sizeof(int))) == NULL)
		return;
	if ((temp = (struct data*)malloc(size * sizeof(struct data))) == NULL)
		return;
	for (n = 0; n < p; n++) { // 1�� �ڸ�, 10���ڸ�, 100�� �ڸ� ������ ����
		for (i = 0; i < k; i++)
			counts[i] = 0; // ��� ������ ���� �迭 �ʱ�ȭ
		   // ��ġ�� ���.
		  // n:0 => 1,  1 => 10, 2 => 100
		pval = (int)pow((double)k, (double)n);
		// �� ������ �߻�Ƚ���� �־��ݴϴ�.
		for (j = 0; j < size; j++) {
			// 253�̶�� ���ڶ��
			// n:0 => 3,  1 => 5, 2 => 2
			index = (int)(array[j].year / pval) % k;
			counts[index] = counts[index] + 1;
		}
		// ī��Ʈ �������� ���մϴ�.
		if (asc) {
			for (i = 1; i < k; i++) {
				counts[i] = counts[i] + counts[i - 1];
			}
		}
		else {
			for (i = k-2; i >= 0; i--) {
				counts[i] = counts[i] + counts[i + 1];
			}
		}
		// ������� ���
		for (j = size - 1; j >= 0; j--) { // �ڿ������� ����
			index = (int)(array[j].year / pval) % k;
			temp[counts[index] - 1] = array[j];
			counts[index] = counts[index] - 1; // �ش� ���� ī��Ʈ�� 1 ����
		}
		// �ӽ� ������ �����մϴ�
		memcpy(array, temp, size * sizeof(struct data));
	}
}
//������ downheap��
void downheapY(struct data array[], int cur, int k)
{
	int left, right, p;
	while (cur < k) {
		left = cur * 2 + 1;
		right = cur * 2 + 2; //and t

		if (left >= k && right >= k) break;

		p = cur;
		if (left < k && array[p].year < array[left].year) { // ���ڿ��� �� �� ��带 �־��� ��ġ ����
			p = left;
		}
		if (right < k && array[p].year < array[right].year) {
			p = right;
		}
		if (p == cur) break;

		swap(&array[cur], &array[p]);
		cur = p;
	}
}
//������ heapify ��
void heapifyY(struct data array[], int n)
{
	int i;
	for (i = (n - 1) / 2; i >= 0; i--) {
		downheapY(array, i, n);
	}
}
//������ �����ϴ� �� ����
void heapY(struct data array[], int size)
{
	int k;
	heapifyY(array, size); // �� ������ �������ݴϴ�.
	for (k = size - 1; k > 0; ) {
		swap(&array[0], &array[k]);
		//k--;
		downheapY(array, 0, k); //�� ������ �����մϴ�.
		k--;
	}
}
//Ÿ��Ʋ�� downheap
void downheapT(struct data array[], int cur, int k)
{
	int left, right, p;
	while (cur < k) {
		left = cur * 2 + 1;
		right = cur * 2 + 2; //and t

			if (left >= k && right >= k) break;

		p = cur;
		if (left < k && strcmp(array[p].title,array[left].title)<0) { // ���ڿ��� �� �� ��带 �־��� ��ġ ����
			p = left;
		}
		if (right < k && strcmp(array[p].title,array[right].title)<0) {
			p = right;
		}
		if (p == cur) break;

		swap(&array[cur], &array[p]);
		cur = p;
	}
}
//Ÿ��Ʋ�� heapify�� 
void heapifyT(struct data array[], int n)
{
	int i;
	for (i = (n - 1) / 2; i >= 0; i--) {
		downheapT(array,i, n);
	}
}
//Ÿ��Ʋ�� �����ϴ� �� ����
void heapT(struct data array[], int size)
{
	int k;
	heapifyT(array,size); // �� ������ �������ݴϴ�.
	for (k = size - 1; k > 0; ) {
		swap(&array[0], &array[k]);
		//k--;
		downheapT(array,0, k); //�� ������ �����մϴ�.
		k--;
	}
}
//�������� �����ϴ� ���� ����
void insertT(struct data *array, int start, int end)	
{
	struct data temp;			//�� ��
	int i, j = 0;			

	for (i = start; i < end - 1; i++){	//�� n-1�� �ݺ�
		temp = array[i+1];				
		for (j = i; (j >= 0) && (strcmp(array[j].title, temp.title) > 0); j--) {	//i��Һ��� 0��°��ұ��� ��
			array[j + 1] = array[j];		//�ű� �ڸ��� �� ������ �־��ݴϴ�.		
		}
		array[j + 1] = temp;	
	}
}
//������ �����ϴ� ��������
void insertY(struct data *array, int start, int end)
{
	struct data temp;			//�� ��
	int i, j = 0;

	for (i = start; i < end - 1; i++) {	//�� n-1�� �ݺ�
		temp = array[i + 1];
		for (j = i; (j >= 0) && (array[i].year > temp.year); j--) {	//i��Һ��� 0��°��ұ��� ��
			array[j + 1] = array[j];		//�ű� �ڸ��� �� ������ �־��ݴϴ�.		
		}
		array[j + 1] = temp;
	}
}
//Ÿ��Ʋ�� �����ϴ� �պ� ����
void mergeSortT(struct data *array, int left, int right)	
{
	int mid;	//mid��

	if(left<right)
	{
		mid = (left + right) / 2;		//�迭 �߰���
		mergeSortT(array, left, mid);		//���� �迭 �����մϴ�
		mergeSortT(array, mid + 1, right);//������ �迭 �����մϴ�
		mergeT(array, left, mid, right);	//����
	}
}

//Ÿ��Ʋ�� �����ϴ� �պ� ���� �迭 �����Լ�
void mergeT(struct data *array, int left, int mid, int right)	
{
	int i = left;		//���� �ε���
	int j = mid + 1;	//������ �ε���
	int index = left;	//temp �ε���
	int z;
	//struct data temp[SIZE];

	while (i <= mid && j <= right)	//��� ������ ������ �̵��Ҷ����� �ݺ��մϴ�.
	{
		if (strcmp(array[i].title,array[j].title) <= 0)		//�� �迭 �� �������� �ֽ��ϴ�.
			temp[index++] = array[i++];
		else
			temp[index++] = array[j++];
	}
	//��� ������ �����µ� �迭�� �����Ͱ� ���� ��� ���� �ű�ϴ�.
	if (i > mid)					//�����ʿ� �����ִ� ���
		while (j <= right)			
			temp[index++] = array[j++];
	else							//���ʿ� �����ִ� ���
		while (i <= mid)			
			temp[index++] = array[i++];

	for (z = left; z <= right; z++)	//���ĵ� �� �ű�
		array[z] = temp[z];
}
//������ �����ϴ� �պ� ����
void mergeSortY(struct data *array, int left, int right)
{
	int mid;	//mid��

	if (left < right)
	{
		mid = (left + right) / 2;		//�迭 �߰���
		mergeSortY(array, left, mid);		//���� �迭 �����մϴ�
		mergeSortY(array, mid + 1, right);//������ �迭 �����մϴ�
		mergeY(array, left, mid, right);	//����
	}
}

//Ÿ��Ʋ�� �����ϴ� �պ� ���� �迭 �����Լ�
void mergeY(struct data *array, int left, int mid, int right)
{
	int i = left;		//���� �ε���
	int j = mid + 1;	//������ �ε���
	int index = left;	//temp �ε���
	int z;
	//struct data temp[SIZE];

	while (i <= mid && j <= right)	//��� ������ ������ �̵��Ҷ����� �ݺ��մϴ�.
	{
		if (array[i].year <= array[j].year)		//�� �迭 �� �������� �ֽ��ϴ�.
			temp[index++] = array[i++];
		else
			temp[index++] = array[j++];
	}
	//��� ������ �����µ� �迭�� �����Ͱ� ���� ��� ���� �ű�ϴ�.
	if (i > mid)					//�����ʿ� �����ִ� ���
		while (j <= right)
			temp[index++] = array[j++];
	else							//���ʿ� �����ִ� ���
		while (i <= mid)
			temp[index++] = array[i++];

	for (z = left; z <= right; z++)	//���ĵ� �� �ű�
		array[z] = temp[z];
}

//������ �����ϴ� �� ����
void quickSortY(struct data array[], int left, int right) 
{
	int i = left, j = right;
	int pivot = array[(left + right) / 2].year; //������ �������� �����մϴ�.
	do
	{
		while (array[i].year < pivot) // �ǹ������� ū ���� ������ ������ �ݺ��մϴ�.
			i++;
		while (array[j].year > pivot) // �ǹ������� ���� ���� ������ ������ �ݺ��մϴ�.
			j--;
		if (i <= j) //i�� j�� ���� ���� �����Ƿ� swap
		{
			swap(&array[i], &array[j]);
			i++;
			j--;
		}
	} while (i <= j);

	/* recursion */
	if (left < j)
		quickSortY(array, left, j); // �ǹ� �������� ���� ������ �����մϴ�.

	if (i < right)
		quickSortY(array, i, right); // �ǹ� ���� ������ ������ �����մϴ�.
}
//Ÿ��Ʋ�� �����ϴ� �� ����
void quickSortT(struct data array[], int left, int right)
{
	int i = left, j = right;
	char* pivot = array[(left + right) / 2].title; //Ÿ��Ʋ�� �������� �����մϴ�.
	do
	{
		while (strcmp(array[i].title , pivot) < 0) // �ǹ������� ū ���� ������ ������ �ݺ��մϴ�.
			i++;
		while (strcmp(array[j].title, pivot) > 0) // �ǹ������� ���� ���� ������ ������ �ݺ��մϴ�.
			j--;
		if (i <= j) //i�� j�� ���� ���� �����Ƿ� swap
		{
			swap(&array[i], &array[j]);
			i++;
			j--;
		}
	} while (i <= j);

	/* recursion */
	if (left < j)
		quickSortT(array, left, j); // �ǹ� �������� ���� ������ �����մϴ�.

	if (i < right)
		quickSortT(array, i, right); // �ǹ� ���� ������ ������ �����մϴ�.
}

int main()
{
	clock_t startT, finish;

	double sort = 0;

	struct data datas[SIZE];

	char buf[1024];
	char *temp;
	char *title;
	char *genres;
	
	int init = 0, cnum, last=0;
	int tLen,start,end;
	int input, algo1, algo2;
	int i=0;
    FILE *fp = fopen("movies.txt", "r");
	count = 0;
	fseek( fp, 3, SEEK_SET); // ���� �о�ý� ó���� �����Ͱ� �־� �̺κ��� �ǳʶݴϴ�.
	while(fgets(buf,sizeof(buf),fp) !=NULL){
		if((strstr(buf,"\"") != NULL)||(init == 0) ){
			init++;
			continue;
		}
		datas[count].id = atoi(strtok(buf,","));
		title = strtok(NULL, ","); //�о�� ����� �°� �����Ҵ� �մϴ�.
		datas[count].title = (char*)malloc(sizeof(char)*strlen(title));
		strcpy(datas[count].title,title);
		
		if ((temp = strrchr(datas[count].title, '(')) == NULL) { //������ ���� ��� �ǳʶݴϴ�.
			continue;
		}
		else {
			datas[count].year = atoi((temp + 1)); //atoi �Լ��� �̿��� ���� ���� ���ڰ��� �����մϴ�.
			tLen = strlen(datas[count].title);
			for (i = 0; datas[count].title[(tLen - 1 - i)] != '('; i++) {
				datas[count].title[(tLen - 1 - i)] = '\0';
			}
			datas[count].title[(tLen - 1 - i)] = '\0';
		}
		genres = strtok(NULL, ",");
		datas[count].genres = (char*)malloc(sizeof(char)*strlen(genres));
		strcpy(datas[count].genres, genres);
		count++;

	}
	printf("��ü ������ �� : %d\n",count);
	//copy = (WData*)malloc(sizeof(struct data)*count);
	//memset(copy, 0, sizeof(struct data)*count);
	//memcpy(copy,datas,(sizeof(struct data)*count));
	//mergesort(datas,0,count-1);
	//quicksort(datas, 0, count - 1);
	//heap(datas);
	//rxsort(datas, count, 4, 10);
	puts("\n1. 100�� ������ ����");
	puts("\n2. 500�� ������ ����");
	puts("\n3. 1000�� ������ ����");
	puts("\n4. 10000�� ������ ����");
	puts("\n5. ��� ������ ����\n\n");
	scanf("%d",&input);
	system("cls");
	puts("\n ù��° �˰��� ����");
	puts("\n 1. ���� ����");
	puts("\n 2. �պ� ����");
	puts("\n 3. �� ����");
	puts("\n 4. �� ����");
	puts("\n 5. ��� ����");
	puts("\n 6. ��� ����\n");
	scanf("%d",&algo1);
	system("cls");
	puts("\n �ι�° �˰��� ����");
	puts("\n 1. ���� ����");
	puts("\n 2. �պ� ����");
	puts("\n 3. �� ����");
	puts("\n 4. �� ����");
	puts("\n 5. ��� ����");
	puts("\n 6. ��� ����\n");
	scanf("%d",&algo2);
	switch(input){
	case 1:
		cnum = count / 100;
		for(i = 0;i<cnum;i++){
			start = count/cnum * i;
			end = start + 100;
			if( count - start < 100 )
				end = count;
			if( start < count){
				//ù��° ���� ����
				switch(algo1){
				case 1:
					startT = clock();
					insertT(datas,start ,end);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 2:
					startT = clock();
					mergeSortT(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 3:
					startT = clock();
					quickSortT(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 4:
					startT = clock();
					if( count - start < 100 )
						start = count;
					heapT(datas,start);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 5:
					if( count - start < 100 )
						start = count;
					startT = clock();
					rxsort(datas, start, 4, 10, 0);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 6:
					if( count - start < 100 )
						start = count;
					startT = clock();
					countingsort(datas,start, 0);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				}
				//�ι�° ���� ����
				switch(algo2){
				case 1:
					startT = clock();
					insertY(datas,start ,end);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 2:
					startT = clock();
					mergeSortY(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 3:
					startT = clock();
					quickSortY(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 4:
					if( count - start < 100 )
						start = count;
					startT = clock();
					heapY(datas,start);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 5:
					if( count - start < 100 )
						start = count;
					startT = clock();
					rxsort(datas, start, 4, 10, 1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 6:
					if( count - start < 100 )
						start = count;
					startT = clock();
					countingsort(datas,start, 1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				}
				
			}
		}
		
		printf("\n100���� ������ ���� �ҿ� �ð� : %f\n\n",sort/ i);
		break;
	case 2:
		cnum = count / 500;
		for(i = 0;i<cnum;i++){
			start = count/cnum * i; 
			end = start + 500;
			if( count - start < 500 )
				end = count;
			if( start < count){
				switch(algo1){
				case 1:
					startT = clock();
					insertT(datas,start ,end);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 2:
					startT = clock();
					mergeSortT(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 3:
					startT = clock();
					quickSortT(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 4:
					startT = clock();
					if( count - start < 500 )
						start = count;
					heapT(datas,start);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 5:
					if( count - start < 500 )
						start = count;
					startT = clock();
					rxsort(datas, start, 4, 10, 0);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 6:
					if( count - start < 500 )
						start = count;
					startT = clock();
					countingsort(datas,start, 0);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				}
				//�ι�° ���� ����
				switch(algo2){
				case 1:
					startT = clock();
					insertY(datas,start ,end);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 2:
					startT = clock();
					mergeSortY(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 3:
					startT = clock();
					quickSortY(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 4:
					if( count - start < 500 )
						start = count;
					startT = clock();
					heapY(datas,start);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 5:
					if( count - start < 500 )
						start = count;
					startT = clock();
					rxsort(datas, start, 4, 10, 1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 6:
					if( count - start < 500 )
						start = count;
					startT = clock();
					countingsort(datas,start, 1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				}
			}
		}
		
		printf("\n500���� ������ ���� �ҿ� �ð� : %f\n\n",sort/ i);
		break;
	case 3:
		cnum = count / 1000;
		for(i = 0;i<cnum;i++){
			start = count/cnum * i; 
			end = start + 1000;
			if( count - start < 1000 )
				end = count;
			if( start < count){
				switch(algo1){
				case 1:
					startT = clock();
					insertT(datas,start ,end);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 2:
					startT = clock();
					mergeSortT(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 3:
					startT = clock();
					quickSortT(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 4:
					startT = clock();
					if( count - start < 1000 )
						start = count;
					heapT(datas,start);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 5:
					if( count - start < 1000 )
						start = count;
					startT = clock();
					rxsort(datas, start, 4, 10, 0);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 6:
					if( count - start < 1000 )
						start = count;
					startT = clock();
					countingsort(datas,start, 0);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				}
				//�ι�° ���� ����
				switch(algo2){
				case 1:
					startT = clock();
					insertY(datas,start ,end);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 2:
					startT = clock();
					mergeSortY(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 3:
					startT = clock();
					quickSortY(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 4:
					if( count - start < 1000 )
						start = count;
					startT = clock();
					heapY(datas,start);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 5:
					if( count - start < 1000 )
						start = count;
					startT = clock();
					rxsort(datas, start, 4, 10,1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 6:
					if( count - start < 1000 )
						start = count;
					startT = clock();
					countingsort(datas,start,1 );
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				}
			}
		}
		
		printf("\n1000���� ������ ���� �ҿ� �ð� : %f\n\n",sort/ i);
		break;
	case 4:
		cnum = count / 10000;
		for(i = 0;i<cnum;i++){
			start = count/cnum * i; 
			end = start + 10000;
			if( count - start < 10000 )
				end = count;
			if( start < count){
				switch(algo1){
				case 1:
					startT = clock();
					insertT(datas,start ,end);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 2:
					startT = clock();
					mergeSortT(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 3:
					startT = clock();
					quickSortT(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 4:
					startT = clock();
					if( count - start < 10000 )
						start = count;
					heapT(datas,start);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 5:
					if( count - start < 10000 )
						start = count;
					startT = clock();
					rxsort(datas, start, 4, 10, 0);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 6:
					if( count - start < 10000 )
						start = count;
					startT = clock();
					countingsort(datas,start, 0);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				}
				//�ι�° ���� ����
				switch(algo2){
				case 1:
					startT = clock();
					insertY(datas,start ,end);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 2:
					startT = clock();
					mergeSortY(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 3:
					startT = clock();
					quickSortY(datas,start,end-1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 4:
					if( count - start < 10000 )
						start = count;
					startT = clock();
					heapY(datas,start);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 5:
					if( count - start < 10000 )
						start = count;
					startT = clock();
					rxsort(datas, start, 4, 10,1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				case 6:
					if( count - start < 10000 )
						start = count;
					startT = clock();
					countingsort(datas,start,1);
					finish = clock();
					sort += (double)(finish-startT)/CLOCKS_PER_SEC;
					break;
				}
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
			}
		}
		
		printf("\n10000���� ������ ���� �ҿ� �ð� : %f\n\n",sort/ i);
		break;
	case 5:
		switch(algo1){
			case 1:
				startT = clock();
				insertT(datas,0 ,count);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
			break;
			case 2:
				startT = clock();
				mergeSortT(datas,0,count-1);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
				break;
			case 3:
				startT = clock();
				quickSortT(datas,0,count-1);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
				break;
			case 4:
				startT = clock();
				heapT(datas,count);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
				break;
			case 5:

				startT = clock();
				rxsort(datas, count, 4, 10, 0);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
				break;
			case 6:

				startT = clock();
				countingsort(datas,count, 0);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
				break;
			}
			//�ι�° ���� ����
			switch(algo2){
			case 1:
				startT = clock();
				insertY(datas,0 ,count);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
				break;
			case 2:
				startT = clock();
				mergeSortY(datas,0,count-1);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
				break;
			case 3:
				startT = clock();
				quickSortY(datas,0,count-1);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
				break;
			case 4:
				startT = clock();
				heapY(datas,count);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
				break;
			case 5:
				startT = clock();
				rxsort(datas, count, 4, 10,1);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
				break;
			case 6:
				startT = clock();
				countingsort(datas,count,1);
				finish = clock();
				sort += (double)(finish-startT)/CLOCKS_PER_SEC;
			break;
			}

		printf("\n��� ������ ���� �ҿ� �ð� : %f\n\n",sort);


		break;
	}

    fclose(fp);

    return 0;
}