def doCacheMath(subRays, maxDepth, iter_):
    if iter == 0: return maxDepth
    for i in range(1, maxDepth):
        gsize = subRays ** i
        if (iter_ % gsize) != 0: return i + 1
    return -1


