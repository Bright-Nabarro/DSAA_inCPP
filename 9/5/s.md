## initial

| v | known |d_v    |p_v|
|---|-------|-------|---|
| A | F     | 0     | 0 |
| B | F     | INF   | 0 |
| C | F     | INF   | 0 |
| D | F     | INF   | 0 |
| E | F     | INF   | 0 |
| F | F     | INF   | 0 |
| G | F     | INF   | 0 |


## A poped
| v | known |d_v    |p_v|
|---|-------|-------|---|
| A | T     | 0     | 0 |
| B | F     | 5     | A |
| C | F     | 3     | A |
| D | F     | INF   | 0 |
| E | F     | INF   | 0 |
| F | F     | INF   | 0 |
| G | F     | INF   | 0 |


## C poped
| v | known |d_v    |p_v|
|---|-------|-------|---|
| A | T     | 0     | 0 |
| B | F     | 5     | A |
| C | T     | 3     | A |
| D | F     | 7     | C |
| E | F     | 7     | C |
| F | F     | INF   | 0 |
| G | F     | INF   | 0 |


## B poped
| v | known |d_v    |p_v|
|---|-------|-------|---|
| A | T     | 0     | 0 |
| B | T     | 5     | A |
| C | T     | 3     | A |
| D | F     | 7     | C |
| E | F     | 3     | B |
| F | F     | INF   | 0 |
| G | F     | 1     | B |


## G poped
| v | known |d_v    |p_v|
|---|-------|-------|---|
| A | T     | 0     | 0 |
| B | T     | 5     | A |
| C | T     | 3     | A |
| D | F     | 7     | C |
| E | F     | 1     | G |
| F | F     | INF   | 0 |
| G | T     | 1     | B |


## E poped
| v | known |d_v    |p_v|
|---|-------|-------|---|
| A | T     | 0     | 0 |
| B | T     | 5     | A |
| C | T     | 3     | A |
| D | F     | 2     | E |
| E | T     | 1     | G |
| F | F     | 1     | E |
| G | T     | 1     | B |


## F poped
| v | known |d_v    |p_v|
|---|-------|-------|---|
| A | T     | 0     | 0 |
| B | T     | 5     | A |
| C | T     | 3     | A |
| D | F     | 2     | E |
| E | T     | 1     | G |
| F | T     | 1     | E |
| G | T     | 1     | B |


## D poped
| v | known |d_v    |p_v|
|---|-------|-------|---|
| A | T     | 0     | 0 |
| B | T     | 5     | A |
| C | T     | 3     | A |
| D | T     | 2     | E |
| E | T     | 1     | G |
| F | T     | 1     | E |
| G | T     | 1     | B |


```
A->B: A->B
A->C: A->C
A->D: A->B->G->E->D
A->E: A->B->G->E
A->F: A->B->G->E->F
A->G: A->B->G
```

