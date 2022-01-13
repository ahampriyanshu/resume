package main

import "fmt"

func main(){

	a := 5
	b := &a

	fmt.Println(a, *b, b, *&a)
	fmt.Printf("Type of a is %T\nType of  b is %T\n", a, b)

	// Change the value with pointer
	*b = 10
	fmt.Println(a)
		
}