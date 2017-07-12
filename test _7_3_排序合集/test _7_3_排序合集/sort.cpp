#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;
void PrintArray(int *a, size_t n)
{
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	cout << endl;
}
void _AdjustDown(int *a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n&&a[child + 1] > a[child])
			child++;
		if (a[child] > a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}
void HeapSort(int *a, size_t n)
{
	assert(a);
	for (int i = (n - 2) / 2; i >= 0; --i)
	{
		_AdjustDown(a, n, i);
	}
	int end = n;
	while (end--)
	{
		swap(a[0], a[end]);
		_AdjustDown(a, end, 0);
	}
}
void SelectSort(int *a, size_t n)
{
	assert(a);
	int lhs = 0,rhs=n-1;
	while (lhs < rhs)
	{
		int max=lhs;
		int min = lhs;
		for (int i = lhs; i <= rhs; ++i)
		{
			if (a[i]>=a[max])
				max = i;
			if (a[i] <= a[min])
				min = i;
		}
		swap(a[min], a[lhs]);
		if (max == lhs)
			max = min;
		 swap(a[max], a[rhs]);
		++lhs;
		--rhs;
	}
}
void InsertSort(int *a, size_t n)
{
	for (int i = 0; i<n-1; i++)
	{
		int end = i;
		int temp = a[end + 1];
		while (end >= 0)
		{
			if (a[end] > temp)
			{
				a[end + 1] = a[end];
				end--;
			}
			else
				break;
			a[end+1] = temp;
		}
	}
}

void ShellSort(int *a, size_t n)
{
	int gap = n;
	while (gap>1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < n - gap; ++i)
		{
			int end = i;
			int temp = a[end + gap];
			while (end >= 0)
			{
				if (a[end]>temp)
				{
					a[end + gap] = a[end];
					end = end - gap;
				}
				else
					break;
				a[end+gap]=temp;
			}
		}
	}
}
void BubbleSort(int *a, size_t n)
{
	assert(a);
	for (int i = 0; i < n - 1; i++)
	{
		bool flag = false;
		for (int j = 0; j < n - 1 - i; j++)
		{	
			if (a[j]>a[j + 1])
			{
				swap(a[j], a[j + 1]);
				flag = true;
			}	
		}
		if (flag == false)
				break;
	}
}
int Partition1(int *a, int left, int right)
{
	int start = left;
	int end = right;
	int key = a[right];
	while (start < end)
	{
		while (start < end&&a[start] <= key)
			start++;
		while (start < end&&a[end] >= key)
			end--;
		if (start < end)
			swap(a[start], a[end]);
	}
	if (start==end)
		swap(a[start], a[right]);
	return start;	
}
int Partition2(int *a, int left, int right)
{
	assert(a&&left < right);
	int key = a[right];
	while (left < right)
	{
		while (left < right&&a[left] <= key)
			left++;
		a[right]=a[left];
		while (left < right&&a[right] >= key)
			right--;
		a[left] = a[right];
	}
	if (left == right)
		a[left]=key;
	return left;
}
int  Partition3(int *a, int left, int right)
{
	int cur = left;
	int prev = left - 1;
	int key = a[right];
	while (cur < right)
	{
		/*if (a[cur] < key&&++prev != cur)
		{
			swap(a[cur], a[prev]);	
		}++ cur;*/
		if (a[cur] < key)
		{
			if (++prev != cur)
				swap(a[cur], a[prev]);
		}
			cur++;
	}
	if (a[cur] == key)
		swap(a[cur], a[++prev]);
	return prev;
}
void QuickSortNonR(int *a, int left, int right)
{
	assert(a);
	stack<int > s;
	s.push(right);
	s.push(left);
	while (!s.empty())
	{
		int begin = s.top();
		s.pop();
		int end = s.top();
		s.pop();
		int div = Partition1(a, begin, end);
		if (begin < div)
		{
			s.push(div - 1);
			s.push(begin);
		}
		if (end>div)
		{
			s.push(end);
			s.push(div + 1);
		}
	}
}
void QuickSort(int *a ,int left , int right)
{
	if (a == NULL || right <= left)
		return;
		int div = Partition3(a, left, right);
		if (div>left)
		QuickSort(a, left, div-1);
		if (div<right)
		QuickSort(a, div+1, right);
}
void merge(int *a, int *temp, int left, int mid, int right)
{
	int  begin1 = left;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = right;
	int index = begin1;
	while (begin1 <= end1&&begin2 <= end2)
	{
		if (a[begin1] <= a[begin2])
			temp[index++] = a[begin1++];
		else
			temp[index++] = a[begin2++];
	}
	if (begin1 > end1)//begin1зпЭъ
	{
		while (begin2 <= end2)
			temp[index++] = a[begin2++];
	}
	else if (begin2 > end2)
	{
		while (begin1 <= end1)
			temp[index++] = a[begin1++];
	}
}

