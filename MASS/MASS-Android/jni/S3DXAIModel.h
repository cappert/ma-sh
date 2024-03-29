//-----------------------------------------------------------------------------
#ifndef __S3DXAIModel_h__
#define __S3DXAIModel_h__
//-----------------------------------------------------------------------------
#include "S3DXAIVariable.h"
#include "S3DXAIEngineAPI.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace S3DX
//-----------------------------------------------------------------------------
{
    class AIModel
    {
    protected :

        //---------------------------------------------------------------------
        //  Common AIModel instance methods 
        //  (corresponding to the built-in this.xxx function in the script)
        //---------------------------------------------------------------------
        AIVariable  getObject       ( ) const ;
        AIVariable  getUser         ( ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10, const AIVariable &_vArg11 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10, const AIVariable &_vArg11, const AIVariable &_vArg12 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10, const AIVariable &_vArg11, const AIVariable &_vArg12, const AIVariable &_vArg13 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10, const AIVariable &_vArg11, const AIVariable &_vArg12, const AIVariable &_vArg13, const AIVariable &_vArg14 ) const ;
        void        sendEvent       (                            const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10, const AIVariable &_vArg11, const AIVariable &_vArg12, const AIVariable &_vArg13, const AIVariable &_vArg14, const AIVariable &_vArg15 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10, const AIVariable &_vArg11 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10, const AIVariable &_vArg11, const AIVariable &_vArg12 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10, const AIVariable &_vArg11, const AIVariable &_vArg12, const AIVariable &_vArg13 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10, const AIVariable &_vArg11, const AIVariable &_vArg12, const AIVariable &_vArg13, const AIVariable &_vArg14 ) const ;
        void        postEvent       ( const AIVariable &_nDelay, const AIVariable &_sEventName, const AIVariable &_vArg0, const AIVariable &_vArg1, const AIVariable &_vArg2, const AIVariable &_vArg3, const AIVariable &_vArg4, const AIVariable &_vArg5, const AIVariable &_vArg6, const AIVariable &_vArg7, const AIVariable &_vArg8, const AIVariable &_vArg9, const AIVariable &_vArg10, const AIVariable &_vArg11, const AIVariable &_vArg12, const AIVariable &_vArg13, const AIVariable &_vArg14, const AIVariable &_vArg15 ) const ;
        void        sendStateChange (                            const AIVariable &_sStateName ) ;
        void        postStateChange ( const AIVariable &_nDelay, const AIVariable &_sStateName ) ;

        //---------------------------------------------------------------------
        //  Private AIModel instance methods 
        //---------------------------------------------------------------------
        AIVariable  __getVariable   ( const AIVariable &_sName ) const ;
        AIVariable  __setVariable   ( const AIVariable &_sName, const AIVariable &_vValue ) const ;
    } ;

    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
