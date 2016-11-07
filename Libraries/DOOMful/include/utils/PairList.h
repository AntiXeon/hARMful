/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		PairList.h                 */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/30/2014                 */
/* UPDATE:      03/30/2014                 */
/*                                         */
/* A PairList is a list of pair objects.   */
/* The aim is to simulate a hash table     */
/* where the order of the inserted         */
/* elements is kept.                       */
/* Moreover, it is useful to read data in  */
/* their insertion order, without direct   */
/* access, for some data.                  */
/*******************************************/

#ifndef __DOOM__PAIRLIST__
#define __DOOM__PAIRLIST__

#include <stdlib.h>
#include <errno.h>

#include <debug/Test.h>
#include <patterns/Iterator/Iterable.h>
#include <patterns/Iterator/Iterator.h>
#include <utils/Mutex.h>


namespace Doom {

    /**
     * @brief   A linked list of pair nodes.
     * @author  CB (c) 2015
     * @version 0.1     2015/03/30
     */
    template <class K, class V>
    class PairList : public Iterable {
        /** DEFINITIONS OF STRUCTURES INTERNALLY USED BY THE LIST **/
        private:
            /**
             * @brief   Key/Value structure.
             */
            class KeyValue {
                public:
                    /** @brief   Key of the pair. */
                    K m_key ;

                    /** @brief   Value of the pair. */
                    V m_value ;


                    /** @brief  Create an undefined key/value pair. */
                    KeyValue() ;

                    /** @brief  Create a pair. */
                    KeyValue(const K& key, const V& value) ;

                    /** @brief  Destroy a pair. */
                    virtual ~KeyValue() ;
            } ;

            /**
             * @brief   A node of the list. It contains a key-value pair and a
             *          node next to it to create a linked list.
             */
            class PairNode {
                private:
                    /** @brief  Element contained in the node. */
                    KeyValue m_nodeElement ;

                    /** @brief  Next node in the linked list. */
                    PairNode* m_next ;

                    /** @brief  Previous node in the linked list. */
                    PairNode* m_previous ;

                    /** @brief  Limit concurrent access to the node. */
                    Mutex m_accessNode ;


                public:
                    /**
                     * @brief   Create a new node.
                     * @param   key         Key of the pair node.
                     * @param   value       Value of the pair node.
                     * @param   next        Next node in the list.
                     * @param   previous    Previous node in the list.
                     */
                    PairNode(const K& key,
                             const V& value,
                             PairNode* next = NULL,
                             PairNode* previous = NULL) ;

                    /** @brief  Destroy the node. */
                    virtual ~PairNode() ;


                    /** @brief  Set the next node after the current one. */
                    void setNext(PairNode* next) ;

                    /** @brief  Set the previous node before the current one. */
                    void setPrevious(PairNode* previous) ;

                    /**
                     * @brief   Get the next node.
                     * @return  The next node in the list.
                     */
                    PairNode* getNext() ;

                    /**
                     * @brief   Get the previous node.
                     * @return  The previous node in the list.
                     */
                    PairNode* getPrevious() ;

                    /**
                     * @brief   Get the key/value pair.
                     * @return  The key/value pair of the node.
                     */
                    KeyValue getPair() ;
            } ;

        public:
            /**
             * @brief   A head Iterator is an iterator going from the head to
             *          the tail of the list.
             */
            class hIterator : public Iterator {
                private:
                    /** @brief  Currently accessed node. */
                    PairNode* m_current ;

                public:
                    /** @brief  Create an iterator on the given list. */
                    hIterator() ;

                    /** @brief  Create an iterator on the given list. */
                    hIterator(PairList* list, PairNode* node) ;

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
                    bool hasNext() ;

                    /**
                     * @brief   Get the key of the current pair.
                     * @return  The value of the key.
                     */
                    K getKey() ;

                    /**
                     * @brief   Get the value of the current pair.
                     * @return  The value of the value (!).
                     */
                    V getValue() ;


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
            /** @brief  Head node of the linked list. */
            PairNode* m_headNode ;

            /** @brief  Tail node of the linked list. */
            PairNode* m_tailNode ;

            /** @brief  Length of the list. */
            size_t m_length ;


        public:
            /** @brief  Create an empty PairList. */
            PairList() ;

            /**
             * @brief   Create a PairList with a first node.
             * @param   key     Value of the key to insert.
             * @param   value   Value to insert.
             */
            PairList(const K& key, const V& value) ;

            /** @brief  Create a PairList. */
            virtual ~PairList() ;


            /** @brief   */
            void push_front(const K& key, const V& value) ;

            /** @brief   */
            void pop_front() ;


            /** @brief   */
            void push_back(const K& key, const V& value) ;

            /** @brief   */
            void pop_back() ;


            /** @brief  Get the length of the list. */
            size_t size() ;


            /**
             * @brief   Get an iterator focused on the head node of the list.
             * @return  An iterator whose current element is the head of the list.
             */
            hIterator begin() ;

            /**
             * @brief   Get an iterator focused on the tail node of the list.
             * @return  An iterator whose current element is the tail of the list.
             */
            hIterator end() ;


        private:
            /**
             * @brief   Local pop front function to make it unprotected and easily
             *          reusable by several public functions.
             */
            void private_pop_front() ;
    } ;

    #include "PairList/KeyValue.impl"
    #include "PairList/PairNode.impl"
    #include "PairList/hIterator.impl"
    #include "PairList/PairList.impl"

} ;


#endif
