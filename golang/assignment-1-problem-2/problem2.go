package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

type Park struct {
	parkname string
	state    string
	area     int
}

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func addPark(parks []Park, parkname string, state string, area int, length int) {
	newPark := Park{parkname, state, area}
	parks[length] = newPark
}

func printList(parks []Park, length int) {
	for index, park := range parks {
		if index == length {
			break
		}
		fmt.Printf("%s [%s] %d\n", park.parkname, park.state, park.area)
	}
}

func printCsvList(output *bufio.Writer, parks []Park, length int) {
	for index, park := range parks {
		if index == length {
			break
		}
		_, ok := fmt.Fprintf(output, "%s, %s, %d\n", park.parkname, park.state, park.area)
		check(ok)
	}
}

func main() {
	args := os.Args[1:]

	if len(args) != 2 {
		panic("Wrong number of parameters.")
	}

	input, ok := os.Open(args[0])
	check(ok)

	outfile, ok := os.Create(args[1])
	check(ok)
	output := bufio.NewWriter(outfile)

	in := bufio.NewScanner(input)

	// Cheating - says to use something like strstream but Go doesn't have that
	separator := regexp.MustCompile(`\s*,\s*`)

	var parks [100]Park
	length := 0

	var bigParks [100]Park
	bigParksLength := 0

	for ; in.Scan(); {
		fields := separator.Split(in.Text(), -1)
		area, ok := strconv.Atoi(fields[2])
		check(ok)

		addPark(parks[:], fields[0], fields[1], area, length)
		length++

		if area > 200000 {
			addPark(bigParks[:], fields[0], fields[1], area, bigParksLength)
			bigParksLength++
		}
	}

	printList(parks[:], length)

	printCsvList(output, bigParks[:], bigParksLength)
	check(output.Flush())
	check(outfile.Close())
}
