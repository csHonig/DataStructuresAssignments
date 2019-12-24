package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func insertAtIndex(nums []int, atIndex int, val int) {
	for i := 99; i > atIndex; i-- {
		nums[i] = nums[i-1]
	}
	nums[atIndex] = val
}

func insertIntoSortedArray(nums []int, numEntries int, newValue int) {
	// Initial case

	if numEntries == 0 {
		nums[0] = newValue
		return
	}

	// End

	if newValue >= nums[numEntries-1] {
		nums[numEntries] = newValue
		return
	}

	// Beginning

	if newValue < nums[0] {
		insertAtIndex(nums, 0, newValue)
		return
	}

	// OK, it's between some two existing numbers

	for i := 1; i < numEntries; i++ {
		if nums[i-1] < newValue && newValue <= nums[i] {
			insertAtIndex(nums, i, newValue)
			return
		}
	}
}

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func printArray(nums []int, numEntries int) {
	for index, val := range nums {
		if index == numEntries {
			break
		}
		if index > 0 {
			fmt.Print(", ")
		}
		fmt.Print(val)
	}
	fmt.Print("\n")
}

func main() {
	args := os.Args[1:]

	if len(args) != 1 {
		panic("Failed to open the file.")
	}

	var nums [100]int

	input, ok := os.Open(args[0])
	check(ok)

	in := bufio.NewScanner(input)

	numRead := 0
	for ; in.Scan() ; {
		val, _ := strconv.Atoi(in.Text())
		insertIntoSortedArray(nums[:], numRead, val)
		numRead++
		printArray(nums[:], numRead)
	}
}
