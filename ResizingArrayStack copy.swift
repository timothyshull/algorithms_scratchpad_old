//
// Created by Tim Shull on 11/28/16.
// Copyright (c) 2016 Tim Shull. All rights reserved.
//

import Foundation

public struct ResizingArrayStackReverseIterator<Item>: IteratorProtocol {
    public typealias Element = Item

    private var i: Int
    private var a: [Item?]

    init(_ start: Int, array: [Item?]) {
        self.i = start
        self.a = array
    }

    func hasNext() -> Bool {
        return i > 0
    }

    public mutating func next() -> Element? {
        if i < a.count && i > 0 {
            i -= 1
            return a[1]
        }
        return nil
    }
}

class ResizingArrayStack<Item> {
    private var a: [Item?]
    private var n: Int

    init(max: Int) {
        self.a = [Item?]()
        a.reserveCapacity(max)
        self.n = 0
    }

    public var isEmpty: Bool {
        return n == 0
    }

    public var size: Int {
        return n
    }

    private func resize(newMax: Int) {
        var tmp = [Item?]()
        tmp.reserveCapacity(newMax)
        let maxIndex = n < newMax ? n : newMax
        for i in 0 ... maxIndex {
            tmp[i] = a[i]
        }
        a = tmp
    }

    public func push(item: Item) {
        if n == a.count {
            resize(newMax: 2 * a.count)
        }
        a[n] = item
        n += 1
    }

    public func pop() -> Item {
        n -= 1
        let item = a[n]
        a[n] = nil

        if (n > 0 && n == a.count / 4) {
            resize(newMax: a.count / 2)
        }

        return item!
    }
}

extension ResizingArrayStack: Sequence {
    public typealias Iterator = ResizingArrayStackReverseIterator<Item>

    public func makeIterator() -> Iterator {
        return Iterator(n, array: a)
    }
}
