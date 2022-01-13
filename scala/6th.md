### List 

``List in Scala are immutable``
* Int List
```scala
scala> val list = 1 :: 2 :: 3 :: Nil
list: List[Int] = List(1, 2, 3)

scala> val list = List(1, 2, 3)
list: List[Int] = List(1, 2, 3)

scala> val x = List(2)
x: List[Int] = List(2)

scala> list
res0: List[Int] = List(1, 2, 3)

scala> val y = 1 :: x
y: List[Int] = List(1, 2)

scala> val originalList = List(5, 1, 4, 3, 2)
originalList: List[Int] = List(5, 1, 4, 3, 2)

scala> val newList = originalList.filter(_>2)
newList: List[Int] = List(5, 4, 3)

scala> import scala.collection.mutable.ListBuffer
import scala.collection.mutable.ListBuffer

scala> val li = ListBuffer(1, 2, 3, 4, 5, 6, 7, 8, 9)
li: scala.collection.mutable.ListBuffer[Int] = ListBuffer(1, 2, 3, 4, 5, 6, 7, 8, 9)

scala> li.remove(0)
res2: Int = 1

scala> li
res3: scala.collection.mutable.ListBuffer[Int] = ListBuffer(2, 3, 4, 5, 6, 7, 8, 9)

scala> val li = List.range(0, 10, 2)
li: List[Int] = List(0, 2, 4, 6, 8)

scala> val li = List.fill(3)("w")
li: List[String] = List(w, w, w)

scala> val li = List.tabulate(5)(n => n + n)
li: List[Int] = List(0, 2, 4, 6, 8)

scala> val a = List(1, 2, 3)
a: List[Int] = List(1, 2, 3)

scala> val b = List(4, 5, 6)
b: List[Int] = List(4, 5, 6)

scala> val c = a ::: b
c: List[Int] = List(1, 2, 3, 4, 5, 6)
```

* String List 
```scala

scala> var flowers = new ListBuffer[String]()
flowers: scala.collection.mutable.ListBuffer[String] = ListBuffer()


scala> flowers += "Rose"
res6: scala.collection.mutable.ListBuffer[String] = ListBuffer(Rose)

scala> flowers += "Tulip"
res7: scala.collection.mutable.ListBuffer[String] = ListBuffer(Rose, Tulip)

scala> flowers += "Lilly"
res8: scala.collection.mutable.ListBuffer[String] = ListBuffer(Rose, Tulip, Lilly)

scala> flowers
res10: scala.collection.mutable.ListBuffer[String] = ListBuffer(Rose, Tulip, Lilly)

scala> flowers --=Seq("Lilly")
res11: scala.collection.mutable.ListBuffer[String] = ListBuffer(Rose, Tulip)

scala> flowers
res12: scala.collection.mutable.ListBuffer[String] = ListBuffer(Rose, Tulip)
```