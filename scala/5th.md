### Arrays
* Int arrays
```scala
scala> val arr = new Array[Int](10)
arr: Array[Int] = Array(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

scala> arr(0) = 1

scala> arr(1) = 2

scala> arr
res2: Array[Int] = Array(1, 2, 0, 0, 0, 0, 0, 0, 0, 0)

scala> arr.foreach(println)
1
2
0
0
0
0
0
0
0
0
```

* String arrays
```scala
scala> val arr = new Array[String](10)
arr: Array[String] = Array(null, null, null, null, null, null, null, null, null, null)

scala> arr(0) = "0th Index"

scala> arr
res5: Array[String] = Array(0th Index, null, null, null, null, null, null, null, null, null)
```
### Buffer Array
```scala
scala> import scala.collection.mutable.ArrayBuffer
import scala.collection.mutable.ArrayBuffer

scala> val arr = new ArrayBuffer[Int]()
arr: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer()

scala> arr += 100
res6: arr.type = ArrayBuffer(100)

scala> arr += 200
res7: arr.type = ArrayBuffer(100, 200)

scala> arr
res8: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(100, 200)

scala> arr += (300, 400, 500)
res9: arr.type = ArrayBuffer(100, 200, 300, 400, 500)

scala> arr ++= Array(300, 400, 500)
res11: arr.type = ArrayBuffer(100, 200, 300, 400, 500, 300, 400, 500)

scala> arr --= Array(300, 400, 500)
res12: arr.type = ArrayBuffer(100, 200, 300, 400, 500)
```

### Filter
```scala
scala> arr.filter( _ % 2 != 0 ).foreach(println)

scala> arr
res14: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(100, 200, 300, 400, 500)
```
### Sum, Min ans Max
```scala
scala> val arr = new Array [Int](3)
arr: Array[Int] = Array(0, 0, 0)

scala> arr(1) = 2

scala> arr(2) = 3

scala> arr(0) = 1

scala> arr
res5: Array[Int] = Array(1, 2, 3)


scala> arr.sum
res8: Int = 6

scala> arr.max
res9: Int = 3

scala> arr.min
res12: Int = 1
```