/**
 * @brief 	Mask to perform logical operations on Vector4.
 */
class Mask {
	private:
		/** @brief 	Inner vector of booleans. */
		int32x4_t m_inner ;


                              				  /** CONSTRUCTION / DESTRUCTION **/
        /** @brief  Prevent construction from integers. */
        Mask(const int& value) ;

        /**
         * @brief   Prevent affecting integer values.
         * @return  Nothing to use.
         */
        Mask& operator=(const int&) ;


    public:
        /**
         * @brief   Create an empty Mask.
         */
        Mask() ;

        /**
         * @brief   Create from four boolean values.
         * @param   b1  First value mask.
         * @param   b2  Second value mask.
         * @param   b3  Third value mask.
         * @param   b4  Fourth value mask.
         */
        Mask(
             const bool& b0,
             const bool& b1,
             const bool& b2,
             const bool& b3
            ) ;

        /**
         * @brief   Create from one boolean, applied to all components of the
		 *			Mask.
         * @param   value   The boolean to apply to all values of the Mask.
         */
        Mask(const bool& value) ;

        /**
         * @brief   Create from inner type data.
         * @param   vec     The inner data to copy.
         */
        Mask(const int32x4_t& vec) ;


        /**
		 * @brief  	Destruction of the Mask.
		 */
        virtual ~Mask() ;


                                             				 /*** UTILITIES ***/
        /**
         * @brief   Get values from the mask (unaligned).
         * @param   array   Array in which Mask values are stored.
         * @return  Value in the mask at the given index.
         */
        void get(AlignedArray4i& array) ;

        /**
         * @brief   Get one value from the mask.
         * @param   index   Index of the value to get (should be lower than
		 *					length).
         * @return  Value in the mask at the given index.
         */
        bool get(const unsigned int& index) ;

        /**
         * @brief   Get the length of the Mask.
         * @return  The length of the Mask.
         */
        size_t length() const ;


        /**
         * @brief   Size of the Mask.
         * @return  The length of the Mask.
         */
        static size_t size() ;


                                             				 /*** OPERATORS ***/
                                        				/** AFFECT OPERATORS **/
        /**
         * @brief   Get the values from another Mask and put it in inner data.
         * @param   mask    The mask to copy.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const Mask& mask) ;

        /**
         * @brief   Affect the inner value of the Mask to the
         *          broadcasted one given as parameter.
         * @param   value   The value to put in the Mask, to all its values.
         * @return  The current Mask once the value is affected to its inner
		 *			data.
         */
        Mask& operator=(const bool& value) ;

        /**
         * @brief   Affect the inner value to the Mask.
         * @param   vec     The value to put in the Mask.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const int32x4_t& vec) ;

        /**
         * @brief   Affect the inner value to the Mask.
         * @param   vec     The value to put in the Mask.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const float32x4_t& vec) ;

                                          				  /** CAST OPERATORS **/
		/**
		 * @brief   Cast the current Mask to its inner data type.
		 * @return  The inner data of the Mask.
		 */
		operator int32x4_t() const ;

		/**
		 * @brief   Cast the current Mask to its inner data type.
		 * @return  The inner data of the Mask.
		 */
		operator int32x4_t*() const ;

		/**
         * @brief   Cast the current Mask to its inner data type.
         * @return  The inner data of the Mask.
         */
        operator float32x4_t() ;
} ;
