/*
1. Implement a sorting algorithm using the chrono library profile, sometimes using varying sample sizes
*/

#include <vector>

void BubbleSort(int vectorToSort[], int size)
{
    bool sorted = true;
    do
    {
        sorted = true;  // if it can make one whole run without changing anything, it is sorted
        for (int i = 0; i < size - 1; i++)
        {
            if (vectorToSort[i + 1] < vectorToSort[i])
            {
                int temp = vectorToSort[i];
                vectorToSort[i] = vectorToSort[i + 1];
                vectorToSort[i + 1] = temp;
                sorted = false;
            }
        }
    } while (!sorted);
    
}

/*
* Proved not worth the limited amount of time I had
std::vector<int> MergeSortRecursion(std::vector<int> vectorToSort, int leftIndex, int rightIndex);

std::vector<int> MergeSort(std::vector<int> vectorToSort)
{
    // Declare left variable to 0 and right variable to n - 1
    // Find mid by medium formula.mid = (left + right) / 2
    // Call merge sort on(left, mid)
    // Call merge sort on(mid + 1, rear)
    // Continue till left is less than right
    //  Then call merge function to perform merge sort.

    int leftIndex = 0;
    int rightIndex = vectorToSort.size() - 1;
    //int middleIndex = (leftIndex + rightIndex) / 2;

    //std::vector<int> vectorToSort(arrayToSort, arrayToSort + size);


    return MergeSortRecursion(vectorToSort, leftIndex, rightIndex);
}

std::vector<int> MergeSortRecursion(std::vector<int> vectorToSort, int leftIndex, int rightIndex)
{
    if (leftIndex >= rightIndex)
    {
        return vectorToSort;
    }

    else
    {
        int middleIndex = (leftIndex + rightIndex) / 2;

        // left
        std::vector<int> left;

        std::vector<int> left = MergeSortRecursion(vectorToSort, leftIndex, middleIndex);

        // right
        std::vector<int> right = MergeSortRecursion(vectorToSort, middleIndex+1, rightIndex);

        std::vector<int> merged;
        int leftIndex = 0, rightIndex = 0;

        // merge the two halfs
        while (leftIndex <= left.size() && rightIndex <= right.size())
        {
            if (left[leftIndex] < right[rightIndex])
            {
                merged.push_back(left[leftIndex]);
                leftIndex++;
            }
            else
            {
                merged.push_back(right[rightIndex]);
                rightIndex++;
            }
        }

        return merged;
    }
}
*/