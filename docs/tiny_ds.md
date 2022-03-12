# tiny_ds.h
A collection of generic data structures
## Array

#### Description
The array is the base of all `tiny_ds.h` structures. A simple "stretchy buffer" implementation, it keeps track of its current capacity
and number of elements so it knows when to allocate more space once it gets full. Internally, the array actually looks like this:

     capacity  length
    +--------+--------+-------+-------+-------+-------+
    |   -2   |   -1   |   0   |   1   |   2   |  ...  |
    +--------+--------+-------+-------+-------+-------+
                       \
                         User pointer

The array API functions are all macros, and with macros come no type checking and hard to debug errors, but they are the only way to do
type-agnostic implementations in C. The user will just have to be careful with what they pass as arguments to these macros. Most of
them try to do some checking to see if the passed in array is `NULL` to avoid segmentation faults, but some care is still required.

### Creating / Freeing
There is no `init` or `create` macro for an array, because the macros for insertion check to see if `a` is `NULL` and allocate space if it is.
`tds_array_reserve` can be used to set an initial capacity if needed.

```c
// Define a array of type int like this
int *array = NULL;

// Reserve 32 spaces in the array
tds_array_reserve(array, 32);

// Free the array when it's no longer needed
tds_array_free(array);
```

#### Macros
```c
void tds_array_reserve(T *a, int n)
void tds_array_free(T *a);
```

### Inserting / Deleting
Inserting an element into an array takes a few steps. First, if required, uninitialized elements are allocated at the end of the array
with `tds_array_pushn`. Then, the rest of the elements are shifted down using `tds_array_insn` to make room for the new element. Finally,
the element is inserted at the specified index with `tds_array_ins`. Data can be inserted using any of these steps. For example, multiple
elements can be appended to an array at once like this:
```c
int *array = NULL;
int to_insert[5] = {1, 2, 3, 4, 5};

int *ptr = tds_array_pushn(array, 5);
for (int i = 0; i < 5; i++)
        ptr[i] = to_insert[i];
// or memcpy(ptr, to_insert, sizeof to_insert);
```
`tds_array_del{n}` deletes elements in an array the way an `std::vector` does in C++, shifting the other elements down and overwriting the
deleted element with the one from the next index. This keeps the array tightly packed with no gaps and keeps the order. `tds_array_delswap`
deletes an element by swapping it with the last element in the array then popping the last element off the array, similar to the "swap and pop" idiom
in C++. This allows an element to be deleted in O(1) time, but changes the order of the array. `tds_array_delswap` is much faster than
`tds_array_del` and should probably be used, unless the array's order needs to be maintained.
```c
// Building off of the insertion example above
tds_array_del(array, 3);
tds_array_deln(array, 2, 4);

int last = tds_array_pop(array); // last == 0
int len = tds_array_len(array); // len == 0
tds_array_free(array);
```

#### Macros
```c
// Inserting
T    *tds_array_insn(T *a, int index, int n);
void  tds_array_ins(T *a, int index);
T    *tds_array_pushn(T *a, int n);
void  tds_array_push(T *a);

// Deleting
void  tds_array_deln(T *a, int index, int n);
void  tds_array_del(T *a, int index);
void  tds_array_delswap(T *a, int index);
T    *tds_array_popn(t *a, int n);
T     tds_array_pop(T *a);
void  tds_array_clear(T *a);
```

### Accessing / Iterating
Since the array is just a normal C array, access into it happens as it would with any other array.
```c
float *array = NULL;
tds_array_push(array, 5.0f);
tds_array_push(array, 10.0f);

float x = array[1]; // x == 10.0f
```

Array elements can also be set like a normal array.
```c
array[1] = 15.0f;
```

Looping through an array can be done with a regular for loop by testing against `tds_array_len(array)`, or by using the `tds_array_foreach` macro.
```c
// Normal for loop
for (size_t i = 0; i < tds_array_len(array); i++) {
        printf("%d\n", array[i]);
}

// Notice how the curly brackets are inside the macro as a parameter
tds_array_foreach(int i, array, {
        printf("%d\n", i);
});

// The curly brackets are not required
tds_array_foreach(int i, array,
        printf("%d\n", i);
);

// The "iterator" can be any type
tds_array_foreach(my_custom_type c, array, {
        print_my_custom_type(c);
});
```

#### Macros
```c
T *tds_begin(T *a);
T *tds_end(T *a);

tds_array_foreach(T it, T *array, ...);
```
## Map

#### Description
A generic hashmap implementation. A hashmap is really a specialized array, where the array type is a struct that has a key and value field.
Since a hashmap is an array, it stores the capacity and length before the returned pointer, along with 2 other pieces of data. An element is used
to represent the "default" or "empty" value to test against when determining whether a bucket is open. The other element is used as a temporary
element to store the key and value so the address of the key can be taken even if it's not an rvalue.

     capacity  length   default   temp
    +--------+--------+--------+--------+-------+-------+-------+
    |   -4   |   -3   |   -2   |   -1   |   0   |   1   |  ...  |
    +--------+--------+--------+--------+-------+-------+-------+
                                        \
                                          User pointer
