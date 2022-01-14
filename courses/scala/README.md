# Scala Crash Course

## Installation

### First check whether if JAVA is installed on your linux machine
`` java --version ``

### Install scala 
`` sudo apt-get install scala ``

### Start scala's REPL
`` scala ``

### If everything worked fine , something like this should appear in your terminal
```scala
Welcome to Scala 2.11.12 (OpenJDK 64-Bit Server VM, Java 11.0.7).
Type in expressions for evaluation. Or try :help.

scala>
```

* Use `` :q `` to exit REPL

## Session 1

### Use REPL for arithmetic calculation
```scala
Welcome to Scala 2.11.12 (OpenJDK 64-Bit Server VM, Java 11.0.7).
Type in expressions for evaluation. Or try :help.

scala> 60 + 9
res0: Int = 69

scala> 93 - 24
res1: Int = 69

scala> 13 * 5 + ( 32 / 8 )
res2: Int = 69
```

### Const and Variables

* val : Immutable variable ( Read Only)
* var : mutable variable ( Read-Write)

```scala
scala> val x : Int = 10
x: Int = 10

scala> x = 11
<console>:12: error: reassignment to val
       x = 11
         ^
scala> var x : Int = 10
x: Int = 10

scala> x =11
x: Int = 11

```

### Data Types
```scala
scala> val x : Int = 10
x: Int = 10

scala> val x : String = "scala"
x: String = scala

scala> val x : Float  =10f
x: Float = 10.0

scala> val x : Double = 10
x: Double = 10.0

scala> val x : Boolean = true
x: Boolean = true
```

* If we don't write data type, scala automatically inferes the data type of variable not that doesn,t make it dynamically typed language instead it is called `` Type Inference``

## Session 2

### Data types in Scala

Index |  Data Type | Description
| -- | -- | --
1 | Any | Super type
2 | AnyVal | Represent value type
3 | AnyRef | Subtype of reference type
4 | Double | 64 bit float
5 | Float  | 32 bit float
6 | Long | 64 bit signed value
7 | Int | 32 bit signed value
8 | Short | 16 bit signed value
9 | Byte | 8 bit signed value
10 | Unit | Void
11 | Boolean | True/False
12 | Char | 16 bit unsigned unicode
13 | Null | Null
14 | Nothing | Subtype of everytype

### Assigning Block Expression

* Using ``;`` as delimeter
```scala
scala> val x = { val a = 30; val b = 20 ; a + b }
x: Int = 50
 ```

* Using `` new line `` as delimeter
```scala 
scala> val x = {
     | val b = 30
     | val a = 20
     | a + b }
x: Int = 50
```
### lazy loading
```scala
scala> lazy val x = 1000000
x: Int = <lazy>

scala> x * 2
res1: Int = 2000000

scala> val x = { 1 to 100000}.toList
x: List[Int] = List(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, ...
scala> x.reduce(_+_)
res2: Int = 705082704

scala> lazy val x = { 1 to 100000}.toList
x: List[Int] = <lazy>

scala> x.reduce(_+_)
res3: Int = 705082704
```

## Session 3

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

## Session 4

### Functions

* def **funcName**( **params**: type): return type {
    **expression**
}


```scala
scala> def arearect(l: Float, b: Float): Float ={
     | l * b
     | }
arearect: (l: Float, b: Float)Float

scala> arearect(13, 17)
res0: Float = 221.0
```
* Use `Unit` in return type if function doesn't return anything i.e void function
```scala
scala> def areaRect(l: Float, b: Float): Unit ={
     | println( l *b)
     | }
areaRect: (l: Float, b: Float)Unit

scala> areaRect(40.5f, 3.5f)
141.75
```

* Boolean function
```scala
scala> def isEvenNumber(x: Int):Boolean ={
     | x % 2 == 0
     | }
isEvenNumber: (x: Int)Boolean

scala> isEvenNumber(9)
res2: Boolean = false

scala> isEvenNumber(8)
res3: Boolean = true
```

* Passing default arguments

```scala
scala> def areaRect(l: Int, b: Int = 10):Int = { l*b }
areaRect: (l: Int, b: Int)Int

scala> areaRect(10)
res4: Int = 100
```

* Overwriting default argument
```scala
scala> areaRect(10, 12)
res5: Int = 120

scala> def areaRect(l: Int = 10, b: Int):Int = { l*b }
areaRect: (l: Int, b: Int)Int

scala> areaRect(12)
<console>:13: error: not enough arguments for method areaRect: (l: Int, b: Int)Int.
Unspecified value parameter b.
       areaRect(12)
               ^

scala> areaRect(b = 12)
res7: Int = 120

scala> areaRect(12 , 10)
res8: Int = 120
```

## Session 5

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

## Session 6

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

## Session 7

### Map
```scala
scala> val map = Map( 0 -> "OFF", 1 -> "ON" )
map: scala.collection.immutable.Map[Int,String] = Map(0 -> OFF, 1 -> ON)

scala> map
res13: scala.collection.immutable.Map[Int,String] = Map(0 -> OFF, 1 -> ON)

scala> map(1)
res14: String = ON

scala> map(32)
java.util.NoSuchElementException: key not found: 32
  at scala.collection.MapLike$class.default(MapLike.scala:228)
  at scala.collection.AbstractMap.default(Map.scala:59)
  at scala.collection.MapLike$class.apply(MapLike.scala:141)
  at scala.collection.AbstractMap.apply(Map.scala:59)
  ... 32 elided

scala> map.get(1)
res17: Option[String] = Some(ON)
```
* Hashtable/Map are always unordered and hence element can not be inserted in between.

## Session 8

### Tuples
```scala
tu: (Int, String, String) = (7,Bond,England)

scala> tu._1
res1: Int = 7

scala> tu._3
res2: String = England
```

## Session 9

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