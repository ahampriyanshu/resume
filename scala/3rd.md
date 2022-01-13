### `foreach` loop 
```scala
scala> val str = "Test"
str: String = Test

scala> str.foreach(println)
T
e
s
t
```

### `for` loop
```scala
scala> for ( i <- 1 to 5 ) println(i)
1
2
3
4
5

scala> 1 to 5
res2: scala.collection.immutable.Range.Inclusive = Range(1, 2, 3, 4, 5)

scala> for ( i <- 5 to 1 by -1 ) println(i)
5
4
3
2
1

scala> for ( i <- 1 to 5; j <- 1 to 4 ) println(s"($i, $j)")
(1, 1)
(1, 2)
(1, 3)
(1, 4)
(2, 1)
(2, 2)
(2, 3)
(2, 4)
(3, 1)
(3, 2)
(3, 3)
(3, 4)
(4, 1)
(4, 2)
(4, 3)
(4, 4)
(5, 1)
(5, 2)
(5, 3)
(5, 4)
```
### `if` in `for`
* Inefficient way
```scala
scala> for ( i <- 1 to 5; j <- 1 to 4 ) if(i==j)println(s"($i, $j)")
(1, 1)
(2, 2)
(3, 3)
(4, 4)
```
* Efficient way (For loop with a guard condition)
```scala
scala> for ( i <- 1 to 5; j <- 1 to 4 if i==j)println(s"($i, $j)") 
(1, 1)
(2, 2)
(3, 3)
(4, 4)

scala> for ( i <- 1 to 20 if i % 2 == 0) println(i)2
4
6
8
10
12
14
16
18
20

scala> val x =for ( i <- 1 to 20 if i % 2 == 0) yield(i)
x: scala.collection.immutable.IndexedSeq[Int] = Vector(2, 4, 6, 8, 10, 12, 14, 16, 18, 20)

scala> x
res2: scala.collection.immutable.IndexedSeq[Int] = Vector(2, 4, 6, 8, 10, 12, 14, 16, 18, 20)
```