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

### If we don't write data type scala automatically inferres the data type of variable nut that doesn,t make it dynamically typed language instead it is called `` Type Inference``

