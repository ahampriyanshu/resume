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