/*
 *  File:    NXThreadSafeQueue.h
 *
 *  author:  张雄(zhang xiong)
 *  date:    2016_08_27
 *  purpose: define a thread safe queue interface
 */

#pragma once

#include <string>
#include <utility>

namespace NX {
    class ThreadSafeQueue{
    public:
        ThreadSafeQueue(){/*empty here*/}
        virtual ~ThreadSafeQueue() {/*empty here*/}
        static ThreadSafeQueue* Create();
        static void Destroy(ThreadSafeQueue* const pQueue){delete pQueue;}
        
    public:
        /**
         *  get the capacity of the queue
         *
         *  <return value>
         *  return value give how many elemeny the queue can hold
         */
        virtual int  Capacity() = 0;
        
        
        /**
         *  get the currrent element holds by the queue
         *
         *  <return value>
         *  return value give how many elemeny the queue holds
         */
        virtual int  Count() = 0;
        
        /**
         *  Init the queue
         *
         *  <return value>
         *  true:  init success
         *  false: init failed, the caller must destroy this queue
         */
        virtual bool Init() = 0;
        
        /**
         *  Check wheather queue is empty
         *
         *  <return value>
         *  true:  queue is empty
         *  false: queue is not empty
         */
        virtual bool Empty() = 0;
        
        /**
         *  Check wheather queue is full
         *
         *  <return value>
         *  true:  queue is full
         *  false: queue is not full
         */
        virtual bool Full() = 0;
        
        /**
         *  enqueue a element
         *
         *  <parameter>
         *  strMsg: the string to be equeued
         *  bForceInsert: this parameter is used only when queue is full and we still need to enque this element, if queue is
         *                not full, this parameter is not used
         *
         *  <return value>
         *  true:  enqueue succed
         *  false: enque failed
         */
        virtual bool Enque(const std::string &strMsg, const bool bForceInsert) = 0;
        
        /**
         *  dequeue a element
         *
         *  <return value>
         *  <bool, string> = <deque succed, the dequed value> if the first is false, then the second is a garbage
         */
        virtual std::pair<bool, std::string> Deque() = 0;
    };
    
    /**
     *  serialize interface, which is used for serialize & unserialize the msg queue data
     */
    class Serializable{
    public:
        Serializable() {/*empty here*/}
        virtual ~Serializable() {/*empty here*/}
        
    public:
        virtual bool Serialize() = 0;
        virtual bool UnSerialize() = 0;
    };
}