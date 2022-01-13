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