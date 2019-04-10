#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <sstream>//stringstream ss(s)
#include <sys/time.h>
using namespace std;








template <typename T>
void displayVector(vector<T> &arr);

class heapSortClass{
private:
    int k;
    int size;
public:
    vector<int> a;
private:
    void maxHeap(int n);
    void buildMaxHeap();
    void heapSort();

public:
    heapSortClass(vector<int> &nums, int k);
    int addElement(int val);
};


void heapSortClass::maxHeap(int n)
{
    int leftChild, rightChild, largest;
    leftChild = 2 * n;
    rightChild = 2 * n + 1;
    if (leftChild<=size&&a[leftChild-1]>a[n-1])
        largest = leftChild;
    else
        largest = n;
    if (rightChild<=size&&a[rightChild-1]>a[largest-1])
        largest = rightChild;
    if (largest != n)
    {

        swap(a[n-1], a[largest-1]);
//        displayVector(a);
        maxHeap(largest);

    }

}

void heapSortClass::buildMaxHeap()
{
    int i = a.size() / 2;
    for (i; i > 0; i--)
        maxHeap(i);

}

void heapSortClass::heapSort()
{
    int i;
    buildMaxHeap();
    for (i = size; i>1; i--)
    {
        swap(a[0], a[i-1]);
//        displayVector(a);
        size = size - 1;
        maxHeap(1);


    }

}

heapSortClass::heapSortClass(vector<int> &nums, int k){
    k = k;
    size = nums.size();
    a = nums;
    heapSort();
}

int heapSortClass::addElement(int val){
    a.push_back(val);
    size = a.size();
    heapSort();
    vector<int>::iterator it = a.end()-k;
    return *it;

}




template <typename T>
void displayVector(vector<T>& vector_) {
    //一定要添加typename关键字来说明这里的T是代表类型,而不是数据
    for (typename  vector<T>::iterator it=vector_.begin(); it != vector_.end(); it++){
        cout << *it<< " ";
    }
    cout << endl;
}

template <typename  T>
void swap1(T &a, T &b){
    T temp=a;
    a = b;
    b = temp;
}

template <typename T>
void bubbleSort(vector<T> &arr){
    bool out=false;
    for (int i=0; i<arr.size()-1 && !out; i++) {
        out = true;
        for (int j = i+1; j< arr.size(); j++){
            if (arr[i]>arr[j]){
                swap(arr[i], arr[j]);
                out = false;
            }
        }
    }
}

template <typename T>
vector<T> *mergeTwoVector(vector<T> *v1, vector<T> *v2){
    int size1 = v1->size();
    int size2 = v2->size();

//    vector<T> *re = (vector<T>)malloc(sizeof(T));
    vector<T> *re = new vector<T>;
    int i=0, j=0;
    while (i <size1 && j<size2) {
        if (*(v1->begin()+i) < *(v2->begin()+j)){
            re->push_back((*v1)[i]);
            i++;
        }
        else{
            re->push_back((*v2)[j]);
            j++;
        }
    }
    if (i<size1) {
        while (i < size1) {
            re->push_back((*v1)[i]);
            i++;
        }
    }
    else if(j<size2) {
        while (j < size2) {
            re->push_back((*v2)[j]);
            j++;
        }
    }
    else{
        ;
    }
    return re;
}

template <typename T>
vector<T> *mergeSort(vector<T> &arr){

    if (arr.size()==1){
        vector<T> *re = new vector<T>;
        re->push_back(arr[0]);
        return re;
    }
    else if (arr.size() ==2){
        vector<T> *re = new vector<T>;
        re->push_back(arr[0]);
        re->push_back(arr[1]);
        if ((*re)[0]>(*re)[1])
            swap1((*re)[0], (*re)[1]);
        return re;
    }
    else{
        typename vector<T>::const_iterator left_start= arr.begin();
        typename vector<T>::const_iterator left_end = arr.begin()+arr.size()/2;
        vector<T> left_arr(left_start, left_end);
//        displayVector(left_arr);
        typename vector<T>::const_iterator right_start= arr.begin()+arr.size()/2;
        typename vector<T>::const_iterator right_end = arr.end();
        vector<T> right_arr(right_start, right_end);
//        displayVector(right_arr);
        vector<T> *left_re;
        left_re = mergeSort(left_arr);
        vector<T> *right_re;
        right_re = mergeSort(right_arr);
        vector<T> *re;
        re = mergeTwoVector(left_re, right_re);
        delete left_re;
        delete right_re;
//        displayVector(*re);
        return re;
    }
}
template <typename T>
vector<T> *quickSort_ptr(vector<T> &nums) {

    int size = nums.size();
    if (nums.size()==0){
        vector<T> *re = new vector<T>;
        return re;
    }
    else if (nums.size() < 2) {
        vector<T> *re = new vector<T>;
        re->push_back(nums[0]);
        return re;
    } else if (size < 3) {
        vector<T> *re = new vector<T>;
        re->push_back(nums[0]);
        re->push_back(nums[1]);
        if ((*re)[0] > (*re)[1])
            swap1((*re)[0], (*re)[1]);
        return re;
    }
    vector<T> left_arr;
    vector<T> right_arr;
    for (typename vector<T>::iterator iter = nums.begin() + 1; iter != nums.end(); iter++) {
        if (*iter < nums[0])
            left_arr.push_back(*iter);
        else {
            right_arr.push_back(*iter);
        }
    }
    vector<T> *re = new vector<T>;
    vector<T> *left_re = quickSort_ptr(left_arr);
    vector<T> *right_re = quickSort_ptr(right_arr);
    re->insert(re->end(), left_re->begin(), left_re->end());
    re->insert(re->end(), nums[0]);
    re->insert(re->end(), right_re->begin(), right_re->end());
//    delete left_re;
//    delete right_re;
//    displayVector(left_re);
    return re;

}

