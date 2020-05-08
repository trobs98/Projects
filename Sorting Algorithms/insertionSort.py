import sys

size = int(sys.argv[1])
array_1 = list(reversed(range(size)))

def insertionSort(array):
    for k in range(0,20):
        print("before: ",array[k])
    for j in range(1,len(array)):
        key = array[j]
        i = j - 1
        while (i >= 0 and array[i] > key):
            array[i + 1] = array[i]
            i = i - 1
        array[i + 1] = key

def isSorted(array):
    for i in range(0,20):
        print("after: ",array[i])

print("ARRAY WITH ", size," INTS: ", "\n")
insertionSort(array_1)
isSorted(array_1)