void _mergeSort(int *a ,int * temp, int left, int right)
{
	if (left >= right)
		return;
	int mid = left - (left - right) / 2;
	_mergeSort(a, temp, left, mid);
	_mergeSort(a, temp, mid + 1, right);
	merge(a, temp, left, mid, right);
	memmove(a + left, temp + left, (right - left + 1)*sizeof(int));
}
void MergeSort(int * a, size_t n)
{
	if (a==NULL||n <= 0)
		return;
	int left = 0;
	int right = n - 1;
	int *temp = new int[n];
	_mergeSort(a,temp, left, right);
	delete[] temp;
}
void TestMergeSort()
{
	int a[] = { 4, 3, 7, 6, 5, 8, 9, 0, 2, 1, 12, 18, 15, 11 };
	PrintArray(a, sizeof(a) / sizeof(a[1]));
	MergeSort(a, sizeof(a) / sizeof(a[1]));
	PrintArray(a, sizeof(a) / sizeof(a[1]));
}
void TestBubbleSort()
{

	int a[] = { 4, 3, 7, 6, 5, 8, 9, 0, 2, 1, 12, 18, 15, 11 };
	PrintArray(a, sizeof(a) / sizeof(a[1]));
	BubbleSort(a, sizeof(a) / sizeof(a[1]));
	PrintArray(a, sizeof(a) / sizeof(a[1]));
}
void TestInsertSort()
{
	int a[] = { 4, 3, 7, 6, 5, 8, 9, 0, 2, 1, 12, 18, 15, 11 };
	PrintArray(a, sizeof(a) / sizeof(a[1]));
	InsertSort(a, sizeof(a) / sizeof(a[1]));
	PrintArray(a, sizeof(a) / sizeof(a[1]));
	ShellSort(a, sizeof(a) / sizeof(a[1]));
	PrintArray(a, sizeof(a) / sizeof(a[1]));
}
void TestQuickSort()
{
	int a[] = { 4, 3, 7, 6, 5, 8, 9, 0, 2, 1, 12, 18, 15, 11 };
	//int a[] = {2,0,4,9,3,6,8,7,1,5};
	//int a[] = { 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2 };
	//int a[] = {0,2,1,5,4,2};
	PrintArray(a, sizeof(a) / sizeof(a[1]));
	//QuickSortNonR(a, 0, sizeof(a) / sizeof(a[1]) - 1);
	QuickSort(a, 0, sizeof(a) / sizeof(a[1]) - 1);
	PrintArray(a, sizeof(a) / sizeof(a[1]));
}
void TestSelectSort()
{
	int a[] = { 4, 3, 7, 6, 5, 8, 9, 0, 2, 1, 12, 18, 15, 11 };
	//int a[] = { 9, 7, 3, 0, 1 };
	SelectSort(a, sizeof(a) / sizeof(a[1]));
	PrintArray(a, sizeof(a) / sizeof(a[1]));
}
void TestHeapSort()
{
	int a[] = { 4, 3, 7, 6, 5, 8, 9, 0, 2, 1, 12, 18, 15, 11 };
	HeapSort(a, sizeof(a) / sizeof(a[1]));
	PrintArray(a, sizeof(a) / sizeof(a[1]));
}
int main()
{
	//TestInsertSort();
	//TestHeapSort();
	//TestSelectSort();
	//TestBubbleSort();
	//TestQuickSort();
	TestMergeSort();
	return 0;
}
