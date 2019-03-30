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

void countingsort(struct data [],int, int ); // 계수 정렬

void insertT(struct data *, int, int);	//타이틀로 정렬하는 삽입정렬
void insertY(struct data *, int, int);	//연도로 정렬하는 삽입 정렬

void swap(struct data*, struct data*);

void mergeSortY(struct data *, int, int);	//연도로 정렬하는 합병정렬
void mergeY(struct data *, int, int, int);	//연도로 정렬하는 합병정렬
void mergeSortT(struct data *, int, int);	//타이틀로 정렬하는 합병정렬
void mergeT(struct data *, int, int, int);	//타이틀로 정렬하는 합병정렬

void quickSortT(struct data [], int, int);	//타이틀로 정렬하는 퀵정렬
void quickSortY(struct data[], int, int);	//연도로 정렬하는 퀵정렬

void rxsort(struct data*, int , int , int, int ); //기수정렬 내부적으로 계수정렬 사용

//연도 힙정렬
void heapifyY(struct data [], int );
void downheapY(struct data[], int, int);
void heapY(struct data [], int size);
//타이틀 힙정렬
void heapifyT(struct data[], int);
void downheapT(struct data[], int, int);
void heapT(struct data[], int size);

int count; //읽어온 데이터들의 라인 수
struct data temp[SIZE]; //합병 정렬에 쓰이는 배열

//정렬시 사용됨
void swap(struct data *arr1, struct data *arr2) {
	struct data temp;
	temp = *arr1;
	*arr1 = *arr2;
	*arr2 = temp;
}
//계수 정렬
//size 정렬할 배열 수

