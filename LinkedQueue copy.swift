//
//  LinkedQueue.swift
//  Algos4
//
//  Created by Tim Shull on 9/13/16.
//  Copyright © 2016 Tim Shull. All rights reserved.
//

import Foundation


open class LinkedQueueNode<T:Equatable>: Equatable, CustomStringConvertible {
    typealias NodeType = LinkedQueueNode<T>
    
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
    
    public static func ==(lhs: LinkedQueueNode<T>, rhs: LinkedQueueNode<T>) -> Bool {
        return lhs.next! == rhs.next! && lhs.value == rhs.value && lhs === rhs
    }
    
    public static func !=(lhs: LinkedQueueNode<T>, rhs: LinkedQueueNode<T>) -> Bool {
        return !(lhs == rhs)
    }
    
    public static func ==(lhs: LinkedQueueNode<T>?, rhs: LinkedQueueNode<T>) -> Bool {
        return lhs!.next! == rhs.next! && lhs!.value == rhs.value && lhs === rhs
    }
    
    public static func !=(lhs: LinkedQueueNode<T>?, rhs: LinkedQueueNode<T>) -> Bool {
        return !(lhs == rhs)
    }
}


struct LinkedQueueIterator<T:Comparable>: IteratorProtocol {
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

enum LinkedQueueError: Error {
    case badPeak
}

class LinkedQueue<Item:Comparable>: Sequence, CustomStringConvertible {
    typealias NodeType = Node<Item>?
    typealias Iterator = BagIterator<Item>
    
    fileprivate var first: NodeType
    fileprivate var last: NodeType
    fileprivate var n: Int
    
    init() {
        first = nil
        last = nil
        n = 0
        assert(check(), "Linked queue invariant check failed")
    }
    
    func isEmpty() -> Bool {
        return first == nil
    }
    
    func size() -> Int {
        return n
    }
    
    func peek() throws -> Item {
        if isEmpty() {
            throw LinkedQueueError.badPeak
        }
        return first!.value
    }
    
    func enqueue(_ item: Item) {
        let oldlast = last
        last = Node<Item>(value: item)
        last!.value = item
        if isEmpty() {
            first = last
        } else {
            oldlast!.next = last
        }
        n += 1
        assert(check(), "Linked queue invariant check failed")
    }
    
    func dequeue() throws -> Item? {
        if isEmpty() {
            throw LinkedQueueError.badPeak
        }
        let item = first?.value
        first = first?.next
        n -= 1
        if isEmpty() {
            last = nil
        }
        assert(check(), "Linked queue invariant check failed")
        return item
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
            if last != nil {
                return false
            }
        } else if n == 1 {
            if first == nil || last == nil {
                return false
            }
            if first !== last {
                return false
            }
            if first?.next != nil {
                return false
            }
        } else {
            if first == nil || last == nil {
                return false
            }
            if first === last {
                return false
            }
            if first?.next == nil {
                return false
            }
            if last?.next != nil {
                return false
            }
            
            var numberOfNodes = 0
            var x = first
            repeat {
                numberOfNodes += 1
                x = x?.next
            } while x != nil && numberOfNodes <= n
            
            if (numberOfNodes != n) {
                return false
            }
            
            var lastNode = first
            while lastNode!.next != nil {
                lastNode = lastNode?.next
            }
            
            if (last !== lastNode) {
                return false
            }
         
        }
        return true
    }
        
}
