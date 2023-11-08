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
T.1: Produzindo 0#528979626
T.2: Consumindo 0#528979626
T.1: Produzindo 1#2125759249
T.2: Consumindo 1#2125759249
T.1: Produzindo 2#2097746451
T.2: Consumindo 2#2097746451
T.1: Produzindo 3#1585569158
T.2: Consumindo 3#1585569158
T.1: Produzindo 4#536262883
T.2: Consumindo 4#536262883
T.1: Produzindo 5#2128891769
T.2: Consumindo 5#2128891769

> T.2: Consumidor esperando

T.1: Produzindo 6#1058918916
T.2: Consumindo 6#1058918916
T.1: Produzindo 7#1053238523
T.2: Consumindo 7#1053238523
T.1: Produzindo 8#72153840
T.2: Consumindo 8#72153840
T.1: Produzindo 9#1508811972
T.2: Consumindo 9#1508811972
```