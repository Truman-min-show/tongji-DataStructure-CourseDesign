from math import ceil, floor


def getShellGaps(N):
    
    gaps, k = [], 0
    getKth = lambda k: floor(N / 2 ** k)
    while getKth(k) > 1:
        gaps.append(getKth(k))
        k += 1
    return gaps + [1]


def getCiuraGaps(*args):
   
    return [1750, 701, 301, 132, 57, 23, 10, 4, 1]


def getTokudaGaps(N):
    
    gaps, k = [], 1
    getKth = lambda k: ceil((9 * (9 / 4) ** (k - 1) - 4) / 5)
    while getKth(k) <= N:
        gaps = [getKth(k)] + gaps
        k += 1
    return gaps


def getKnuthGaps(N):
   
    gaps, k = [], 0
    getKth = lambda k: (3 ** k - 1) // 2
    while getKth(k) < ceil(N / 3):
        gaps = [getKth(k)] + gaps
        k += 1
    return gaps



GAPS = {
    "ciura": getCiuraGaps,
    "shell": getShellGaps,
    "tokuda": getTokudaGaps,
    "knuth": getKnuthGaps
}


def shellSort(array, *args, gapType="ciura"):
   

    gaps = GAPS.get(gapType, "ciura")(len(array))
    for gap in gaps:
        for i in range(gap, len(array)):
            temp, j = array[i], i
            while j >= gap and array[j - gap] > temp:
                yield array, j, j - gap, -1, -1
                array[j] = array[j - gap]
                j -= gap
            yield array, -1, -1, i, j
            array[j] = temp
