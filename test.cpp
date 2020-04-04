#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;


    //获取k第一次出现的下标
    int getFirst(int data[], int k, int len) {
        int start = 0, end = len-1;
        int mid;
        while (start <= end) {
            mid = (start + end) / 2;
            if (data[mid] < k) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }

        }
        // start指向第一个小于k的数的下标，while循环结束，返回的start表示k第一次出现的下标。
        // 如果k不存在，则返回第一个大于k的数的下标。
        return data[start];
    }

    //获取k最后一次出现的下标
    int getLast(int data[], int k,int len) {
        int start = 0, end = len-1;
        int mid;

        while (start <= end) {
            mid = (start + end) / 2;
            if (data[mid] <= k) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }

        }
        // end指向第一个大于k的数的下标，while循环结束，返回的end表示k最后一次出现的下标。
        // 如果k不存在，则返回第一个小于k的数的下标。
        return data[end];
    }


    int main() {
        int arr1[8] = {1, 2, 3, 3, 3, 3, 4, 6};
        int arr2[6] = {3, 3, 3, 3, 4, 5};
        int arr3[5] = {1, 2, 3, 4, 6};
        printf("%d\n", getFirst(arr1,0,8));
        printf("%d\n", getLast(arr1,7,8));
    }
