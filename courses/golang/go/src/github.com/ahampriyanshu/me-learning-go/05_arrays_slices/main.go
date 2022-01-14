package main

import "fmt"

func main(){
	// Arrays
	var fruit [2]string
	fruit[0] = "Apple"
	fruit[1] = "Orange"

	fruitShortHand := [4]string{"Apple", "Orange", "Pears", "Grape"}

	fmt.Println(fruit, fruitShortHand)
	fmt.Println(fruitShortHand[1:3])
	fmt.Println(len(fruit))
}