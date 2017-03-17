//
// Created by Tim Shull on 11/28/16.
// Copyright (c) 2016 Tim Shull. All rights reserved.
//

import Foundation

public class LinkedStackNode<Element> {
    typealias Node = LinkedStackNode<Element>

    var item: Element
    var next: Node?

    public init(value: Element) {
        self.item = value
    }
}

extension LinkedStackNode: CustomStringConvertible {
    public var description: String {
        return "LinkedStackNode(\(item))"
    }
}

extension LinkedStackNode: Equatable {
    public static func ==(lhs: LinkedStackNode<Element>, rhs: LinkedStackNode<Element>) -> Bool {
        return lhs === rhs
    }

    public static func !=(lhs: LinkedStackNode<Element>, rhs: LinkedStackNode<Element>) -> Bool {
        return !(lhs == rhs)
    }
}

enum LinkedStackError: Error {
    case noSuchElementException(message: String)
}

public struct LinkedStackIterator<T:Comparable>: IteratorProtocol {
    public typealias Element = LinkedStackNode<T>

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

public class LinkedStack<Element:Comparable> {
    public typealias Node = LinkedStackNode<Element>

    // Collection protocol conformance
    public typealias Index = Int
    public typealias Iterator = LinkedStackIterator<Element>

    // members
    internal var first: Node?
    internal var n: Int

    public init() {
        first = nil // unnecessary
        n = 0
#if DEBUG
        assert(check(), "LinkedStack invariant check failed")
#endif
    }

    public var isEmpty: Bool {
        return first == nil
    }

    public var size: Int {
        return n
    }

    public func push(item: Element) -> Void {
        let oldFirst = first
        first = Node(value: item)
        first?.next = oldFirst
        n += 1
#if DEBUG
        assert(check(), "LinkedStack invariant check failed when calling push with \(withItem)")
#endif
    }

    public func pop() throws -> Element {
        if isEmpty {
            throw LinkedStackError.noSuchElementException(message: "Stack underflow")
        }
        let item = first!.item
        first = first!.next
        n -= 1
#if DEBUG
        assert(check(), "LinkedStack invariant check failed after calling pop")
#endif
        return item
    }

    public func peek() throws -> Element {
        if isEmpty {
            throw LinkedStackError.noSuchElementException(message: "Stack underflow")
        }
        return first!.item
    }
}

extension LinkedStack {
    private func check() -> Bool {
        return checkSize() && checkConsistency() && checkNumberOfNodes()
    }

    private func checkSize() -> Bool {
        if size < 0 {
            return false
        }
        return true
    }

    private func checkConsistency() -> Bool {
        if size == 0 {
            if first != nil {
                return false
            }
        } else if size == 1 {
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
}

extension LinkedStack: Sequence {
    public func makeIterator() -> Iterator {
        return Iterator(first)
    }
}

extension LinkedStack: CustomStringConvertible {
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

public func linkedStackMain() {
    let stack: LinkedStack<String> = LinkedStack<String>()
    print("Add strings to the stack: ")
    while let line = readLine(strippingNewline: true)?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines), line != "" {
        if line != "-" {
            stack.push(item: line)
        } else if !stack.isEmpty {
            do {
                try print("\(stack.pop()) ")
            } catch LinkedStackError.noSuchElementException(let message) {
                print("An error occurred: \(message)")
            } catch {
                print("An unknown error occurred")
            }
        }
    }
}