template <typename T>
vector<T> quickSort(vector<T> &nums) {

    int size = nums.size();
    if (nums.size()==0){
        vector<T> re;
        return re;
    }
    else if (nums.size() < 2) {
        vector<T> re;
        re.push_back(nums[0]);
        return re;
    } else if (size < 3) {
        vector<T> re;
        re.push_back(nums[0]);
        re.push_back(nums[1]);
        if (re[0] > re[1])
            swap1(re[0], re[1]);
        return re;
    }
    vector<T> left_arr;
    vector<T> right_arr;
    for (typename vector<T>::iterator iter = nums.begin() + 1; iter != nums.end(); iter++) {
        if (*iter < nums[0])
            left_arr.push_back(*iter);
        else {
            right_arr.push_back(*iter);
        }
    }
    vector<T> left_re = quickSort(left_arr);
    vector<T> right_re = quickSort(right_arr);
    left_re.insert(left_re.end(), nums[0]);
    left_re.insert(left_re.end(), right_re.begin(), right_re.end());
    return left_re;

}

void temp(){
    vector<int> nums;
    string s;
    getline(cin, s);
    int a;
    stringstream ss(s);
    while (ss>>a) {
//		cout << a << endl;
        nums.push_back(a);
    }
    string line;
    while (getline(ss, line, ' '))//按空格分割
    {
        if (!line.empty())
            cout << line << endl;
    }
    displayVector(nums);

}
template <typename T>
vector<T> getRandomVector(int n, T range){
    vector<T> re;
    unsigned  seed = (unsigned)time(NULL);
    srand(seed);
    typename  vector<T>::iterator iter=re.end();
    for (int i=0; i<n; i++){
        re.push_back((T)rand()%range);
    }
    return re;
}

template <typename T>
vector<T> getZeroVector_bad(int n, T num){
    vector<T> re;
    typename  vector<T>::iterator iter=re.end();
    for (int i=0; i<n; i++){
        re.insert(iter, num);
        iter = re.end();
    }
    return re;
}

template <typename T>
vector<T> getZeroVector(int n, T num){
    vector<T> re;
    typename  vector<T>::iterator iter=re.end();
    for (int i=0; i<n; i++){
        re.push_back(num);
    }
    return re;
}

inline unsigned get_cost_time(timeval t0){
    unsigned timeUsed;
    timeval t1;
    gettimeofday(&t1, NULL);
    timeUsed=1000000*(t1.tv_sec-t0.tv_sec)+t1.tv_usec-t0.tv_usec;
    return  timeUsed;
}

template <typename T>
void quickSort1(vector<T> &nums, int l, int r) {
    if (l>=r)
        return;
    int i=l+1, j=r, x=nums[l];
    vector<T> left_arr;
    vector<T> right_arr;

    while (i < j) {
        while (i <= j && nums[i] <= x) {//从左向右找第一个大于x的数
            left_arr.push_back(nums[i]);
            i++;
        }
        if (i<=j){
            right_arr.push_back(nums[i]);
            i++;
        }
        while (i <= j && nums[j] >= x) {//从右向左找到第一个小于x的
            right_arr.push_back(nums[j]);
            j--;
        }
        if (i<=j){
            left_arr.push_back(nums[j]);
            j--;
        }
    }
    left_arr.insert(left_arr.end(), x);
    left_arr.insert(left_arr.end(), right_arr.begin(), right_arr.end());
    nums = left_arr;
    quickSort1(nums, l, i-1);
    quickSort1(nums, i+1, r);
    nums = nums;
    return;
}

