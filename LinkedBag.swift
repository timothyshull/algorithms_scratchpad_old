//
// Created by Tim Shull on 11/28/16.
// Copyright (c) 2016 Tim Shull. All rights reserved.
//

import Foundation

public class LinkedBagNode<Element> {
    typealias Node = LinkedBagNode<Element>

    var item: Element
    var next: Node?

    public init(value: Element) {
        self.item = value
    }
}

extension LinkedBagNode: CustomStringConvertible {
    public var description: String {
        return "LinkedBagNode(\(item))"
    }
}

extension LinkedBagNode: Equatable {
    public static func ==(lhs: LinkedBagNode<Element>, rhs: LinkedBagNode<Element>) -> Bool {
        return lhs === rhs
    }

    public static func !=(lhs: LinkedBagNode<Element>, rhs: LinkedBagNode<Element>) -> Bool {
        return !(lhs == rhs)
    }
}

enum LinkedBagError: Error {
    case noSuchElementException(message: String)
}

public struct LinkedBagIterator<T:Comparable>: IteratorProtocol {
    public typealias Element = LinkedBagNode<T>

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

public class LinkedBag<Element:Comparable> {
    public typealias Node = LinkedBagNode<Element>

    // Collection protocol conformance
    public typealias Index = Int
    public typealias Iterator = LinkedBagIterator<Element>

    // members
    internal var first: Node?
    internal var n: Int

    public init() {
        first = nil // unnecessary
        n = 0
    }

    public var isEmpty: Bool {
        return first == nil
    }

    public var size: Int {
        return n
    }

    public func add(item: Element) -> Void {
        let oldFirst = first
        first = Node(value: item)
        first?.next = oldFirst
        n += 1
    }
}

extension LinkedBag: Sequence {
    public func makeIterator() -> Iterator {
        return Iterator(first)
    }
}

extension LinkedBag: CustomStringConvertible {
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

public func linkedBagMain() {
    let bag: LinkedBag<String> = LinkedBag<String>()
    print("Add strings to the bag: ")
    while let line = readLine(strippingNewline: true)?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines), line != "" {
        bag.add(item: line)
    }
    print("The size of the bag is \(bag.size)")
    for line in bag {
        print(line)
    }
}