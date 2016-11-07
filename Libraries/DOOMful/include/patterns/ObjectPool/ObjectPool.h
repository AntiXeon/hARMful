/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       ObjectPool.h               */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    09/01/2015                 */
/* UPDATE:      09/01/2015                 */
/*                                         */
/* An ObjectPool create an initial amount  */
/* of objects. They are cached when unused */
/* and taken from cache when required,     */
/* avoiding dynamic allocations and so the */
/* related time consumption (against a     */
/* higher amount of used memory).          */
/*******************************************/

#ifndef __DOOM__OBJECT_POOL__
#define __DOOM__OBJECT_POOL__


#include <list>
#include <debug/Test.h>
#include <interfaces/IClearable.h>


namespace Doom {

    /**
     * @brief   An ObjectPool create an initial amount of objects. They are
     *          cached when unused and taken from cache when required, avoiding
     *          dynamic allocations and so the related time consumption (against
     *          a higher amount of used memory).
     *
     * @warning IPoolable is the class associated to the PoolableObject.
     * @see     PoolableObject
     *
     * @author  CB (c) 2015
     * @version 0.1     2015/01/09
     */
    template <class PoolableClass>
    class ObjectPool {
        private:
            /** @brief   Available states for the PoolableObject. */
            enum PoolableState {
                                State_Used, // In the in-use list of the ObjectPool;
                                State_Cache // in the cache of the ObjectPool.
                               } ;

        public:
            /** @brief  Behaviors of the ObjectPool when the cache is empty. */
            enum PoolBehavior {
                               Behavior_CreateNewObjects,   // Create new objects
                               Behavior_SynchronizeThreads, // Synchronize threads
                               Behavior_UndefinedValue      // Return undefined...
                              } ;

            /**
             * @brief   An IPoolable is an object that can be managed by an
             *          ObjectPool.
             *          It must clearable (ie. clear its inner data for reuse).
             *
             * @warning ClearableClass type must extend the IPoolable interface.
             * @warning ClearableClass must implement the static method
             *          <code>static IClearable* CreateInternal() ;</code>
             *
             * @author  CB (c) 2015
             * @version 0.1     2015/09/02
             */
            class IPoolable : public IClearable {
                // Only the ObjectPool can access private data.
                friend ObjectPool<PoolableClass> ;

                private:
                    /** @brief  Parent ObjectPool. This helps controlling PoolableObject. */
                    ObjectPool* m_parent ;

                    /** @brief  State of the PoolableObject. */
                    ObjectPool::PoolableState m_state ;

                public:
                    /** @brief  Destruction of an IPoolable. */
                    virtual ~IPoolable() {}
            } ;

            /**
             * @brief   A PoolableObjectFactory can generate new IPoolable instances.
             *
             * @warning ClearableClass type must extend the IPoolable interface.
             * @warning ClearableClass must implement the static method
             *          <code>static IClearable* CreateInternal() ;</code>
             *
             * @author  CB (c) 2015
             * @version 0.1     2015/09/02
             */
            class PoolableObjectFactory : public Factory<PoolableClass, IPoolable>{
                public:
                    /** @brief  Destruction of a PoolableObjectFactory. */
                    virtual ~PoolableObjectFactory() {}
            } ;


        private:
            /**
             * @brief   Maximal amount of data the cache can contain. If zero,
             *          the cache has "no limit" of size.
             */
            size_t m_maxSize ;

            /** @brief  Behavior of the ObjectPool when the cache is empty. */
            PoolBehavior m_behavior ;

            /** @brief  Mutex to avoid ObjectPool corruption. */
            Mutex m_mutex ;

            /**
             * @brief   Mutex to synchronize threads when cache is empty.
             *          It may occur that several threads want to get values
             *          from the ObjectPool. Yet, when cache is empty, in
             *          default situation it returns an undefined value.
             *          To avoid such situation, a thread that insert back a
             *          value can unlock this mutex to allow another one to get
             *          a such cached value.
             */
            Mutex m_synchronize ;

            /** @brief  Factory to generate new IPoolable instances. */
            PoolableObjectFactory* m_factory ;

            /** @brief  List of unused IPoolable instances. */
            std::list<IPoolable*> m_cache ;

            /**
             * @brief   List of instances generated by the ObjectPool.
             *          They are destroyed with the ObjectPool.
             */
            std::list<IPoolable*> m_trace ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an empty ObjectPool.
             *          This ObjectPool can create new instances of IPoolable.
             * @param   factory             The Factory used to generate new
             *                              content.
             * @param   maxSize             Maximal amount of data tIPoolablecan
             *                              contain. If zero, the cache has "no
             *                              limit" of size.
             */
            ObjectPool(
                       PoolableObjectFactory* factory,
                       size_t maxSize = 0
                      ) ;

            /**
             * @brief   Create an ObjectPool containing a start amount of data
             *          in cache. These data are generated by the ObjectPool
             *          with default data provided by the IPoolable type.
             * @param   factory             The Factory used to generate new
             *                              content.
             * @param   originalSize        Original amounIPoolable in the
             *                              ObjectPool.
             * @param   behavior            Behavior of the ObjectPool when the
             *                              cache is empty.
             * @param   maxSize             Maximal amount of data the cache can
             *                              contain. If zero, the cache has "no
             *                              limit" of size.
             */
            ObjectPool(
                       PoolableObjectFactory* factory,
                       size_t originalSize,
                       PoolBehavior behavior,
                       size_t maxSize = 0
                      ) ;

            /**
             * @brief   Create an ObjectPool with an initial list of data.
             * @param   factory             The Factory used to generate new
             *                              content.
             * @param   originalSet         Original set of data.
             * @param   createNewObjects    If TRUE, the ObjectPool can create
             *                              additional instances of IPoolable
             *                              when cache is empty. If IPoolable
             *                              ObjectPool only uses original set of
             *                              data without creation of new data.
             * @param   maxSize             Maximal amount of data the cache can
             *                              contain. If zero, the cache has "no
             *                              limit" of size.
             */
            ObjectPool(
                       PoolableObjectFactory* factory,
                       const std::list<IPoolable*>& originalSet,
                       PoolBehavior behavior,
                       size_t maxSize = 0
                      ) ;


            /**
             * @brief   Destruction of the ObjectPool.
             * @warning Destroy the ObjectPool implies the destruction of all
             *          the instances created by the ObjectPool.
             *          Do not continue to use such instances!
             *          Moreover, original set of data is not handled by the
             *          destruction.
             */
            virtual ~ObjectPool() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Get a IPoolable instance from the ObjectPool.
             *          This iIPoolables taken from the cache.
             * @param   The gotten object. NULL if the ObjectPool is
             *          configurated to not wait or not generate an object when
             *          the cache is empty.
             */
            IPoolable* grab() ;

            /**
             * @brief   Unuse a value, moving it to the cache of the ObjectPool.
             * @warning The given instance must be one of the instances created
             *          by the ObjectPool. It also must be in the in-use list of
             *          the ObjectPool.
             * @warning The given instance is invalidated (NULL).
             */
            void drop(IPoolable* instance) ;


        private:
            /**
             * @brief   Assign the given instance to the current ObjectPool.
             * @param   instance    Instance of IPoolable to assign.
             */
            void assignObjectToPool(IPoolable* instance) ;

            /**
             * @brief   Generate an IPoolable instance.
             * @return  The generateIPoolablele.
             */
            IPoolable* generateObject() ;

            /** @brief  Initialize the cache. */
            void initializeCache() ;
    } ;

    #include "ObjectPool.impl"

} ;


#endif
