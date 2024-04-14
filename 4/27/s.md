3, 9, 1, 5
# after 3
```DOT
digraph tree
{
    3->2
    3->10
    2->1
    2->N1
    10->4
    10->11
    4->N2
    4->6
    6->5
    6->8
    8->7
    8->9
    11->N3
    11->12
    12->N4
    12->13

    N1[label=""]
    N2[label=""]
    N3[label=""]
    N4[label=""]
}
```

# after 9
```DOT
digraph tree
{
    9->3
    9->10
    3->2
    3->4
    2->1
    2->N1
    4->N2
    4->8
    8->6
    8->N3
    6->5
    6->7
    10->N4
    10->11
    11->N5
    11->12
    12->N6
    12->13

    N1[label=""]
    N2[label=""]
    N3[label=""]
    N4[label=""]
    N5[label=""]
    N6[label=""]
}
```

# after 1
```DOT
digraph tree
{
    1->N1
    1->9
    9->2
    9->10
    2->N2
    2->3
    3->N3
    3->4
    4->N4
    4->8
    8->6
    8->N5
    6->5
    6->7
    10->N6
    10->11
    11->N7
    11->12
    12->N8
    12->13
    N1[label=""]
    N2[label=""]
    N3[label=""]
    N4[label=""]
    N5[label=""]
    N6[label=""]
    N7[label=""]
    N8[label=""]
}
```

# after 5
```DOT
digraph tree
{
    5->1
    5->9
    1->N1
    1->2
    2->N2
    2->4
    4->3
    4->N3
    9->6
    9->10
    6->N4
    6->8
    8->7
    8->N5
    10->N6
    10->11
    11->N7
    11->12
    12->N8
    12->13
    N1[label=""]
    N2[label=""]
    N3[label=""]
    N4[label=""]
    N5[label=""]
    N6[label=""]
    N7[label=""]
    N8[label=""]
}
```