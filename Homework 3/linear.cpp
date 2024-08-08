//
//  main.cpp
//  HW3 - linear
//


// Return true if the somePredicate function returns true for at
// least one of the array elements; return false otherwise.
bool anyTrue(const double a[], int n)
{
    // base case: gone through all elements and no calls to some Predicate return true
    if (n <= 0)
        return false;
    if (n == 1)
        return somePredicate(*a);
    
    if (somePredicate(*a))
        return true;
    
    
    return anyTrue(a+1, n-1);  // This is not always correct.
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if (n <= 0)
        return 0;
    
    if (n == 1)
    {
        return somePredicate(*a);
    }
    
    int i = countTrue(a + 1, n - 1);
    return (somePredicate(*a) + i);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if (n <= 0)
        return -1;
    if (somePredicate(*a))
    {
            return 0; // I THINK THIS IS RIGHT???? WALK THROUGH
    }
    
    int k = firstTrue((a + 1), n-1);
    
    if (k == -1)
        return -1;
    else
        return k + 1;
    
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told that no doubles are to
// be considered in the array, return -1.
int indexOfMinimum(const double a[], int n)
{
    if (n <= 0)
        return -1;
    if (n == 1)
        return 0;
    
    int i = a[0]; // value of 1st element
    
    int k = indexOfMinimum(a + 1, n - 1);
    
    int j = a[k + 1];
    
    if (i < j)
        return 0;
    else
        return k + 1;

}

// If all n1 elements of a1 appear in the n2 element array a2, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 is not a
// not-necessarily-contiguous subsequence of a2), return false.
// (Of course, if a1 is empty (i.e., n1 is 0), return true.)
// For example, if a2 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a1 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a1 is
//    50 30 20
// or
//    10 20 20
bool isIn(const double a1[], int n1, const double a2[], int n2)
{
    if (n1 <= 0) // a1 is an empty array
        return true;
    if (n2 == 0)
        return false;

    
    if (*a1 == *a2)
    {
       return isIn(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    
    else // theyre not equal
        return isIn(a1, n1, a2 + 1, n2 - 1);
        

}
