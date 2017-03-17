//
// Created by Tim Shull on 11/28/16.
// Copyright (c) 2016 Tim Shull. All rights reserved.
//

import Foundation

public func bagStats() {
    let numbers: LinkedBag<Double> = LinkedBag<Double>();
    print("Enter floating point values (i.e. 1.123) to add to the bag: ")
    while let line = readLine(strippingNewline: true)?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines), line != "" {
        if let val = Double(line) {
            numbers.add(item: val)
        }
    }
    let n = numbers.size
    var sum = 0.0
    for elem in numbers {
        sum += elem.item
    }
    let mean: Double = sum / Double(n)
    for elem in numbers {
        sum += (elem.item - mean) * (elem.item - mean)
    }
    let std = sqrt(sum / Double(n - 1))
    print("Mean: \(String(format: "%.2f", mean))")
    print("Std dev: \(String(format: "%.2f", std))")
}

public func readInts() -> [Int?] {
    let q: LinkedQueue<Int> = LinkedQueue<Int>()
    print("Add integer values to the queue: ")
    while let line = readLine(strippingNewline: true)?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines), line != "" {
        if let val = Int(line) {
            q.enqueue(item: val)
        }
    }
    let n = q.size
    var a: [Int?] = [Int?]()
    a.reserveCapacity(n)

    for i in 0 ... n {
        do {
            try a[i] = q.dequeue()
        } catch {
            print("Error dequeuing")
        }
    }
    return a
}

public func reverseStack() {
    let stack: LinkedStack<Int> = LinkedStack<Int>()
    while let line = readLine(strippingNewline: true)?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines), line != "" {
        if let val = Int(line) {
            stack.push(item: val)
        }
    }

    for i in stack {
        print(i)
    }
}

public func djikstraTwoStack() {
    let ops: LinkedStack<String> = LinkedStack<String>()
    let vals: LinkedStack<Double> = LinkedStack<Double>()

    while let line = readLine(strippingNewline: true)?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines), line != "" {
        switch line {
        case "(":
            break
        case "+", "-", "*", "/", "sqrt":
            ops.push(item: line)
        case ")":
            var op: String!
            var v: Double!
            do {
                op = try ops.pop()
                v = try vals.pop()
            } catch {
                print("An error occurred while popping from the ops queue")
                break
            }
            do {
                switch op {
                case "+":
                    v = try vals.pop() + v
                case "-":
                    v = try vals.pop() - v
                case "*":
                    v = try vals.pop() * v
                case "/":
                    v = try vals.pop() / v
                case "sqrt":
                    v = sqrt(v)
                default:
                    print("Unrecognized op: \(op)")
                }
            } catch {
                print("An error occurred while evaluating using the vals queue")
            }
            vals.push(item: v)
        default:
            vals.push(item: Double(line)!)
        }
    }
    do {
        print("Evaluated value: \(try vals.pop())")
    } catch {
        print("Unable to pop the total value")
    }
}

public func resizeArray<Element>(array: inout [Element?], newSize: Int) {
    var tmp = [Element?]()
    tmp.reserveCapacity(newSize)
    let maxIndex = array.count < newSize ? array.count : newSize
    for i in 0 ... maxIndex {
        tmp[i] = array[i]
    }
    array = tmp
}