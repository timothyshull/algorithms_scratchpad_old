//
// Created by Tim Shull on 11/28/16.
// Copyright (c) 2016 Tim Shull. All rights reserved.
//

import Foundation

public class LinkedQueueNode<Element> {
    typealias Node = LinkedQueueNode<Element>

    var item: Element
    var next: Node?

    public init(value: Element) {
        self.item = value
    }
}

extension LinkedQueueNode: CustomStringConvertible {
    public var description: String {
        return "LinkedQueueNode(\(item))"
    }
}

extension LinkedQueueNode: Equatable {
    public static func ==(lhs: LinkedQueueNode<Element>, rhs: LinkedQueueNode<Element>) -> Bool {
        return lhs === rhs
    }

    public static func !=(lhs: LinkedQueueNode<Element>, rhs: LinkedQueueNode<Element>) -> Bool {
        return !(lhs == rhs)
    }
}

enum LinkedQueueError: Error {
    case noSuchElementException(message: String)
}

public struct LinkedQueueIterator<T:Comparable>: IteratorProtocol {
    public typealias Element = LinkedQueueNode<T>

    var current: Element?

    init(_ start: Element?) {
        current = start
    }

    func hasNext() -> Bool {
        if let n = current {
            return n.next != nil
        }
        return false
    }

    public mutating func next() -> Element? {
        let n = current
        current = current?.next
        return n
    }
}

public class LinkedQueue<Element:Comparable> {
    public typealias Node = LinkedQueueNode<Element>

    // Collection protocol conformance
    public typealias Index = Int
    public typealias Iterator = LinkedQueueIterator<Element>

    // members
    internal var first: Node?
    internal var last: Node?
    internal var n: Int

    public init() {
        first = nil // unnecessary
        last = nil // unnecessary
        n = 0
#if DEBUG
        assert(check(), "LinkedQueue invariant check failed")
#endif
    }

    public var isEmpty: Bool {
        return first == nil
    }

    public var size: Int {
        return n
    }

    public func peek() throws -> Element {
        guard !isEmpty else {
            throw LinkedQueueError.noSuchElementException(message: "Queue underflow")
        }
        return first!.item
    }

    public func enqueue(item: Element) -> Void {
        let oldLast = last
        last = Node(value: item)
        last?.next = nil
        if isEmpty {
            first = last
        } else {
            oldLast?.next = last
        }
        n += 1
#if DEBUG
        assert(check(), "LinkedQueue invariant check failed when calling enqueue with \(withItem)")
#endif
    }

    public func dequeue() throws -> Element {
        guard !isEmpty else {
            throw LinkedQueueError.noSuchElementException(message: "Queue underflow")
        }
        let item = first!.item
        first = first!.next
        n -= 1
        if isEmpty {
            last = nil
        }
#if DEBUG
        assert(check(), "LinkedQueue invariant check failed after calling dequeue")
#endif
        return item
    }
}

extension LinkedQueue {
    private func check() -> Bool {
        return checkSize() && checkConsistency() && checkNumberOfNodes() && checkLastNode()
    }

    private func checkSize() -> Bool {
        if size < 0 {
            return false
        }
        return true
    }

    private func checkConsistency() -> Bool {
        if size == 0 {
            if first != nil || last != nil {
                return false
            }
        } else if size == 1 {
            if first == nil || last == nil {
                return false
            }
            if first != last {
                return false
            }
            if first?.next != nil {
                return false
            }
        } else {
            if first == nil || last == nil {
                return false
            }
            if first == last {
                return false
            }
            if first?.next == nil {
                return false
            }
            if last!.next != nil {
                return false
            }
        }
        return true
    }

    private func checkNumberOfNodes() -> Bool {
        var numberOfNodes = 0
        var x = first
        while x != nil && numberOfNodes <= n {
            numberOfNodes += 1
            x = x?.next
        }

        if numberOfNodes != n {
            return false
        }

        return true
    }

    private func checkLastNode() -> Bool {
        var lastNode = first
        while lastNode?.next != nil {
            lastNode = lastNode!.next
        }
        if last != lastNode {
            return false
        }
        return true
    }
}

extension LinkedQueue: Sequence {
    public func makeIterator() -> Iterator {
        return Iterator(first)
    }
}

extension LinkedQueue: CustomStringConvertible {
    public var description: String {
        var tmp = "{"
        for n in self {
            tmp += n.description
            if n.next != nil {
                tmp += ", "
            }
        }
        return tmp + "}"
    }
}

public func linkedQueueMain() {
    let queue: LinkedQueue<String> = LinkedQueue<String>()
    print("Add strings to the queue: ")
    while let line = readLine(strippingNewline: true)?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines), line != "" {
        if line != "-" {
            queue.enqueue(item: line)
        } else if !queue.isEmpty {
            do {
                try print("\(queue.dequeue()) ")
            } catch LinkedQueueError.noSuchElementException(let message) {
                print("An error occurred: \(message)")
            } catch {
                print("An unknown error occurred")
            }
        }
    }
}