# Outputs

## Without condvar

```yaml
0: Produzindo 0
1: Consumindo 0
1: Consumindo 0
0: Produzindo 1
1: Consumindo 0
0: Produzindo 2
0: Produzindo 3
1: Consumindo 0
0: Produzindo 4
1: Consumindo 4
0: Produzindo 5
1: Consumindo 5
0: Produzindo 6
1: Consumindo 6
0: Produzindo 7
1: Consumindo 7
0: Produzindo 8
1: Consumindo 8
0: Produzindo 9
1: Consumindo 9
```

## With condvar

```yaml
0: Produzindo 0
1: Consumindo 0
0: Produzindo 1
1: Consumindo 1
0: Produzindo 2
1: Consumindo 2
0: Produzindo 3
1: Consumindo 3
0: Produzindo 4
1: Consumindo 4
0: Produzindo 5
1: Consumindo 5
0: Produzindo 6
1: Consumindo 6
0: Produzindo 7
1: Consumindo 7
0: Produzindo 8
1: Consumindo 8
0: Produzindo 9
1: Consumindo 9
```

## With condvar and after last Update

```yaml
T.1: Produzindo 0#1636880259
T.2: Consumindo 0#1636880259
T.1: Produzindo 1#1780994943
T.2: Consumindo 1#1780994943
T.1: Produzindo 2#1554935115
T.2: Consumindo 2#1554935115

> T.2: Consumidor esperando

T.1: Produzindo 3#1065977462
T.2: Consumindo 3#1065977462
T.1: Produzindo 4#1574620560
T.2: Consumindo 4#1574620560
T.1: Produzindo 5#1206769939
T.2: Consumindo 5#1206769939
T.1: Produzindo 6#1346802505
T.2: Consumindo 6#1346802505
T.1: Produzindo 7#1232062155
T.2: Consumindo 7#1232062155
T.1: Produzindo 8#1231314711
T.2: Consumindo 8#1231314711

> T.2: Consumidor esperando

T.1: Produzindo 9#1553925285
T.2: Consumindo 9#1553925285
```