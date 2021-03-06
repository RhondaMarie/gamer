#include "GAMER.h"

#if ( MODEL == HYDRO )



// prototypes of built-in EoS
#if   ( EOS == EOS_GAMMA )
void EoS_Init_Gamma();
#elif ( EOS == EOS_NUCLEAR )
# error : ERROR : EOS_NUCLEAR is NOT supported yet !!
#endif // # EOS

// this function pointer must be set by a test problem initializer for non-built-in EoS
void (*EoS_Init_Ptr)() = NULL;




//-------------------------------------------------------------------------------------------------------
// Function    :  EoS_Init
// Description :  Initialize the equation of state (EoS)
//
// Note        :  1. Invoked by Init_GAMER()
//                2. For a non-built-in EoS, "EoS_Init_Ptr" must be set by a test problem initializer
//                   in advance
//
// Parameter   :  None
//
// Return      :  None
//-------------------------------------------------------------------------------------------------------
void EoS_Init()
{

   if ( MPI_Rank == 0 )    Aux_Message( stdout, "%s ...\n", __FUNCTION__ );


// set the initialization function pointer for the built-in EoS
#  if   ( EOS == EOS_GAMMA )
   EoS_Init_Ptr = EoS_Init_Gamma;
#  elif ( EOS == EOS_NUCLEAR )
#  error : ERROR : EOS_NUCLEAR is NOT supported yet !!
#  endif // # EOS


// initialize EoS
   if ( EoS_Init_Ptr != NULL )
      EoS_Init_Ptr();
   else
      Aux_Error( ERROR_INFO, "EoS_Init_Ptr == NULL for EoS %d !!\n", EOS );


   if ( MPI_Rank == 0 )    Aux_Message( stdout, "%s ... done\n", __FUNCTION__ );

} // FUNCTION : EoS_Init



#endif // #if ( MODEL == HYDRO )
