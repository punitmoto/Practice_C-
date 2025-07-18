#include<iostream>
#include<string>
#include<bits/stdc++.h>

using namespace std;

bool isStrUnique(const std::string& str) {

    if(str.length() > 256) return false;

    bool boolarray[256] = {false};
    for (char c:str) {
        unsigned char value = static_cast<unsigned char>(c);
        //if(boolarray[value]) return false;
        //boolarray[value] = true;
        if(boolarray[c-'a']) return false;
        boolarray[c-'a'] = true;
    }
    return true;
}

//Kadane's Algo.
long long maxSubArray(int arr[], int size) {

    long long sum = 0;
    long max = -99999;
    int start = 0;
    int ansStart = 0;
    int ansEnd = 0;
    
    for(int i = 0; i < size; i++) { 
        
        if(sum == 0) {
            start = i;
        }

        sum += arr[i];

        if(sum > max) {
            max = sum;
            ansStart = start;
            ansEnd = i;
        }

        if(sum < 0) {
            sum = 0;                     
        }        
    }

    for(int i = ansStart; i <= ansEnd; i++) {
        std::cout<<" "<<arr[i]<<" ";
    }

    return max;
}

vector<int> TwoSumArray(int size, vector<int> &arr, int target) {
    unordered_map<int, int> mpp;

    for(int i =0 ; i < size; i++) {
        int num = arr[i];
        int moreNeeded = target - num;
        if(mpp.find(moreNeeded) != mpp.end()) {
            return {mpp[moreNeeded], i};
        }
        mpp[num] = i;
    }
    return {-1,-1};
}

//Search in rotated sorted array
int searchInRotatedArray(int size, vector<int>&arr, int target){
    int low = 0, mid = 0, high = size-1;

    while(low <= high) {
        mid = (low+high)/2;

        if(arr[mid] == target) return mid;
        
        if(arr[low] <= arr[mid]) {
            if(target > arr[low] && target <= arr[mid]) {
                high = mid-1;
            }
            else {
                low = mid+1;
            }
        }
        else {
            if(target >= arr[mid] && target <= arr[high]) {
                low = mid + 1;
            }
            else {
                high = mid-1;
            }
        }
    }
    return -1;
}

int main(){
    
    int arr[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4};
    int size = sizeof(arr)/sizeof(arr[0]);

    int maxsum = maxSubArray(arr, size);

    vector<int> arr1 = {2,6,5,8,11};
    int size = 5;
    int target = 14;

    vector<int>ans = TwoSumArray(size, arr1, target);

    std::string input = "abcdaa";
    //std::cout<<input <<" is "<<isStrUnique(input);
    return 0;
}