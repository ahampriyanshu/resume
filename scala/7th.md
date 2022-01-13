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