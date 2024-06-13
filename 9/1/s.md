
### indegree initial

|vec| indegree  |
|---|-----------|
|s  |0          |
|t  |3          |
|A  |2          |
|B  |1          |
|C  |3          |
|D  |2          |
|E  |4          |
|F  |2          |
|G  |1          |
|H  |1          |
|I  |2          |


### output s
```
s
```

|vec| indegree  |
|---|-----------|
|t  |3          |
|A  |1          |
|B  |1          |
|C  |3          |
|D  |1          |
|E  |4          |
|F  |2          |
|G  |0          |
|H  |1          |
|I  |2          |


### output G
```
s -> G
```
|vec| indegree  |
|---|-----------|
|t  |3          |
|A  |1          |
|B  |1          |
|C  |3          |
|D  |0          |
|E  |3          |
|F  |2          |
|H  |0          |
|I  |2          |

### output D
```
s -> G -> D 
```
|vec| indegree  |
|---|-----------|
|t  |3          |
|A  |0          |
|B  |1          |
|C  |3          |
|E  |2          |
|F  |2          |
|H  |0          |
|I  |2          |

### output A
```
s -> G -> D -> A
```
|vec| indegree  |
|---|-----------|
|t  |3          |
|B  |0          |
|C  |3          |
|E  |1          |
|F  |2          |
|H  |0          |
|I  |2          |

### output B
```
s -> G -> D -> A -> B
```
|vec| indegree  |
|---|-----------|
|t  |3          |
|C  |2          |
|E  |1          |
|F  |2          |
|H  |0          |
|I  |2          |

### output H
```
s -> G -> D -> A -> B -> H
```
|vec| indegree  |
|---|-----------|
|t  |3          |
|C  |2          |
|E  |0          |
|F  |2          |
|I  |1          |

### output E
```
s -> G -> D -> A -> B -> H -> E
```
|vec| indegree  |
|---|-----------|
|t  |3          |
|C  |1          |
|F  |1          |
|I  |0          |

### output I
```
s -> G -> D -> A -> B -> H -> E -> I
```
|vec| indegree  |
|---|-----------|
|t  |2          |
|C  |1          |
|F  |0          |

### output F
```
s -> G -> D -> A -> B -> H -> E -> I -> F
```
|vec| indegree  |
|---|-----------|
|t  |1          |
|C  |0          |


### output C then t
```
s -> G -> D -> A -> B -> H -> E -> I -> F -> C -> t
```

