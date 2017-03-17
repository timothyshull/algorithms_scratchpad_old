//
// Created by Tim Shull on 9/12/16.
// Copyright (c) 2016 ___FULLUSERNAME___. All rights reserved.
//

import Foundation


open class Node<T:Equatable>: CustomStringConvertible {
    typealias NodeType = Node<T>

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
}


struct BagIterator<T:Comparable>: IteratorProtocol {
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

class Bag<Item:Comparable>: Sequence {
//class Bag<Item:Comparable>: CollectionType {

    typealias NodeType = Node<Item>?
    typealias Iterator = BagIterator<Item>

    fileprivate var first: NodeType
    fileprivate var n: Int

    init() {
        first = nil
        n = 0
    }

    func isEmpty() -> Bool {
        return first == nil
    }

    func size() -> Int {
        return n
    }

    func add(_ item: Item) {
        let oldFirst = first
        first = Node<Item>(value: item)
        first!.value = item
        first!.next = oldFirst
        n += 1
    }

    func makeIterator() -> Iterator {
        return BagIterator(first)
    }
}
