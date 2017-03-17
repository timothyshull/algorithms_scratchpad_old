//
// Created by Tim Shull on 11/28/16.
// Copyright (c) 2016 Tim Shull. All rights reserved.
//

import Foundation

class FixedCapacityStackOfStrings {
    private var a: [String?]
    private var n: Int

    init(max: Int) {
        self.a = [String?]()
        a.reserveCapacity(max)
        self.n = 0
    }

    public var isEmpty: Bool {
        return n == 0
    }

    public var size: Int {
        return n
    }

    public func push(item: String) {
        a[n] = item
        n += 1
    }

    public func pop() -> String {
        n -= 1
        let item = a[n]
        a[n] = nil
        return item!
    }
}

public func fcsosMain() {
    let s = FixedCapacityStackOfStrings(max: 100)
    while let line = readLine(strippingNewline: true)?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines), line != "" {
        if line != "-" {
            s.push(item: line)
        } else if !s.isEmpty {
            print("\(s.pop()) ")
        }
    }
    print("(\(s.size) left on stack")
}
