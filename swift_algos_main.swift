//
//  main.swift
//  Algos4
//
//  Created by Tim Shull on 9/12/16.
//  Copyright (c) 2016 Tim Shull. All rights reserved.
//

import Foundation

let keyboard = FileHandle(fileDescriptor: 0, closeOnDealloc: true)

extension String {
    func trim() -> String {
        return self.trimmingCharacters(in: NSCharacterSet(charactersIn: " \n\r") as CharacterSet)
    }
}

func bagMain() {
    print("Running the main function for a linked bag")
    
    let bag: Bag<String> = Bag()
    
    var inputString: String?
    repeat {
        print("Input a new string:")
        let inputData = keyboard.availableData
        inputString = NSString(data: inputData, encoding: String.Encoding.utf8.rawValue) as? String
        if inputString!.trim() != "" {
            bag.add(inputString!.trim())
        }
    } while inputString!.trim() != ""
    
    print("The size of the bag is: \(bag.size())")
    
    for s in bag {
        print(s)
    }
}

// TODO: fix this main to better show the functionality of linked queue
func linkedQueueMain() {
    print("Running the main function for a linked queue")
    
    let queue: LinkedQueue<String> = LinkedQueue()
    let keyboard = FileHandle(fileDescriptor: 0, closeOnDealloc: true)
    var inputString: String?
    repeat {
        print("Input a new string:")
        let inputData = keyboard.availableData
        inputString = NSString(data: inputData, encoding: String.Encoding.utf8.rawValue) as? String
        if inputString!.trim() != "" {
            queue.enqueue(inputString!.trim())
        }
    } while inputString!.trim() != ""
    
    print("The size of the queue is: \(queue.size())")
    
    repeat {
        do {
            try print(queue.dequeue()! + " ")
        } catch {
            print("An error occurred while dequeueing an item from the LinkedQueue")
        }
    } while !queue.isEmpty()
//    for s in queue {
//        print(s)
//    }
}

// TODO: fix this main to better show the functionality of linked queue
func linkedStackMain() {
    print("Running the main function for a linked stack")
    let stack: LinkedStack<String> = LinkedStack()
    
    let keyboard = FileHandle(fileDescriptor: 0, closeOnDealloc: true)
    var inputString: String?
    repeat {
        print("Input a new string:")
        let inputData = keyboard.availableData
        inputString = NSString(data: inputData, encoding: String.Encoding.utf8.rawValue) as? String
        if inputString!.trim() != "" {
            stack.push(inputString!.trim())
        }
    } while inputString!.trim() != ""
    
}

bagMain()
linkedQueueMain()
