/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		AbstractThread.h           */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/10/2016                 */
/* UPDATE:      01/10/2016                 */
/*                                         */
/* Abstract class  to provide a generic    */
/* API to all available threads types.     */
/*******************************************/

#ifndef __DOOM__ABSTRACT_THREAD__
#define __DOOM__ABSTRACT_THREAD__

namespace Doom {

   /**
    * @brief   Abstract class to provide a generic API to all available threads
    *          types.
    * @author  CB (c) 2016
    * @version 0.1     2016/01/10
    */
    class AbstractThread {

        public:
            /**
             * @brief   A routine for threads.
             */
            typedef void* (*ThreadRoutine) (void*) ;


            /**
             * @brief   Available thread states:
             *              - Created: Thread has just been created.
             *              - Running: Thread is running.
             *              - Joining: Thread being joined.
             *              - Joined: Thread is joined, waiting its termination.
             *              - Stopping: Thread is being stopped.
             *              - Stopped: Thread is stopped.
             *              - Canceled: Thread has been canceled.
             */
            enum ThreadState {
                              ThreadCreated,
                              ThreadRunning,
                              ThreadJoining,
                              ThreadJoined,
                              ThreadStopping,
                              ThreadStopped,
                              ThreadCanceled
                             } ;

        protected:
            /**
             * @brief   Context of the thread when running.
             */
            class ThreadContext {
                private:
                    /**
                     * @brief   The thread owning the context.
                     */
                    AbstractThread* m_owner ;

                    /**
                     * @brief   Routine that the thread mainly executes.
                     */
                    ThreadRoutine m_routine ;

                    /**
                     * @brief   Argument of the thread.
                     */
                    void* m_argument ;

                    /**
                     * @brief   Condition to stop the thread routine in a proper
                     *          and secured manner.
                     */
                    volatile bool* m_stopCondition ;


                public:
                    /**
                     * @brief   Creation of a ThreadContext.
                     */
                    ThreadContext() ;

                    /**
                     * @brief   Destruction of the ThreadContext.
                     */
                    virtual ~ThreadContext() ;

                    /**
                     * @brief   Set the owner of the context.
                     * @param   owner   Owner of the context.
                     */
                    void setOwner(AbstractThread* owner) ;

                    /**
                     * @brief   Set the routine of the thread.
                     * @param   routine     Routine that the thread mainly
                     *                      executes.
                     */
                    void setRoutine(ThreadRoutine routine) ;

                    /**
                     * @brief   Set the argument of the thread routine.
                     * @param   argument    Argument of the thread.
                     */
                    void setArgument(void* argument) ;

                    /**
                     * @brief   Set the stop condition of the thread.
                     * @param   Condition to stop the thread routine in a proper
                     *          and secured manner.
                     */
                    void setStopCondition(volatile bool* stopCondition) ;


                    /**
                     * @brief   Get the owning thread.
                     * @return  The thread owning the context.
                     */
                    AbstractThread* getOwner() const ;

                    /**
                     * @brief   Get the routine of the thread.
                     * @return  Routine that the thread mainly executes.
                     */
                    ThreadRoutine getRoutine() const ;

                    /**
                     * @brief   Get the argument of the thread routine.
                     * @return  Argument of the thread.
                     */
                    void* getArgument() const ;

                    /**
                     * @brief   Switch the value of the thread stop condition.
                     * @return  TRUE if the switch is possible, FALSE else.
                     */
                    bool switchStopCondition() ;

            } ;


        private:
            /**
             * @brief   State of the Thread
             */
            ThreadState m_state ;

            /**
             * @brief   Context of the thread.
             */
            ThreadContext m_context ;


        public:
            /**
             * @brief   Create an AbstractThread.
             */
            AbstractThread() ;

            /**
             * @brief   Destruction of the AbstractThread.
             */
            virtual ~AbstractThread() ;


            /**
             * @brief   Make the thread run its related function.
             * @param   routine         The routine to execute in the thread.
             * @param   argument        Argument given to the routine.
             * @param   stopCondition   The condition to properly stop the
             *                          thread if its routine uses a loop.
             * @warning @a stopCondition is used in loop in the routine as for
             *          example :
             *          <code>
             *          bool run = true ;
             *          while(run) { // Do something... }
             *          </code>
             */
            void run(
                     ThreadRoutine routine,
                     void* argument,
                     volatile bool* stopCondition
                    ) ;

            /**
             * @brief   Wait for the end of the thread execution.
             * @return  Returned value by the thread routine.
             */
            virtual void* join() = 0 ;

            /**
             * @brief   Force the thread to stop.
             * @return  Returned value by the thread routine. NULL if the
             *          routine has been canceled.
             */
            virtual void* stop() = 0 ;

            /**
             * @brief   Cancel the thread execution.
             */
            virtual void cancel() = 0 ;

            /**
             * @brief   Get the state of the thread.
             */
            ThreadState getState() const ;

        protected:
            /**
             * @brief   Make the thread run its related function.
             */
            virtual void run() = 0 ;

            /**
             * @brief   Get context of the thread.
             */
            ThreadContext* getContext() const ;

            /**
             * @brief   Set the state of the thread.
             * @param   state   New state of the thread.
             */
            void setState(const ThreadState& state) ;

    } ;

} ;

#endif
