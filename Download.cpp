/*
 *   Copyright (C) 2023 Gene Gajewski WG5ENE
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Download.h"
#include <system.IOUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDL *DL;
//---------------------------------------------------------------------------
__fastcall TDL::TDL(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool TDL::GetFile(String &url, String &filename)
{
	using System::Ioutils::TPath;
    ABORT=false;

	try {
		String basefile = TPath::GetFileName(url);
		filename =
			TPath::Combine(TPath::GetDownloadsPath(), basefile);
		Caption = "Downloading: " + basefile;

		_di_IHTTPResponse LResponse = FClient->Head(url);
		__int64 LSize = LResponse->ContentLength;

		ProgressBar1->Max = LSize;
		ProgressBar1->Min = 0;
		ProgressBar1->Position = 0;

		// Create the file that is going to be downloaded
		FDownloadStream = new TFileStream(filename, fmCreate);
		FDownloadStream->Position = 0;

		FGlobalStart = TThread::GetTickCount();

		// synchronous http download
		FHTTPResponse = FClient->Get(url, FDownloadStream);

		__int64 fsize = FDownloadStream->Size;
		FDownloadStream->Free();

		if(FHTTPResponse->StatusCode == 200)
		{
			if(fsize == LSize)
				return true;
		}
	}
	catch(...)
	{
	  // exceptions?
	}

	// failed

	if(FileExists(filename))
		DeleteFile(filename);
	filename = "";
	return  false;
}
//---------------------------------------------------------------------------
void TDL::UpdateProgress(int AValue, float ASpeed, bool &Abort)
{
    Abort = ABORT;
	ProgressBar1->Position = AValue;
	String s;
	s.sprintf(L"%0.2f MB/s", ASpeed / 1000000.0);
	Label1->Caption = s;
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TDL::ReceiveDataEvent(TObject* const Sender,
	__int64 AContentLength, __int64 AReadCount, bool &Abort)
{
	if (Abort == false) {
		UInt32 LTime = TThread::GetTickCount() - FGlobalStart;
		float LSpeed = (AReadCount * 1000) / LTime;

		bool LAbort = Abort;
		System::Classes::TThread::Synchronize(
			NULL, SyncLambda<int, float, bool &>(
					  &this->UpdateProgress, AReadCount, LSpeed, LAbort));
		Abort = LAbort;
	}
}
//--------------------------------------------------------------------------
void __fastcall TDL::BtnAbortClick(TObject *Sender)
{
	ABORT = true;
}
//---------------------------------------------------------------------------
void __fastcall TDL::FormCreate(TObject *Sender)
{
	FClient = THTTPClient::Create();
	FClient->OnReceiveData = ReceiveDataEvent;
}
//---------------------------------------------------------------------------
void __fastcall TDL::FormDestroy(TObject *Sender)
{
	FClient->Free();
}
//---------------------------------------------------------------------------

