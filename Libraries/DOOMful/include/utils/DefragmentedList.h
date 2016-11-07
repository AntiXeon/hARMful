/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       DefragmentedIndicesList.h  */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    23/02/2015                 */
/* UPDATE:      23/02/2015                 */
/*                                         */
/* A DefragmentedList is a list of         */
/* elements that, when they are removed,   */
/* are not erased from memory but cached.  */
/* This avoids allocations and deletion of */
/* memory objects that can have a cost in  */
/* loops.                                  */
/*******************************************/

#ifndef __DOOM__DEFRAGMENTED_LIST__
#define __DOOM__DEFRAGMENTED_LIST__

#include <stdlib.h>
#include <errno.h>

#include <DOOMStrings.h>
#include <debug/Test.h>
#include <patterns/Iterator/Iterable.h>
#include <patterns/Iterator/Iterator.h>
#include <utils/Mutex.h>


namespace Doom {

    /**
     * @brief   A DefragmentedList is a list of elements that, when they are
     *          removed, are not erased from memory but cached. This avoids
     *          allocations and deletion of memory objects that can have a cost
     *          in loops.
     *
     * @author  CB (c)  2015
     * @version 0.1     2015/02/24
     */
    template <class T>
    class DefragmentedList : public Iterable {
        /** DEFINITIONS OF STRUCTURES INTERNALLY USED BY THE LIST **/
        private:
            enum TransferList {
                                UnusedList = 0,
                                UsedList
                              } ;

            /**
             * @brief   A Node of the DefragmentedList.
             */
            class Node {
                private:
                    /** @brief  To know if the Node is in used list. */
                    bool m_used ;

                    /** @brief  Next element of the current Node. */
                    Node* m_next ;

                    /** @brief  Previous element of the current Node. */
                    Node* m_previous ;

                    /** @brief  Value of the Node. */
                    T m_value ;

                    /** @brief  Limit concurrent access to the Node. */
                    Mutex m_accessNode ;

                public:
                    /**
                     * @brief  Create a new Node.
                     */
                    Node() ;

                    /**
                     * @brief   Create a new Node.
                     * @param   value       Value of the Node.
                     * @param   next        Next Node in the DefragmentedList.
                     */
                    Node(const T& value, Node* next = NULL) ;

                    /**
                     * @brief   Destruction of the Node.
                     */
                    virtual ~Node() ;


                    /** @brief  Set the next Node after the current one. */
                    inline void setNext(Node* next) ;

                    /**
                     * @brief   Get the next Node.
                     * @return  The next Node in the DefragmentedList.
                     */
                    inline Node* getNext() ;

                    /** @brief  Set the previous Node before the current one. */
                    inline void setPrevious(Node* next) ;

                    /**
                     * @brief   Get the previous Node.
                     * @return  The previous Node in the DefragmentedList.
                     */
                    inline Node* getPrevious() ;

                    /**
                     * @brief   Set the value of the Node.
                     * @param   value   new value of the Node.
                     */
                    inline void setValue(const T& value) ;

                    /**
                     * @brief   Get the value.
                     * @return  The value of the Node.
                     */
                    inline T& getValue() ;

                    /**
                     * @brief   Set the Node transfered either to the used list
                     *          or unused one.
                     * @param   list    List to which the Node is transfered to.
                     */
                    inline void transferTo(TransferList list) ;

                    /**
                     * @brief   To know if the Node is in the used list.
                     * @return  TRUE if in used list, FALSE if in unused (or
                     *          elsewhere?).
                     */
                    inline bool isInUsedList() ;
            } ;

            /**
             * @brief   Inner list structure to easily manage both lists of used
             *          elements and cached elements.
             */
            class InnerList {
                public:
                    /** @brief  Length of the list. */
                    size_t length ;

                    /** @brief  Head node of the DefragmentedList. */
                    Node* head ;

                    /** @brief  Tail node of the DefragmentedList. */
                    Node* tail ;

                public:
                    /** @brief  Initialization of the InnerList. */
                    InnerList() ;

                    /** @brief  Destruction of the InnerList. */
                    virtual ~InnerList() ;
            } ;


        public:
            /**
             * @brief   A Code contains a value used to access a Node in the
             *          DefragmentedList without having to browse the list.
             *          It also contains a code to identify the
             *          DefragmentedList.
             */
            class Code {
                friend DefragmentedList ;

                private:
                    /** @brief  The shortcut to the Node. */
                    Node* node ;
                    /** @brief  List pointer to check if it its the right one. */
                    DefragmentedList* list ;

