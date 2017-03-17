// LinkedListNode
public class LinkedListNode<Element> {
    typealias Node = LinkedListNode<Element>

    var value: Element
    var next: Node?
    weak var previous: Node?

    public init(value: Element) {
        self.value = value
    }
}

extension LinkedListNode: CustomStringConvertible {
    public var description: String {
        return "Node(\(value))"
    }
}

extension LinkedListNode: Equatable {
    public static func ==(lhs: LinkedListNode<Element>, rhs: LinkedListNode<Element>) -> Bool {
        return lhs === rhs
    }

    public static func !=(lhs: LinkedListNode<Element>, rhs: LinkedListNode<Element>) -> Bool {
        return !(lhs == rhs)
    }
}


// LinkedListIterator
public struct LinkedListIterator<T:Comparable>: IteratorProtocol {
    public typealias Element = LinkedListNode<T>

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


// LinkedList
public class LinkedList<Element:Comparable> {
    public typealias Node = LinkedListNode<Element>

    // Collection protocol conformance
    public typealias Index = Int
    public typealias Iterator = LinkedListIterator<Element>

    // members
    internal var head: Node?
    internal var tail: Node?
    internal var size: Int

    public init() {
        // head = nil
        size = 0
#if DEBUG
        assert(check(), "Linked queue invariant check failed")
#endif
    }

    public var isEmpty: Bool {
        return head == nil
    }

    public var first: Node? {
        return head
    }

    public var startIndex: Int {
        return 0;
    }

    public var endIndex: Int {
        return size
    }

    public var count: Int {
        return size
    }

    public func node(atIndex index: Int) -> Node? {
        if 0 <= index && index <= size {
            var node = head
            var i = index
            while node != nil {
                if i == 0 {
                    return node
                }
                i -= 1
                node = node!.next
            }
        }
        return nil
    }

    public subscript(index: Int) -> Element {
        let node = self.node(atIndex: index)
        assert(node != nil)
        return node!.value
    }

    public func append(_ value: Element) {
        let oldTail = tail
        tail = Node(value: value)
        if isEmpty {
            head = tail
        } else {
            oldTail!.next = tail
        }
        size += 1
#if DEBUG
        assert(check(), "Linked queue invariant check failed")
#endif
    }

    public func insert(_ value: Element, atIndex index: Int) {
        assert(index >= 0, "Index \(index) is out of range for LinkedList")

        var i = index
        var next = head
        var prev: Node?

        repeat {
            i -= 1
            prev = next
            next = next!.next
        } while next != nil && i > 0

        let n = Node(value: value)
        n.previous = prev
        n.next = next
        prev?.next = n
        next?.previous = n

        if prev == nil {
            head = n
        }
        size += 1
#if DEBUG
        assert(check(), "Linked queue invariant check failed")
#endif
    }

    public func removeAll() {
        head = nil // does this definitely drop the reference count for all nodes?
        size = 0
    }

    public func remove(node: Node) -> Element {
        let prev = node.previous
        let next = node.next

        if let prev = prev {
            prev.next = next
        } else {
            head = next
        }
        next?.previous = prev
        size -= 1
        node.previous = nil
        node.next = nil
        return node.value
    }

    public func removeLast() -> Element {
        assert(!isEmpty, "Cannot remove the last element of an empty LinkedList")
        return remove(node: tail!)
    }

    public func remove(atIndex index: Int) -> Element {
        let node = self.node(atIndex: index)
        assert(node != nil)
        return remove(node: node!)
    }

    private func check() -> Bool {
        if size < 0 {
            return false
        } else if size == 0 {
            if head != nil {
                return false
            }
            if tail != nil {
                return false
            }
        } else if size == 1 {
            if head == nil || tail == nil {
                return false
            }
            if head !== tail {
                return false
            }
            if head?.next != nil {
                return false
            }
        } else {
            if head == nil || tail == nil {
                return false
            }
            if head === tail {
                return false
            }
            if head?.next == nil {
                return false
            }
            if tail?.next != nil {
                return false
            }

            var numberOfNodes = 0
            var x = head
            repeat {
                numberOfNodes += 1
                x = x?.next
            } while x != nil && numberOfNodes <= size

            if (numberOfNodes != size) {
                return false
            }

            var lastNode = head
            while lastNode!.next != nil {
                lastNode = lastNode?.next
            }

            if (tail !== lastNode) {
                return false
            }

        }
        return true
    }
}

extension LinkedList: Sequence {
    public func makeIterator() -> Iterator {
        return Iterator(head)
    }
}

extension LinkedList: CustomStringConvertible {
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

extension LinkedList {
    public func reverse() {
        var node = head
        while let current = node {
            node = current.next
            swap(&current.next, &current.previous)
            head = current
        }
    }
}

extension LinkedList {
    public func map<ResultType>(transform: (Element) -> ResultType) -> LinkedList<ResultType> {
        let result = LinkedList<ResultType>()
        var node = head
        while node != nil {
            result.append(transform(node!.value))
            node = node!.next
        }
        return result
    }

