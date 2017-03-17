//
//  LinkedStack.swift
//  Algos4
//
//  Created by Tim Shull on 9/14/16.
//  Copyright © 2016 Tim Shull. All rights reserved.
//

import Foundation


open class LinkedStackNode<T:Equatable>: Equatable, CustomStringConvertible {
    typealias NodeType = LinkedStackNode<T>
    
    var value: T
    var next: NodeType? = nil
    open var description: String {
        get {
            return "Node(\(value))"
        }
    }
    
    init(value: T) {
        self.value = value
    }
    
    public static func ==(lhs: LinkedStackNode<T>, rhs: LinkedStackNode<T>) -> Bool {
        return lhs.next! == rhs.next! && lhs.value == rhs.value && lhs === rhs
    }
    
    public static func !=(lhs: LinkedStackNode<T>, rhs: LinkedStackNode<T>) -> Bool {
        return !(lhs == rhs)
    }
    
    public static func ==(lhs: LinkedStackNode<T>?, rhs: LinkedStackNode<T>) -> Bool {
        return lhs!.next! == rhs.next! && lhs!.value == rhs.value && lhs === rhs
    }
    
    public static func !=(lhs: LinkedStackNode<T>?, rhs: LinkedStackNode<T>) -> Bool {
        return !(lhs! == rhs)
    }
}


struct LinkedStackIterator<T:Comparable>: IteratorProtocol {
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

enum LinkedStackError: Error {
    case badPeak
    case operationOnEmptyStack
}

class LinkedStack<Item:Comparable>: Sequence, CustomStringConvertible {
    typealias NodeType = Node<Item>?
    typealias Iterator = BagIterator<Item>
    
    fileprivate var first: NodeType
    fileprivate var n: Int
    
    init() {
        first = nil
        n = 0
        assert(check(), "Linked queue invariant check failed")
    }
    
    func isEmpty() -> Bool {
        return first == nil
    }
    
    func size() -> Int {
        return n
    }
    
    func push(_ item: Item) {
        let oldFirst = first
        first = Node<Item>(value: item)
        first?.value = item
        first?.next = oldFirst
        n += 1
        assert(check(), "Linked stack invariant check failed")
    }
    
    func pop() throws -> Item {
        if isEmpty() {
            throw LinkedStackError.operationOnEmptyStack
        }
        let tmp = first?.value
        first = first?.next
        n -= 1
        assert(check(), "Linked stack invariant check failed")
        return tmp!
    }
    
    func peek() throws -> Item {
        if isEmpty() {
            throw LinkedStackError.badPeak
        }
        return first!.value
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