                    /**
                     * @brief   Check the list of the Code to the one using it.
                     * @param   otherList   The other list to check if it is the
                     *          same.
                     */
                    inline void check(DefragmentedList* otherList) ;
            } ;


            /**
             * @brief   A head hIterator is an iterator going from the head to
             *          the tail of the DefragmentedList.
             */
            class hIterator : public Iterator {
                private:
                    /** @brief  Currently accessed Node. */
                    Node* m_current ;

                public:
                    /** @brief  Create an iterator on the given list. */
                    hIterator() ;

                    /** @brief  Create an iterator on the given list. */
                    hIterator(DefragmentedList* list, Node* node) ;

                    /** @brief  Copy an iterator. */
                    hIterator(hIterator* other) ;

                    /** @brief  Destruction of the iterator. */
                    virtual ~hIterator() ;


                    /**
                     * @brief   Test if a following node to the current one
                     *          exists in the list.
                     * @return  TRUE if a node is linked to the current one,
                     *          FALSE else.
                     */
                    inline bool hasNext() ;


                    /**
                     * @brief   Get the value of the current Node.
                     * @return  The value of the Node.
                     */
                    inline T& getValue() ;

                    /**
                     * @brief   Get a quick access code to the current Node.
                     */
                    inline Code getCode() ;


                    /** @brief   Suffix operator used by hIterator++. */
                    hIterator operator++(int) ;

                    /** @brief   Prefix operator used by ++hIterator. */
                    hIterator& operator++() ;


                    /** @brief  Test if iterators are the same. */
                    bool operator==(const hIterator& other) ;

                    /** @brief  Test if iterators are different. */
                    bool operator!=(const hIterator& other) ;
            } ;

        protected:
            /**
             * @brief  Used list of elements.
             */
            InnerList m_used ;

            /**
             * @brief  Unused list of elements.
             */
            InnerList m_unused ;


        public:
            /**
             * @brief   Create an empty DefragmentedList.
             */
            DefragmentedList() ;

            /**
             * @brief   Create an empty DefragmentedList with a pre-allocated
             *          cache of Nodes.
             */
            DefragmentedList(size_t initialCacheSize) ;

            /**
             * @brief   Destruction of the DefragmentedList.
             */
            virtual ~DefragmentedList() ;


            /**
             * @brief   Push a new value in the DefragmentedList. If the cache
             *          list is not empty, one of its Nodes is connected. Else a
             *          new one is allocated on-the-fly.
             * @param   value   The value to push.
             * @return  A Code to the new Node of the DefragmentedList.
             */
            void push(const T& value) ;

            /**
             * @brief   Pop the last element of the DefragmentedList.
             */
            void pop() ;

            /**
             * @brief   Insert an element after the Node represented by the
             *          Code.
             */
            void insertAt(Code& code, const T& value) ;

            /**
             * @brief   Remove an element from the list of used elements.
             * @param   code    Code to quickly access to the Node of the
             *                  DefragmentedList.
             */
            void remove(Code& code) ;


            /**
             * @brief   Size of the list of used elements.
             */
            inline size_t size() ;

            /**
             * @brief   Get an iterator focused on the head node of the list.
             * @return  An iterator whose current element is the head of the
             *          list.
             */
            inline hIterator begin() ;

            /**
             * @brief   Get an iterator focused on the following of the tail
             *          node in the list.
             * @return  An iterator whose current element is "after" the tail of
             *          the list.
             * @warning Do not get the value of this hIterator, it has no
             *          defined value and could cause a segmentation fault.
             */
            inline hIterator end() ;

            /**
             * @brief   Get an iterator focused on the tail node of the list.
             * @return  An iterator whose current element is the tail of the
             *          list.
             */
            inline hIterator rbegin() ;

            /**
             * @brief   Get an iterator focused on the preceeding of the head
             *          node in the list.
             * @return  An iterator whose current element is "before" the head
             *          of the list.
             * @warning Do not get the value of this hIterator, it has no
             *          defined value and could cause a segmentation fault.
             */
            inline hIterator rend() ;


        private:
            /**
             * @brief   Check invariant conditions on the lists.
             */
            inline void invariant() ;
    } ;

    #include "DefragmentedList/Node.impl"
    #include "DefragmentedList/Code.impl"
    #include "DefragmentedList/hIterator.impl"
    #include "DefragmentedList/InnerList.impl"
    #include "DefragmentedList/List.impl"

} ;


#endif
