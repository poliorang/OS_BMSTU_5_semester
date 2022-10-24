//for i in 0..<10 {
//    print(Int.random(in: -10...10), terminator: " ")
//}
//print("")

func shakerSort<T: Comparable>(_ array: [T]) -> [T] {
    var resultArray = array
    var left = 0
    var right = resultArray.count - 1

    while left <= right {
        for i in left..<right {
            if resultArray[i] > resultArray[i + 1] {
                resultArray.swapAt(i, i + 1)
            }
        }
        right -= 1

        for i in stride(from: right, to: left, by: -1) {
            if resultArray[i - 1] > resultArray[i] {
                resultArray.swapAt(i, i - 1)
            }
        }
        left += 1
    }
    
    return resultArray
}

print("\n | proc 1 (sort array) START\nInput array: ")
let input = readLine()!
var array = input.split(separator: " ").map({Int($0) ?? 0})
print("Sorted array:")
array = shakerSort(array)
for elem in array { print(elem, terminator: " ") }
print("")
