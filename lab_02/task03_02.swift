import Foundation

func DamerauLevenshteinRecursive(_ firstString: String, _ secondString: String) -> Int {
    let n = firstString.count
    let m = secondString.count
    
    if n == 0 || m == 0 {
        if n != 0 { return n }
        if m != 0 { return m }
        
        return 0
    }
    
    let symbolN = firstString.index(before: firstString.endIndex)
    let symbolM = secondString.index(before: secondString.endIndex)
    
    let a = String(firstString[..<symbolN])
    let b = String(secondString[..<symbolM])
    
    var change = 0
    if firstString[symbolN] != secondString[symbolM] {
        change += 1
    }
    
    let insertOperation = DamerauLevenshteinRecursive(a, secondString) + 1
    let deleteOperation = DamerauLevenshteinRecursive(firstString, b) + 1
    let changeOperation = DamerauLevenshteinRecursive(a, b) + change
    
    if n > 1 && m > 1 {
        let symbolNMinusOne = firstString.index(firstString.endIndex, offsetBy: -2)
        let symbolMMinusOne = secondString.index(secondString.endIndex, offsetBy: -2)
        let c = String(firstString[..<symbolNMinusOne])
        let d = String(secondString[..<symbolMMinusOne])
        
        if firstString[symbolN] == secondString[symbolMMinusOne] && firstString[symbolNMinusOne] == secondString[symbolM] {
            let transposeOperation = DamerauLevenshteinRecursive(c, d) + 1
            return min(insertOperation, deleteOperation, changeOperation, transposeOperation)
        }
    }
    
    return min(insertOperation, deleteOperation, changeOperation)
}


func getStrings() -> [String] {
    let input = readLine()!
    var arr = input.components(separatedBy: " ")
    
    return arr
}

print("\n | proc 2 (Damerau distance) START\nInput strings: ")
var arr = getStrings()
print("Damerau distance:")
print(DamerauLevenshteinRecursive(arr[0], arr[1]))
