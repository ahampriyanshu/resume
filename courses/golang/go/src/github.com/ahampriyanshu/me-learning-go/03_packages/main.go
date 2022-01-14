package main

import ("fmt" 
"math"
"github.com/priyanshumay/me-learning-go/03_packages/strutil"
)

func main(){

	fmt.Println(math.Floor(2.7))
	// 2
	fmt.Println(math.Ceil(2.7))
	//3
	
	fmt.Println(math.Sqrt(16))
	fmt.Println(math.Pow(2, 10))

	fmt.Println(strutil.Reverse("gnirts a si sihT"))
}