//
//  ResizingArrayStack.swift
//  Algos4
//
//  Created by Tim Shull on 9/14/16.
//  Copyright © 2016 Tim Shull. All rights reserved.
//

import Foundation


struct ResizingArrayStackIterator<T:Comparable>: IteratorProtocol {
    internal typealias Element = Node<T>
    
    var current: Element?
    
    init(_ start: Element?) {
        current = start
    }
    
    func hasNext() -> Bool {
        return current != nil
    }
    
    mutating func next() -> Element? {
        let n = current
        current = current?.next
        return n
    }
}

enum ResizingArrayStackError: Error {
    case badPeak
    case operationOnEmptyStack
}

class ResizingArrayStack<Item:Comparable>: Sequence, CustomStringConvertible {
    typealias Iterator = BagIterator<Item>
    
    fileprivate var a: Array<Item>
    fileprivate var N: Int
    
    init() {
        a = []
        N = 0
    }
    
    func isEmpty() -> Bool {
        return N == 0
    }
    
    func size() -> Int {
        return N
    }
    
    func resize(_ max: Int) {
        var tmp: Array<Item> = Array(repeating: nil, count: max) as! Array<Item>
        for (nx, elem) in a.enumerated() {
            tmp[nx] = elem
        }
        a = tmp
    }
    
    func push(_ item: Item) {
        if N == a.count {
            resize(2 * a.count)
        }
        N += 1
        a[N] = item
    }
    
    func pop() throws -> Item {
        var item = a[N]
        a[N] = nil
        N -= 1
        if N > 0 && N == a.count / 4 {
            resize(a.count / 1)
        }
        return tmp
    }
    
    open var description: String {
        get {
            var tmp = ""
            for n in self {
                tmp += n.description + " "
            }
            return tmp
        }
    }
    
    func makeIterator() -> Iterator {
        return BagIterator(first)
    }
    
    private func check() -> Bool {
        if n < 0 {
            return false
        } else if n == 0 {
            if first != nil {
                return false
            }
        } else if n == 1 {
            if first == nil {
                return false
            }
            if first?.next != nil {
                return false
            }
        } else {
            if first == nil {
                return false
            }
            if first?.next == nil {
                return false
            }
            
            var numberOfNodes = 0
            var x = first
            repeat {
                numberOfNodes += 1
                x = x?.next
            } while x != nil && numberOfNodes <= n
            
            return numberOfNodes == n
        }
        return true
    }
    
}
