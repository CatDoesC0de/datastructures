int main()
{
    int SomeInt = 10;

    // (1)
    // A pointer is a variable which the value stores the memory address to
    // another value of a specified type. The default intialization for a
    // pointer is a garbage value.
    int* SomePointer;

    // (2)
    // A pointer is declared by 'type* variable_name' (as shown in section 1
    // with int* SomePointer)

    // We can get the memory-address of SomeInt by using the & operator
    // and initialize SomePointer with the returned address.
    SomePointer = &SomeInt;

    // (3)
    // To acces the variable that the pointer is pointing to, use a * BEFORE
    // the variable name.
    *SomePointer = 3;

    // NOTE: If we didn't assign SomePointer to &SomeInt in section 2,
    // doing *SomePointer = 3 is DANGEROUS as SomePointer would contain a
    // garbage value and may point to memory outside of this process's memory,
    // causing a crash.

    // (4)
    // When creating an array like so, (in most expressions) SomeInts decays to
    // an int* pointer to its first element.
    int SomeInts[3];

    // (5)
    // Pointer arithmetic is used inside contiguous memory blocks (arrays)
    // to index to a particular element.

    int SomeElement = SomeInts[2];
    // The expression SomeInts[2] REALLY means *(SomeInts + 2)

    // However if we literally took some memory address say 8
    // and added 2 to it we would be in the middle of the current integer
    // if the integer is 4 bytes. So the compiler does an automatic scaling by
    // sizeof(type)
    //
    // Like this
    // *(SomeInts + (sizeof(int) * 2));
    //
    // This also explains why array indexing starts at 0 because
    // : *(SomeInts + (sizeof(int) * 0))
    // : *(SomeInts + (4 * 0))
    // : *(SomeInts + (0))
    // : *(SomeInts + (0)) == *(SomeInts)

    // Iterating over and setting each value of SomeInts to 0 in O(n) time

    for (int i = 0; i < 3; i++)
    {
        *(SomeInts + i) = 0;
    }
}