    public func filter(predicate: (Element) -> Bool) -> LinkedList<Element> {
        let result = LinkedList<Element>()
        var node = head
        while node != nil {
            if predicate(node!.value) {
                result.append(node!.value)
            }
            node = node!.next
        }
        return result
    }
}

extension LinkedList {
    convenience init(array: Array<Element>) {
        self.init()
        for element in array {
            self.append(element)
        }
    }
}


//public struct Array<Element> : RandomAccessCollection, MutableCollection {
//    public typealias Index = Int
//    public typealias Iterator = IndexingIterator<[Element]>
//    public var startIndex: Int { get }
//    public var endIndex: Int { get }
//    public func index(after i: Int) -> Int
//    public func formIndex(after i: inout Int)
//    public func index(before i: Int) -> Int
//    public func formIndex(before i: inout Int)
//    public func index(_ i: Int, offsetBy n: Int) -> Int
//    public func index(_ i: Int, offsetBy n: Int, limitedBy limit: Int) -> Int?
//    public func distance(from start: Int, to end: Int) -> Int
//    public typealias Indices = CountableRange<Int>
//    public subscript(index: Int) -> Element
//    public subscript(bounds: Range<Int>) -> ArraySlice<Element>
//}
//
//extension Array : ExpressibleByArrayLiteral {
//    public init(arrayLiteral elements: Element...)
//}
//
//extension Array : RangeReplaceableCollection {
//    public init()
//    public init<S : Sequence where S.Iterator.Element == Element>(_ s: S)
//    public init(repeating repeatedValue: Element, count: Int)
//    public var count: Int { get }
//    public var capacity: Int { get }
//    public mutating func reserveCapacity(_ minimumCapacity: Int)
//    public mutating func append(_ newElement: Element)
//    public mutating func append<S : Sequence where S.Iterator.Element == Element>(contentsOf newElements: S)
//    public mutating func append<C : Collection where C.Iterator.Element == Element>(contentsOf newElements: C)
//    public mutating func insert(_ newElement: Element, at i: Int)
//    public mutating func remove(at index: Int) -> Element
//    public mutating func removeAll(keepingCapacity keepCapacity: Bool = default)
//}
//
//extension Array : CustomReflectable {
//    public var customMirror: Mirror { get }
//}
//
//extension Array : CustomStringConvertible, CustomDebugStringConvertible {
//    public var description: String { get }
//    public var debugDescription: String { get }
//}
//
//extension Array {
//    public func withUnsafeBufferPointer<R>(_ body: (UnsafeBufferPointer<Element>) throws -> R) rethrows -> R
//    public mutating func withUnsafeMutableBufferPointer<R>(_ body: (inout UnsafeMutableBufferPointer<Element>) throws -> R) rethrows -> R
//}
//
//extension Array {
//    public mutating func replaceSubrange<C where C : Collection, C.Iterator.Element == _Buffer.Element>(_ subrange: Range<Int>, with newElements: C)
//}
//
//extension Array {
//    public mutating func withUnsafeMutableBytes<R>(_ body: (UnsafeMutableRawBufferPointer) throws -> R) rethrows -> R
//    public func withUnsafeBytes<R>(_ body: (UnsafeRawBufferPointer) throws -> R) rethrows -> R
//}
//
//extension Array {
//    public mutating func popLast() -> Element?
//}
//
//public protocol Collection : Indexable, Sequence {
//    associatedtype IndexDistance : SignedInteger = Int
//    associatedtype Iterator : IteratorProtocol = IndexingIterator<Self>
//    public func makeIterator() -> Self.Iterator
//    associatedtype SubSequence : IndexableBase, Sequence = Slice<Self>
//    public subscript(position: Self.Index) -> Self.Iterator.Element { get }
//    public subscript(bounds: Range<Self.Index>) -> Self.SubSequence { get }
//    associatedtype Indices : IndexableBase, Sequence = DefaultIndices<Self>
//    public var indices: Self.Indices { get }
//    public func prefix(upTo end: Self.Index) -> Self.SubSequence
//    public func suffix(from start: Self.Index) -> Self.SubSequence
//    public func prefix(through position: Self.Index) -> Self.SubSequence
//    public var isEmpty: Bool { get }
//    public var count: Self.IndexDistance { get }
//    public var first: Self.Iterator.Element? { get }
//    public func index(_ i: Self.Index, offsetBy n: Self.IndexDistance) -> Self.Index
//    public func index(_ i: Self.Index, offsetBy n: Self.IndexDistance, limitedBy limit: Self.Index) -> Self.Index?
//    public func distance(from start: Self.Index, to end: Self.Index) -> Self.IndexDistance
//}
//
//extension Collection where Iterator == IndexingIterator<Self> {
//    public func makeIterator() -> IndexingIterator<Self>
//}
//
//extension Collection where SubSequence == Slice<Self> {
//    public subscript(bounds: Range<Self.Index>) -> Slice<Self> { get }
//}
//
//extension Collection where SubSequence == Self {
//    public mutating func popFirst() -> Self.Iterator.Element?
//}
//
//extension Collection {
//    public var isEmpty: Bool { get }
//    public var first: Self.Iterator.Element? { get }
//    public var underestimatedCount: Int { get }
//    public var count: Self.IndexDistance { get }
//}
//
//extension Collection {
//    public func map<T>(_ transform: (Self.Iterator.Element) throws -> T) rethrows -> [T]
//    public func dropFirst(_ n: Int) -> Self.SubSequence
//    public func dropLast(_ n: Int) -> Self.SubSequence
//    public func prefix(_ maxLength: Int) -> Self.SubSequence
//    public func suffix(_ maxLength: Int) -> Self.SubSequence
//    public func prefix(upTo end: Self.Index) -> Self.SubSequence
//    public func suffix(from start: Self.Index) -> Self.SubSequence
//    public func prefix(through position: Self.Index) -> Self.SubSequence
//    public func split(maxSplits: Int = default, omittingEmptySubsequences: Bool = default, whereSeparator isSeparator: (Self.Iterator.Element) throws -> Bool) rethrows -> [Self.SubSequence]
//}
//
//extension Collection where Iterator.Element : Equatable {
//    public func split(separator: Self.Iterator.Element, maxSplits: Int = default, omittingEmptySubsequences: Bool = default) -> [Self.SubSequence]
//}
//
//extension Collection where SubSequence == Self {
//    public mutating func removeFirst() -> Self.Iterator.Element
//    public mutating func removeFirst(_ n: Int)
//}
//
//extension Collection where Iterator.Element : Equatable {
//    public func index(of element: Self.Iterator.Element) -> Self.Index?
//}
//
//extension Collection {
//    public func index(where predicate: (Self.Iterator.Element) throws -> Bool) rethrows -> Self.Index?
//}
//
//extension Collection where Iterator.Element : Collection {
//    public func joined() -> FlattenCollection<Self>
//}
//
//extension Collection where Indices == DefaultIndices<Self> {
//    public var indices: DefaultIndices<Self> { get }
//}
//extension Collection {
//    public var lazy: LazyCollection<Self> { get }
//}
//
//extension Collection where Self : LazyCollectionProtocol {
//    public var lazy: Self { get }
//}










////
//// Created by Tim Shull on 11/28/16.
//// Copyright (c) 2016 Tim Shull. All rights reserved.
////
//
//import Foundation
//
//// insert (next)
//// get next
//// remove next
//// get head
//// get tail
//// get data
//
//public class LinkedListNode<Element> {
//    typealias Node = LinkedListNode<Element>
//
//    var item: Element
//    var next: Node?
//
//    public init(value: Element) {
//        self.item = value
//    }
//}
//
//extension LinkedListNode: CustomStringConvertible {
//    public var description: String {
//        return "Node(\(item))"
//    }
//}
//
//extension LinkedListNode: Equatable {
//    public static func ==(lhs: LinkedListNode<Element>, rhs: LinkedListNode<Element>) -> Bool {
//        return lhs === rhs
//    }
//
//    public static func !=(lhs: LinkedListNode<Element>, rhs: LinkedListNode<Element>) -> Bool {
//        return !(lhs == rhs)
//    }
//}
//
//public struct LinkedListIterator<T:Comparable>: IteratorProtocol {
//    public typealias Element = LinkedListNode<T>
//
//    var current: Element?
//
//    init(_ start: Element?) {
//        current = start
//    }
//
//    func hasNext() -> Bool {
//        if let n = current {
//            return n.next != nil
//        }
//        return false
//    }
//
//    public mutating func next() -> Element? {
//        let n = current
//        current = current?.next
//        return n
//    }
//}
//
//public class LinkedList<Element:Comparable> {
//    public typealias Node = LinkedListNode<Element>
//
//    // Collection protocol conformance
//    public typealias Index = Int
//    public typealias Iterator = LinkedListIterator<Element>
//
//    // members
//    internal var first: Node?
//    internal var n: Int
//
//    public init() {
//        first = nil // unnecessary
//        n = 0
//#if DEBUG
//        assert(check(), "Linked list invariant check failed")
//#endif
//    }
//
//    // bk
//    public var isEmpty: Bool {
//        return first == nil
//    }
//
//    // protocol
//    public var startIndex: Int {
//        return 0;
//    }
//
//    // protocol
//    public var endIndex: Int {
//        return n
//    }
//
//    // protocol
//    public var count: Int {
//        return n
//    }
//
//    // bk
//    public var size: Int {
//        return n
//    }
//
//    public func insert(after node: Node?) -> Void {
//
//    }
//
//    public func getNext(after node: Node?) -> Node? {
//
//    }
//
//    public func removeNext(after node: Node?) -> Void {
//
//    }
//
//    public func getHead() -> Node? {
//
//    }
//
//    public func getTail() -> Node? {
//
//    }
//
//    public func getData(from node: Node?) -> Element? {
//
//    }
//
//    public func node(atIndex index: Int) -> Node? {
//        if 0 <= index && index <= size {
//            var node = head
//            var i = index
//            while node != nil {
//                if i == 0 {
//                    return node
//                }
//                i -= 1
//                node = node!.next
//            }
//        }
//        return nil
//    }
//
//    public subscript(index: Int) -> Element {
//        let node = self.node(atIndex: index)
//        assert(node != nil)
//        return node!.value
//    }
//
//    public func append(_ value: Element) {
//        let oldTail = tail
//        tail = Node(value: value)
//        if isEmpty {
//            head = tail
//        } else {
//            oldTail!.next = tail
//        }
//        size += 1
//#if DEBUG
//        assert(check(), "Linked queue invariant check failed")
//#endif
//    }
//
//    public func insert(_ value: Element, atIndex index: Int) {
//        assert(index >= 0, "Index \(index) is out of range for LinkedList")
//
//        var i = index
//        var next = head
//        var prev: Node?
//
//        repeat {
//            i -= 1
//            prev = next
//            next = next!.next
//        } while next != nil && i > 0
//
//        let n = Node(value: value)
//        n.previous = prev
//        n.next = next
//        prev?.next = n
//        next?.previous = n
//
//        if prev == nil {
//            head = n
//        }
//        size += 1
//#if DEBUG
//        assert(check(), "Linked queue invariant check failed")
//#endif
//    }
//
//    public func removeAll() {
//        head = nil // does this definitely drop the reference count for all nodes?
//        size = 0
//    }
//
//    public func remove(node: Node) -> Element {
//        let prev = node.previous
//        let next = node.next
//
//        if let prev = prev {
//            prev.next = next
//        } else {
//            head = next
//        }
//        next?.previous = prev
//        size -= 1
//        node.previous = nil
//        node.next = nil
//        return node.value
//    }
//
//    public func removeLast() -> Element {
//        assert(!isEmpty, "Cannot remove the last element of an empty LinkedList")
//        return remove(node: tail!)
//    }
//
//    public func remove(atIndex index: Int) -> Element {
//        let node = self.node(atIndex: index)
//        assert(node != nil)
//        return remove(node: node!)
//    }
//
//    private func check() -> Bool {
//        if size < 0 {
//            return false
//        } else if size == 0 {
//            if head != nil {
//                return false
//            }
//            if tail != nil {
//                return false
//            }
//        } else if size == 1 {
//            if head == nil || tail == nil {
//                return false
//            }
//            if head !== tail {
//                return false
//            }
//            if head?.next != nil {
//                return false
//            }
//        } else {
//            if head == nil || tail == nil {
//                return false
//            }
//            if head === tail {
//                return false
//            }
//            if head?.next == nil {
//                return false
//            }
//            if tail?.next != nil {
//                return false
//            }
//
//            var numberOfNodes = 0
//            var x = head
//            repeat {
//                numberOfNodes += 1
//                x = x?.next
//            } while x != nil && numberOfNodes <= size
//
//            if (numberOfNodes != size) {
//                return false
//            }
//
//            var lastNode = head
//            while lastNode!.next != nil {
//                lastNode = lastNode?.next
//            }
//
//            if (tail !== lastNode) {
//                return false
//            }
//
//        }
//        return true
//    }
//}
//
//extension LinkedList: Sequence {
//    public func makeIterator() -> Iterator {
//        return Iterator(head)
//    }
//}
//
//extension LinkedList: CustomStringConvertible {
//    public var description: String {
//        var tmp = "{"
//        for n in self {
//            tmp += n.description
//            if n.next != nil {
//                tmp += ", "
//            }
//        }
//        return tmp + "}"
//    }
//}



