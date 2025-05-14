#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
int k = 0, n = 0;
int main() {
    std::map<int, int> groupA, groupB;
    std::map<int, int> beginGroup;
    std::scanf("%d %d", &n, &k);
    std::vector<int> nums(n);
    for (int i = 0; i < k; i++) {
        std::scanf("%d", &nums[i]);
        beginGroup[nums[i]]++;
    }
    for (int i = k; i < n; i++) {
        std::scanf("%d", &nums[i]);
    }
    int i = 0;
    for (const auto& pair : beginGroup) {
        if (i < ((k + 1) / 2)) {
            if (i + pair.second <= ((k + 1) / 2)) {
                groupA[pair.first] = pair.second;
            } else if (i + pair.second > ((k + 1) / 2)) {
                groupA[pair.first] += ((k + 1) / 2) - i;
                groupB[pair.first] += pair.second + i - ((k + 1) / 2);
            }
        } else {
            groupB[pair.first] = pair.second;
        }
        i += pair.second;
    }
    auto oit=std::prev(groupA.end());
    std::printf("%d ",oit->first);
    if (k==1)
    {
        for (int i = k; i < n; i++)
        {
            printf("%d ",nums[i]);
        }
        return 0;
    }
    for (i = k; i < n; i++) { //i位置是待提取元素，待去除元素位置是 i - k
        auto it = std::prev(groupA.end());
        int mid = it->first;
        if (nums[i] > mid) {
            auto gb=groupB.begin();
            if (nums[i - k] <= mid&&nums[i]>gb->first) {/*当加入的元素小于B中最小元素*/
                auto itB = groupB.begin();
                groupA[itB->first]++;                
                groupB[nums[i]]++;
                groupA[nums[i - k]]--;
                itB->second--;
                if (groupA[nums[i - k]] == 0) {
                    groupA.erase(nums[i - k]);
                }

                if (itB->second == 0) {
                    groupB.erase(itB->first);
                }
            }
            else if (nums[i - k] <= mid&&nums[i]<=gb->first)
            {
                groupA[nums[i]]++;
                groupA[nums[i - k]]--;
                if (groupA[nums[i - k]] == 0) {
                    groupA.erase(nums[i - k]);
                }
            }            
            else {
                groupB[nums[i]]++;
                groupB[nums[i - k]]--;
                if (groupB[nums[i - k]] == 0) {
                    groupB.erase(nums[i - k]);
                }
            }
        } else if (nums[i] < mid) {
            if (nums[i - k] > mid) {//删的元素在组B，加的元素在组A，情况唯一，中位数上溢到组B，组A加
                groupA[nums[i]]++;
                groupB[mid]++;
                groupB[nums[i - k]]--;
                it->second--;
                if (groupB[nums[i - k]] == 0) {
                    groupB.erase(nums[i - k]);
                }
                if (it->second == 0) {
                    groupA.erase(it->first);
                }
            } else {
                groupA[nums[i]]++;
                groupA[nums[i - k]]--;
                if (groupA[nums[i - k]] == 0) {
                    groupA.erase(nums[i - k]);
                }
            }
        } else {
            if (nums[i - k] < mid) {
                groupA[nums[i]]++;
                groupA[nums[i - k]]--;
                if (groupA[nums[i - k]] == 0) {
                    groupA.erase(nums[i - k]);
                }
            } else if (nums[i - k] > mid) {
                groupB[nums[i]]++;
                groupB[nums[i - k]]--;
                if (groupB[nums[i - k]] == 0) {
                    groupB.erase(nums[i - k]);
                }
            }
        }
                    // printf("\n删除%d,加入%d\n",nums[i-k],nums[i]);
                    // for (const auto& pair : groupA)
                    // {
                    //     for (int j = 0; j < pair.second; j++)
                    //     {
                    //         std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
                    //     }
                    // }
                    // printf("\n");
                    // for (const auto& pair : groupB)
                    // {
                    //     for (int j = 0; j < pair.second; j++)
                    //     {
                    //         std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
                    //     }
                    // }
        it = std::prev(groupA.end());
        std::printf("%d ", it->first);
    }
    return 0;
}