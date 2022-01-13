### Sets

* These are also immutable by default
* These don't contain any duplicate elements
```scala
scala> var set =  Set(1, 2, 3, 7)
set: scala.collection.immutable.Set[Int] = Set(1, 2, 3, 7)

scala> val set = Set(1, 1, 1, 2, 4, 5, 5)
set: scala.collection.immutable.Set[Int] = Set(1, 2, 4, 5)

scala> println("First element :" + set.head)
First element :1

scala> println("First element :" + set.tail)
First element :Set(2, 4, 5)

scala> println("Tail element :" + set.tail)
Tail element :Set(2, 4, 5)

scala> println("Is the set empty :" + set.isEmpty)
Is the set empty :false

scala> val set = Set("apples", "oranges", "pears")
set: scala.collection.immutable.Set[String] = Set(apples, oranges, pears)

scala> val fruit1 = Set("apples", "oranges", "pears")
fruit1: scala.collection.immutable.Set[String] = Set(apples, oranges, pears)

scala> val fruit2 = Set("apples", "oranges", "banana")
fruit2: scala.collection.immutable.Set[String] = Set(apples, oranges, banana)

scala> println( "Combined sets :" + (fruit1 ++ fruit2))
Combined sets :Set(apples, oranges, pears, banana)

```