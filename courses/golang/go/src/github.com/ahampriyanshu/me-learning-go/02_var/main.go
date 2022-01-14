package main

import "fmt"

func main(){

	var name = "Bill Burr"

	shortname, height :="Burr", 5.10
	// short hand method
	// pay attention while printing out `height`
	var age = 53

	var isCool = true
	// var is mutable 
	const isNotCool = false
	// const is immutable

	fmt.Println(name, age , shortname, height, isCool)
	fmt.Printf("%T\n", name)
	fmt.Printf("%T\n", age)
}