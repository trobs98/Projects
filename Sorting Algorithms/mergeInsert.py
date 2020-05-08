import sys

size = int(sys.argv[1])
k = int(sys.argv[2])
array_1 = list(reversed(range(size)))

def insertionSort(array, index1, index2):
    for j in range(index1, index2 + 1):
        key = array[j]
        i = j - 1
        while (i >= index1 and array[i] > key):
            array[i + 1] = array[i]
            i = i - 1
        array[i + 1] = key

def merge_sort(array, k):

    for i in range(0,20):
        print("before: ", array[i])
    merge_sort2(array,0,len(array)-1, k)

def merge_sort2(array,first,last,k):
    if first < last:
        middle = (first +last)//2
        if(middle - first) > k:
            merge_sort2(array, first, middle,k)
            merge_sort2(array, middle+1, last,k)
            merge(array, first, middle+1,last)
        else:
            insertionSort(array, first, middle)
            insertionSort(array, middle+1, last)
            merge(array,first,middle+1,last)

def merge(array, first, middle, last):
    L = array[first:middle]
    R = array[middle:last+1]
    L.append(999999999)
    R.append(999999999)
    i = j = 0
    for k in range (first, last +1):
        if L[i] <= R[j]:
            array[k] = L[i]
            i += 1
        else:
            array[k] = R[j]
            j += 1


def isSorted(array):
    for i in range(0,20):
        print("after: ",array[i])

print("\n","ARRAY WITH ", size, " INTS: ", "\n")
merge_sort(array_1,k)
isSorted(array_1)