void countingsort(struct data array[],int size, int asc) {
	int counts[2016];

	int i, j;
	struct data *temp = (struct data*)malloc(size * sizeof(struct data));
	
	memset(counts,0,sizeof(counts));
	//데이터의 수를 카운트합니다.
	for(i = 0;i<size; i++){
		counts[array[i].year ]++;
	}
	// 누적합을 구합니다.
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
	//누적합을 이용해 정렬합니다.
	for(j=size-1;j >= 0; j--){
		temp[counts[array[j].year] -1 ] = array[j]; 
		counts[array[j].year] -=1;
	}
	memcpy(array, temp, size * sizeof(struct data));



}
//기수 정렬
// k 기수 10진수 일 경우 10
// p 최대 자릿수
void rxsort(struct data *array, int size, int p, int k, int asc) {
	int *counts; // 특정 자리에서 숫자들의 카운트
		
	struct data *temp;// 정렬된 배열을 담을 임시 장소
	int index, pval, i, j, n;
	if ((counts = (int*)malloc(k * sizeof(int))) == NULL)
		return;
	if ((temp = (struct data*)malloc(size * sizeof(struct data))) == NULL)
		return;
	for (n = 0; n < p; n++) { // 1의 자리, 10의자리, 100의 자리 순으로 진행
		for (i = 0; i < k; i++)
			counts[i] = 0; // 계수 정렬을 위해 배열 초기화
		   // 위치값 계산.
		  // n:0 => 1,  1 => 10, 2 => 100
		pval = (int)pow((double)k, (double)n);
		// 각 숫자의 발생횟수를 넣어줍니다.
		for (j = 0; j < size; j++) {
			// 253이라는 숫자라면
			// n:0 => 3,  1 => 5, 2 => 2
			index = (int)(array[j].year / pval) % k;
			counts[index] = counts[index] + 1;
		}
		// 카운트 누적합을 구합니다.
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
		// 계수정렬 방식
		for (j = size - 1; j >= 0; j--) { // 뒤에서부터 시작
			index = (int)(array[j].year / pval) % k;
			temp[counts[index] - 1] = array[j];
			counts[index] = counts[index] - 1; // 해당 숫자 카운트를 1 감소
		}
		// 임시 데이터 복사합니다
		memcpy(array, temp, size * sizeof(struct data));
	}
}
//연도로 downheap함
void downheapY(struct data array[], int cur, int k)
{
	int left, right, p;
	while (cur < k) {
		left = cur * 2 + 1;
		right = cur * 2 + 2; //and t

		if (left >= k && right >= k) break;

		p = cur;
		if (left < k && array[p].year < array[left].year) { // 문자열을 비교 후 노드를 넣어줄 위치 선정
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
//연도로 heapify 함
void heapifyY(struct data array[], int n)
{
	int i;
	for (i = (n - 1) / 2; i >= 0; i--) {
		downheapY(array, i, n);
	}
}
//연도로 정렬하는 힙 정렬
void heapY(struct data array[], int size)
{
	int k;
	heapifyY(array, size); // 힙 구조를 유지해줍니다.
	for (k = size - 1; k > 0; ) {
		swap(&array[0], &array[k]);
		//k--;
		downheapY(array, 0, k); //힙 정렬을 수행합니다.
		k--;
	}
}
//타이틀로 downheap
void downheapT(struct data array[], int cur, int k)
{
	int left, right, p;
	while (cur < k) {
		left = cur * 2 + 1;
		right = cur * 2 + 2; //and t

			if (left >= k && right >= k) break;

		p = cur;
		if (left < k && strcmp(array[p].title,array[left].title)<0) { // 문자열을 비교 후 노드를 넣어줄 위치 선정
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
//타이틀로 heapify함 
void heapifyT(struct data array[], int n)
{
	int i;
	for (i = (n - 1) / 2; i >= 0; i--) {
		downheapT(array,i, n);
	}
}
//타이틀로 정렬하는 힙 정렬
void heapT(struct data array[], int size)
{
	int k;
	heapifyT(array,size); // 힙 구조를 유지해줍니다.
	for (k = size - 1; k > 0; ) {
		swap(&array[0], &array[k]);
		//k--;
		downheapT(array,0, k); //힙 정렬을 수행합니다.
		k--;
	}
}
//제목으로 정렬하는 삽입 정렬
void insertT(struct data *array, int start, int end)	
{
	struct data temp;			//비교 값
	int i, j = 0;			

	for (i = start; i < end - 1; i++){	//총 n-1번 반복
		temp = array[i+1];				
		for (j = i; (j >= 0) && (strcmp(array[j].title, temp.title) > 0); j--) {	//i요소부터 0번째요소까지 비교
			array[j + 1] = array[j];		//옮긴 자리에 그 전값을 넣어줍니다.		
		}
		array[j + 1] = temp;	
	}
}
//연도로 정렬하는 삽입정렬
void insertY(struct data *array, int start, int end)
{
	struct data temp;			//비교 값
	int i, j = 0;

	for (i = start; i < end - 1; i++) {	//총 n-1번 반복
		temp = array[i + 1];
		for (j = i; (j >= 0) && (array[i].year > temp.year); j--) {	//i요소부터 0번째요소까지 비교
			array[j + 1] = array[j];		//옮긴 자리에 그 전값을 넣어줍니다.		
		}
		array[j + 1] = temp;
	}
}
//타이틀로 정렬하는 합병 정렬
void mergeSortT(struct data *array, int left, int right)	
{
	int mid;	//mid값

	if(left<right)
	{
		mid = (left + right) / 2;		//배열 중간값
		mergeSortT(array, left, mid);		//왼쪽 배열 분할합니다
		mergeSortT(array, mid + 1, right);//오른쪽 배열 분할합니다
		mergeT(array, left, mid, right);	//정렬
	}
}

//타이틀로 정렬하는 합병 정렬 배열 분할함수
void mergeT(struct data *array, int left, int mid, int right)	
{
	int i = left;		//왼쪽 인덱스
	int j = mid + 1;	//오른쪽 인덱스
	int index = left;	//temp 인덱스
	int z;
	//struct data temp[SIZE];

	while (i <= mid && j <= right)	//어느 한쪽이 끝까지 이동할때까지 반복합니다.
	{
		if (strcmp(array[i].title,array[j].title) <= 0)		//두 배열 중 작은수를 넣습니다.
			temp[index++] = array[i++];
		else
			temp[index++] = array[j++];
	}
	//어느 한쪽이 끝났는데 배열에 데이터가 남은 경우 전부 옮깁니다.
	if (i > mid)					//오른쪽에 남아있는 경우
		while (j <= right)			
			temp[index++] = array[j++];
	else							//왼쪽에 남아있는 경우
		while (i <= mid)			
			temp[index++] = array[i++];

	for (z = left; z <= right; z++)	//정렬된 값 옮김
		array[z] = temp[z];
}
//연도로 정렬하는 합병 정렬
void mergeSortY(struct data *array, int left, int right)
{
	int mid;	//mid값

	if (left < right)
	{
		mid = (left + right) / 2;		//배열 중간값
		mergeSortY(array, left, mid);		//왼쪽 배열 분할합니다
		mergeSortY(array, mid + 1, right);//오른쪽 배열 분할합니다
		mergeY(array, left, mid, right);	//정렬
	}
}

//타이틀로 정렬하는 합병 정렬 배열 분할함수
void mergeY(struct data *array, int left, int mid, int right)
{
	int i = left;		//왼쪽 인덱스
	int j = mid + 1;	//오른쪽 인덱스
	int index = left;	//temp 인덱스
	int z;
	//struct data temp[SIZE];

	while (i <= mid && j <= right)	//어느 한쪽이 끝까지 이동할때까지 반복합니다.
	{
		if (array[i].year <= array[j].year)		//두 배열 중 작은수를 넣습니다.
			temp[index++] = array[i++];
		else
			temp[index++] = array[j++];
	}
	//어느 한쪽이 끝났는데 배열에 데이터가 남은 경우 전부 옮깁니다.
	if (i > mid)					//오른쪽에 남아있는 경우
		while (j <= right)
			temp[index++] = array[j++];
	else							//왼쪽에 남아있는 경우
		while (i <= mid)
			temp[index++] = array[i++];

	for (z = left; z <= right; z++)	//정렬된 값 옮김
		array[z] = temp[z];
}

//연도로 정렬하는 퀵 정렬
void quickSortY(struct data array[], int left, int right) 
{
	int i = left, j = right;
	int pivot = array[(left + right) / 2].year; //연도를 기준으로 정렬합니다.
	do
	{
		while (array[i].year < pivot) // 피벗값보다 큰 값이 나오기 전까지 반복합니다.
			i++;
		while (array[j].year > pivot) // 피벗값보다 작은 값이 나오기 전까지 반복합니다.
			j--;
		if (i <= j) //i와 j의 값이 멈춰 있으므로 swap
		{
			swap(&array[i], &array[j]);
			i++;
			j--;
		}
	} while (i <= j);

	/* recursion */
	if (left < j)
		quickSortY(array, left, j); // 피벗 기준으로 왼쪽 영역을 정렬합니다.

	if (i < right)
		quickSortY(array, i, right); // 피벗 기준 오른쪽 영역을 정렬합니다.
}
//타이틀로 정렬하는 퀵 정렬
void quickSortT(struct data array[], int left, int right)
{
	int i = left, j = right;
	char* pivot = array[(left + right) / 2].title; //타이틀을 기준으로 정렬합니다.
	do
	{
		while (strcmp(array[i].title , pivot) < 0) // 피벗값보다 큰 값이 나오기 전까지 반복합니다.
			i++;
		while (strcmp(array[j].title, pivot) > 0) // 피벗값보다 작은 값이 나오기 전까지 반복합니다.
			j--;
		if (i <= j) //i와 j의 값이 멈춰 있으므로 swap
		{
			swap(&array[i], &array[j]);
			i++;
			j--;
		}
	} while (i <= j);

	/* recursion */
	if (left < j)
		quickSortT(array, left, j); // 피벗 기준으로 왼쪽 영역을 정렬합니다.

	if (i < right)
		quickSortT(array, i, right); // 피벗 기준 오른쪽 영역을 정렬합니다.
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
	fseek( fp, 3, SEEK_SET); // 파읽 읽어올시 처음에 데이터가 있어 이부분을 건너뜁니다.
	while(fgets(buf,sizeof(buf),fp) !=NULL){
		if((strstr(buf,"\"") != NULL)||(init == 0) ){
			init++;
			continue;
		}
		datas[count].id = atoi(strtok(buf,","));
		title = strtok(NULL, ","); //읽어온 사이즈에 맞게 동적할당 합니다.
		datas[count].title = (char*)malloc(sizeof(char)*strlen(title));
		strcpy(datas[count].title,title);
		
		if ((temp = strrchr(datas[count].title, '(')) == NULL) { //연도가 없는 경우 건너뜁니다.
			continue;
		}
		else {
			datas[count].year = atoi((temp + 1)); //atoi 함수를 이용해 숫자 뒤의 문자값은 무시합니다.
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
	printf("전체 데이터 수 : %d\n",count);
	//copy = (WData*)malloc(sizeof(struct data)*count);
	//memset(copy, 0, sizeof(struct data)*count);
	//memcpy(copy,datas,(sizeof(struct data)*count));
	//mergesort(datas,0,count-1);
	//quicksort(datas, 0, count - 1);
	//heap(datas);
	//rxsort(datas, count, 4, 10);
	puts("\n1. 100개 데이터 정렬");
	puts("\n2. 500개 데이터 정렬");
	puts("\n3. 1000개 데이터 정렬");
	puts("\n4. 10000개 데이터 정렬");
	puts("\n5. 모든 데이터 정렬\n\n");
	scanf("%d",&input);
	system("cls");
	puts("\n 첫번째 알고리즘 선택");
	puts("\n 1. 삽입 정렬");
	puts("\n 2. 합병 정렬");
	puts("\n 3. 퀵 정렬");
	puts("\n 4. 힙 정렬");
	puts("\n 5. 기수 정렬");
	puts("\n 6. 계수 정렬\n");
	scanf("%d",&algo1);
	system("cls");
	puts("\n 두번째 알고리즘 선택");
	puts("\n 1. 삽입 정렬");
	puts("\n 2. 합병 정렬");
	puts("\n 3. 퀵 정렬");
	puts("\n 4. 힙 정렬");
	puts("\n 5. 기수 정렬");
	puts("\n 6. 계수 정렬\n");
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
				//첫번째 정렬 수행
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
				//두번째 정렬 수행
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
		
		printf("\n100번씩 나누어 정렬 소요 시간 : %f\n\n",sort/ i);
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
				//두번째 정렬 수행
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
		
		printf("\n500번씩 나누어 정렬 소요 시간 : %f\n\n",sort/ i);
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
				//두번째 정렬 수행
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
		
		printf("\n1000번씩 나누어 정렬 소요 시간 : %f\n\n",sort/ i);
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
				//두번째 정렬 수행
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
		
		printf("\n10000번씩 나누어 정렬 소요 시간 : %f\n\n",sort/ i);
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
			//두번째 정렬 수행
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

		printf("\n모든 데이터 정렬 소요 시간 : %f\n\n",sort);


		break;
	}

    fclose(fp);

    return 0;
}