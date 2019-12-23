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

func main() {
	var nums [100]int
	in := bufio.NewScanner(os.Stdin)
	numRead := 0
	for ; in.Scan(); numRead++ {
		val, _ := strconv.Atoi(in.Text())
		/// ooooh slices
		insertIntoSortedArray(nums[:], numRead, val)
	}
	fmt.Printf("array: %v", &nums)
}
