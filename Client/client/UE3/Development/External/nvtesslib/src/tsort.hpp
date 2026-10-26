#pragma once

#include <assert.h>

template <class Type>
class TSort
{
public:
    /// sorts the data in ascending order
    static void QSort(Type *data, int count);
};

template <class T>
inline void Swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <class Type>
inline void TSort<Type>::QSort(Type *data, int count)
{
    //  variables used for stack
    assert(count <= 2147483647);   //  stack size restriction
    const int QS_STACK_SIZE = 130; //  should be enough for 32 bit counters
    int stack[QS_STACK_SIZE];
    int stck_top = 0; // top of the stack

    //  variables used for sorting
    int i, j, k;
    int ir = count - 1; //  right element
    int il = 0; //  left element

    //  partitioning element
    Type a;

    for ( ; ; )
    {
        //  insertion sort
        if (ir - il <= 6)
        {
            for (j = il + 1; j <= ir; j++)
            {
                a = data[j];
                for (i = j - 1; i >= il; i--)
                {
                    if (!(a < data[i])) break;
                    data[i + 1] = data[i];
                }
                data[i + 1] = a;
            }
            if (stck_top == 0) break;

            //  pop the stack
            ir = stack[stck_top--];
            il = stack[stck_top--];
        }
        else
        {
            k = (il + ir) >> 1; //  choose median of left, center, and right elements
            //  as partitioning element a. Also rearrange so that
            //  data[il] # data[il+1] # data[ir]
            Swap(data[k], data[il + 1]);
            if (data[ir] < data[il])
                Swap(data[il], data[ir]);
            if (data[ir] < data[il + 1])
                Swap(data[il + 1], data[ir]);
            if (data[il + 1] < data[il])
                Swap(data[il], data[il + 1]);

            i = il + 1; //  initialize pointers for partitioning
            j = ir;
            a = data[il + 1]; //  partitioning element

            for ( ; ; )
            {
                do i++; while (data[i] < a); //  scan up to find element >= a
                do j--; while (a < data[j]); //  scan down to find element < a
                if (j < i) break; //  pointers crossed. Partitioning complete
                Swap(data[i], data[j]); //  exchange elements
            }

            data[il + 1] = data[j]; //  insert partitioning element
            data[j] = a;
            stck_top += 2;
            assert(stck_top < QS_STACK_SIZE);

            if (ir - i + 1 >= j - il)
            {
                stack[stck_top] = ir;
                stack[stck_top - 1] = i;
                ir = j - 1;
            }
            else
            {
                stack[stck_top] = j - 1;
                stack[stck_top - 1] = il;
                il = i;
            }
        }
    }
}
