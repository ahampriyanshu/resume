package main

import "fmt"

func main(){
	ids := []int{51, 56, 1, 23, 10, 49, 786}

	//looping ids

	for i, id := range ids {
		fmt.Printf("%d - ID: %d\n", i, id)
	}

	fmt.Println()
	// If not using index
	
		// for i, id := range ids {
		// 	fmt.Printf("%d - ID: %d\n", i, id)
		// }
	// Will throw error because i is declared is never used
	// Follow this approach 

	for _, id := range ids {
		fmt.Printf("ID: %d\n", id)
	}

	// Adding ids together

	sum := 0
	for _, id := range ids {
		sum += id
	}
	fmt.Println("Sum :", sum)

	// Range with map
	emails := map[string]string{"mike":"mike@gmail.com", "doughlas":"doughlas@gmail.com", "doe":"doe@thefamiy.netflix"}

	for k, v := range emails {
	fmt.Printf("%s : %s \n", k, v)
	}

	for k, v := range emails {
		fmt.Println("Name :" + k + " Mail Id :" + v)
	}
}