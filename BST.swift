//
//  BST.swift
//  Algos4
//
//  Created by Tim Shull on 10/1/16.
//  Copyright © 2016 Tim Shull. All rights reserved.
//

import Foundation


enum BSTError: Error {
    case nullPointerException
}


open class BSTNode<Key:Comparable, Value>: Equatable, CustomStringConvertible {
    typealias NodeType = BSTNode<Key, Value>
    
    var key: Key
    var value: Value
    var size: Int = 0
    var left: NodeType? = nil
    var right: NodeType? = nil
    
    open var description: String {
        get {
            return "BSTNode(\(value))"
        }
    }
    
    init(key: Key, value: Value, size: Int) {
        self.key = key
        self.value = value
        self.size = size
    }
    
    public static func ==(lhs: BSTNode<Key, Value>, rhs: BSTNode<Key, Value>) -> Bool {
        return lhs.key == rhs.key
    }
    
    public static func !=(lhs: BSTNode<Key, Value>, rhs: BSTNode<Key, Value>) -> Bool {
        return !(lhs == rhs)
    }
}


struct BSTIterator<Key:Comparable, Value>: IteratorProtocol {
    internal typealias Element = BSTNode<Key, Value>
    
    var current: Element?
    
    init(_ start: Element?) {
        current = start
    }
    
    func hasNext() -> Bool {
        return current != nil && (current!.left != nil || current!.right != nil)
    }
    
    mutating func next() -> Element? {
        let n = current
        current = current?.right
        return n
    }
}

open class BST<Key:Comparable, Value>: Equatable, CustomStringConvertible {
    typealias NodeType = BSTNode<Key, Value>
    
    var root: NodeType? = nil
    
    init() {
        
    }
    
    func isEmpty() -> Bool {
        return size() == 0
    }
    
    func size() -> Int {
        return size(startNode: root)
    }
    
    func size(startNode: NodeType?) -> Int {
        if startNode == nil {
            return 0
        } else {
            return startNode!.size
        }
    }
    
    func contains(key: Key?) throws -> Bool {
        if key == nil {
            throw BSTError.nullPointerException
        }
        return get(key) != nil
    }
}

