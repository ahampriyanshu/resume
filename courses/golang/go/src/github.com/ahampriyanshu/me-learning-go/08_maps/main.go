package main

import "fmt"

func main() {
	
	// Define map
    emails := make(map[string]string)

    emails["mike"] = "mike@gmail.com"
    emails["stanhope"] = "stanhope@gmail.com"

	fmt.Println(emails)
	fmt.Println(len(emails))
	fmt.Println(emails["mike"])

	// Delete from map
	delete(emails,"mike")
	fmt.Println(emails)
	fmt.Println()
	//map shorthand method

	email := map[string]string{"mike":"mike@gmail.com","stanhope":"stanhope@gmail.com"}

	fmt.Println(email)
	fmt.Println(len(email))
	fmt.Println(email["mike"])

	// Delete from map
	delete(email,"mike")
	fmt.Println(email)

}	}

