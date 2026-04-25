//---------------------------------------------------------------------------

#ifndef ExtraH
#define ExtraH
//---------------------------------------------------------------------------



#include <vcl.DBGrids.hpp>


void __fastcall BestFitDBGridColumn(
    TDBGrid* Grid, TColumn* Col, int MaxRowsToScan /*0 = all*/, int Padding /*pixels*/);

#endif
