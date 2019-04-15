# prototypes

## Examples

+	**Indexing:**

```

2 2
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
0 0
index: 0
value: 1

```

```

2 2
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
0 1
index: 1
value: 2

```

```

2 2
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
1 0
index: 2
value: 3

```


+	**Slicing:**

```

2 2
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
0 0:1
Slice is:
No. of dimensions: 1
[1, 2]

```

```

2 2
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
0:1 1
Slice is:
No. of dimensions: 1
[2, 4]

```

```

2 2
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
1 1
Slice is:
No. of dimensions: 0
4

```

```

2 2
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
0:1 0:1
Slice is:
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]

```

*To extract a row:*

```

2 2
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
1 :
Slice is:
No. of dimensions: 1
[3, 4]

```

*To extract a column:*

```

2 2 
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
: 0
Slice is:
No. of dimensions: 1
[1, 3]

```

*Set slice:*

```

2 2
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
1 : 10
Enter value: Slice is:
No. of dimensions: 1
[3, 4]
Final matrix is:
No. of dimensions: 2
[
  [1, 2], 
  [10, 10]
]

```

```

2 2
1 2 3 4
No. of dimensions: 2
[
  [1, 2], 
  [3, 4]
]
: 0 10
Enter value: Slice is:
No. of dimensions: 1
[1, 3]
Final matrix is:
No. of dimensions: 2
[
  [10, 2], 
  [10, 4]
]

```