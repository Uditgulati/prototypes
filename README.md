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