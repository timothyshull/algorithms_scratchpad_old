//
//  LinkedQueue.swift
//  AlgorithmsMaster
//
//  Created by Tim Shull on 10/4/16.
//  Copyright © 2016 Tim Shull. All rights reserved.
//

import Foundation


class LinkedQueueNode<Item:Equatable>: Equatable, CustomStringConvertible {
    internal typealias ValueType = Item
    internal typealias NodeType = LinkedQueueNode<Item>

    var item: Item? = nil
    var next: NodeType? = nil

    open var description: String {
        get {
            return "Node(\(item))"
        }
    }

    init() {
    }

    init(_ value: Item) {
        item = value
    }

    public static func ==(lhs: NodeType, rhs: NodeType) -> Bool {
        return lhs.next == rhs.next && lhs.item == rhs.item
    }

    public static func !=(lhs: NodeType, rhs: NodeType) -> Bool {
        return !(lhs == rhs)
    }
}


struct LinkedQueueIterator<Item:Comparable>: IteratorProtocol {
    internal typealias Element = LinkedQueueNode<Item>

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
    typealias NodeType = LinkedQueueNode<Item>
    typealias Iterator = LinkedQueueIterator<Item>

    private var first: NodeType?
    private var last: NodeType?
    private var n: Int

    open var description: String {
        get {
            var tmp = ""
            for n in self {
                tmp += n.description + " "
            }
            return tmp
        }
    }

    init() {
        first = nil
        last = nil
        n = 0
        assert(check(), "LinkedQueue invariant check failed during initialization")
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
        return first!.item!
    }

    func enqueue(_ item: Item) {
        let oldLast = last
        last = NodeType(item)
        if isEmpty() {
            first = last
        } else {
            oldLast!.next = last
        }
        n += 1
        assert(check(), "LinkedQueue invariant check failed when calling enqueue")
    }

    func dequeue() throws -> Item? {
        if isEmpty() {
            throw LinkedQueueError.badPeak
        }
        let item = first?.item!
        first = first?.next
        n -= 1
        if isEmpty() {
            last = nil
        }
        assert(check(), "LinkedQueue invariant check failed when calling dequeue")
        return item
    }

    func makeIterator() -> Iterator {
        return LinkedQueueIterator(first)
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
            while lastNode?.next != nil {
                lastNode = lastNode?.next
            }

            if (last != lastNode) {
                return false
            }

        }
        return true
    }
}

func testLinkedQueue() {
    print("Running the main function for a linked queue")

    let queue: LinkedQueue<String> = LinkedQueue()
    var inputString: String?
    repeat {
        print("Input a new string: ")
        inputString = readLine(strippingNewline: true)
        if inputString != nil {
            queue.enqueue(inputString!)
        }
    } while inputString != nil

    print("The size of the queue is: \(queue.size())")

    repeat {
        do {
            try print(queue.dequeue()! + " ")
        } catch {
            print("An error occurred while dequeueing an item from the LinkedQueue")
        }
    } while !queue.isEmpty()
}
