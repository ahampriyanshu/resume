package main

import ("fmt"
		"strconv")

// Defining a struct "Person"
type Person struct{
	// firstName string
	// lastName string
	// city string
	// gender string

	firstName, lastName, city, gender string
	age int
}

// Greeting method (value reciever)
func (p Person) greet() string {
	return "Hello, my name is " + p.firstName + " " + p.lastName + " and I am " + strconv.Itoa(p.age) + " old "	 + p.gender
}

// hasBithday method (pointer reciever)
func (p *Person) hasBithday() {
	p.age++
}

// getMarried (pointer reciever)
func (p *Person) getMarried(spouseLastName string)  {
	if p.gender == "male"{
		return
	} else {
		p.lastName =  spouseLastName
	}
}

func main() {

	person1 := Person{firstName: "Joe", lastName: "Biden", city: "d-one", gender: "male", age: 70}
	person2 := Person{firstName: "Hilary", lastName: "Rodham", city: "d-one", gender: "female", age: 60}

	fmt.Println(person1)
	fmt.Println(person2)
	fmt.Println(person1.firstName)

	fmt.Println(person1.greet())
	person1.hasBithday()
	fmt.Println(person1.greet())

	fmt.Println(person2.greet())
	person2.getMarried("Clinton")
	fmt.Println(person2.greet())

	
}