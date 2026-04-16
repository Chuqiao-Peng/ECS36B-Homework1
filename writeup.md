# Google Test And Debugging Writeup

## Things I Thought To Test
1. See if we can find the index of the minimum value in an array.
2. Swap two values and see if the swap was successful.
3. Check that we can sort an array into ascending order.
4. Verify copying an array creates a new independent array.
5. Confirm command-line inputs are correctly parsed into integers.
...

## Bugs

### Bug 1

### Location

Line 36 in formatting.cpp

```c++
sscanf(argv[i], "%d", ar_out[i]);
```

### How the bug was located

Since Max and I completed the project in the wrong order, we did not begin with writing tests first.
Instead, we manually reviewed the implementation files in src, going through each function and line of code.
Using prior programming knowledge and expected program behavior, we looked for logical inconsistencies, incorrect pointer usage, and memory-related mistakes.
We then confirmed suspected issues using compiler error messages, failed test cases, and unexpected runtime behavior.

### Description

The format specifier %d expects a pointer to an integer (int*), but ar_out[i] is an integer value, not an address. 
Therefore, sscanf does not know where to store the parsed value.

### Fix 

sscanf must store the parsed number into memory, so we must pass the address of the destination variable.

```c++
sscanf(argv[i], "%d", &((*ar_out)[i]));
```

### Bug 2

### Location

Line 36 in sorting.cpp, inside function copy_array(int* ar, int len)

```c++
int* copy = ar;
```

### How the bug was located

Since Max and I completed the project in the wrong order, we did not begin with writing tests first. 
Instead, we manually reviewed the implementation files in src, going through each function and line of code. 
Using prior programming knowledge and expected program behavior, we looked for logical inconsistencies, incorrect pointer usage, and memory-related mistakes. 
We then confirmed suspected issues using compiler error messages, failed test cases, and unexpected runtime behavior.
The bug was identified when modifying the copied array also modified the original array. 
This indicated that both pointers were referencing the same memory instead of creating a true copy.

### Description

This line copies only the pointer, not the data. 
Both copy and ar point to the same memory location, so changes to copy also change ar.

### Fix

Allocate new memory for copy, then copy each element from ar. 
This creates a copy of the array so modifications to copy do not affect ar.

```c++
int* copy = (int*)malloc(sizeof(int) * len);
  for (int i = 0; i < len; ++i) {
    copy[i] = ar[i];
  }
  return copy;
}
```

### Bug 3

### Location

Lines 69-71 in sorting.cpp, inside function print_ar(int* ar, int len)

```c++
int* temp = a;
a = b;
b = temp;
```

### How the bug was located

The swap function executed without errors, but the array values remained unchanged after calling the function.

### Description

Since Max and I completed the project in the wrong order, we did not begin with writing tests first.
Instead, we manually reviewed the implementation files in src, going through each function and line of code.
Using prior programming knowledge and expected program behavior, we looked for logical inconsistencies, incorrect pointer usage, and memory-related mistakes.
We then confirmed suspected issues using compiler error messages, failed test cases, and unexpected runtime behavior.
The current code swaps pointer addresses instead of the values stored at those addresses.
Since a and b are passed by value (the pointer itself is copied), swapping them inside the function does not affect the original variables.

### Fix

Swap the values at the memory locations by dereferencing the pointers. 
This correctly swaps the values stored at the memory locations pointed to by a and b.

```c++
int temp = *a;
*a = *b;
*b = temp;
```