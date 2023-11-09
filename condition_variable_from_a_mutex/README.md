# Project Outputs 📊

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

In this scenario, the project runs without using the condvar (conditional variable) synchronization mechanism. The producer generates elements, and the consumer attempts to consume them. However, without proper synchronization, the output demonstrates issues like multiple consumers consuming the same element and potential data races.

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

Here, the project incorporates the condvar synchronization mechanism, resolving some of the issues observed in the previous scenario. The consumer now waits for the producer to generate data using `condvar_wait`. This ensures that the consumer only attempts to consume when there is data available, improving synchronization.

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

In this final scenario, the project further refines synchronization by implementing a more sophisticated approach. The producer and consumer threads are now more efficiently synchronized. The consumer thread waits when there is no data to consume and wakes up when the producer generates new data. This approach minimizes unnecessary CPU consumption, leading to a more optimal and synchronized execution.