int sortTask() {
    struct timeval tv_begin, tv_end;
    unsigned timeUsed;
    bool dis = false;
    cout<<"prepare data----------------------"<<endl;
    gettimeofday(&tv_begin, NULL);
    vector<int> nums(getRandomVector(10000, 1000));
    if (dis) {
        displayVector(nums);
    }
    cout<<get_cost_time(tv_begin)<<" us"<<endl;
    cout<<endl;

//    vector<int> bubbleNums(nums);
//    cout<<"bubbleSort----------------------"<<endl;
//    if (dis) {
//        displayVector(nums);
//    }
//    gettimeofday(&tv_begin, NULL);
//    bubbleSort(bubbleNums);
//    if (dis) {
//        displayVector(bubbleNums);
//    }
//    cout<<get_cost_time(tv_begin)<<" us"<<endl;
//    cout<<endl;

    cout<<"mergeSort----------------------"<<endl;
    if (dis) {
        displayVector(nums);
    }
    gettimeofday(&tv_begin, NULL);
    vector<int> *mergeSortresults = mergeSort(nums);
    gettimeofday(&tv_end, NULL);
    if (dis) {
        displayVector(*mergeSortresults);
    }
    cout<<get_cost_time(tv_begin)<<" us"<<endl;
    cout<<endl;

//
//    cout<<"quickSort----------------------"<<endl;
//    if (dis) {
//        displayVector(nums);
//    }
//    gettimeofday(&tv_begin, NULL);
//    vector<int> quickSortre = quickSort(nums);
//    gettimeofday(&tv_end, NULL);
//    if (dis) {
//        displayVector(quickSortre);
//    }
//    cout<<get_cost_time(tv_begin)<<" us"<<endl;
//    cout<<endl;
//
//    cout<<"quickSortptr----------------------"<<endl;
//    if (dis) {
//        displayVector(nums);
//    }
//    gettimeofday(&tv_begin, NULL);
//    vector<int> *re1 = quickSort_ptr(nums);
//    gettimeofday(&tv_end, NULL);
//    if (dis) {
//        displayVector(*re1);
//    }
//    cout<<get_cost_time(tv_begin)<<" us"<<endl;


//    cout<<"quickSort1----------------------"<<endl;
//    vector<int> quickSort1Nums(nums);
//    if (dis) {
//        displayVector(quickSort1Nums);
//    }
//    gettimeofday(&tv_begin, NULL);
//    quickSort1(quickSort1Nums, 0, quickSort1Nums.size()-1);
//    gettimeofday(&tv_end, NULL);
//    if (dis) {
//        displayVector(quickSort1Nums);
//    }
//    cout<<get_cost_time(tv_begin)<<" us"<<endl;
//    cout<<endl;

    cout<<"heapSortClass----------------------"<<endl;
    vector<int> heapSortNums(nums);
    if (dis) {
        displayVector(heapSortNums);
    }
    gettimeofday(&tv_begin, NULL);
    heapSortClass *heapSortSolution = new heapSortClass(heapSortNums, 1);
    gettimeofday(&tv_end, NULL);
    if (dis) {
        displayVector(heapSortSolution->a);
    }
    cout<<get_cost_time(tv_begin)<<" us"<<endl;
    cout<<endl;

    cout<<"cppSortClass----------------------"<<endl;
    vector<int> cppSortNums(nums);
    if (dis) {
        displayVector(cppSortNums);
    }
    gettimeofday(&tv_begin, NULL);
    sort(cppSortNums.begin(), cppSortNums.end());
    gettimeofday(&tv_end, NULL);
    if (dis) {
        displayVector(cppSortNums);
    }
    cout<<get_cost_time(tv_begin)<<" us"<<endl;
    cout<<endl;



    return 0;
}

template <typename T>
void displayarr(T arr[], int size){
    for (int i=0; i< size; i++){
        cout<<arr[i] << " ";
    }
    cout<<endl;
}




void taskHeapSort(){

    vector<int> a({ 9, 12, -3, 0, 6, 8, 15, 7});
    
    heapSortClass *heapSortSolution = new heapSortClass(a, 1);
    displayVector(heapSortSolution->a);
    cout<<heapSortSolution->addElement(2)<<endl;
    cout<<heapSortSolution->addElement(2)<<endl;
    cout<<heapSortSolution->addElement(2)<<endl;
    cout<<heapSortSolution->addElement(2)<<endl;

}


int main()
{
//    taskHeapSort();
    sortTask();
}


