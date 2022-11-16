#include "HalfPeopleSoundAPI(Windows).h"
using namespace HalfSound;
int main()
{

	HRecord R = HRecord();
	std::cout << "\n Init Record";
	R.InitFile("Export.HalfSound");
	std::cout << "\n Init Record Save File";
	std::cout << "\n Start Record";
	int i = 10;
	while (i--)
	{
		R.WriteInFile(R.Record());
		std::cout << "\n Recording ... " << 10 - i << "s";
	}
	R.CloseFile();
	R.~HRecord();

	std::cout << "\n\n Start Play !!";

	HPlay P = HPlay();
	
	P.InitFile("Export.HalfSound");
	
	while (P.HaveLoop())
	{
		P.Play(P.ReadFile());
	
		P.ReadFileEnd();
	}
	P.CloseFile();
	P.~HPlay();

	std::cout << "\n Play End ";
	std::cout << "\n Start Echo Sample (non-full version have BUG   Multithreading will solve ) ";

	HRecord R_ = HRecord();
	HPlay P_ = HPlay();
	
	while (true)
	{
		P_.Play((LPSTR)R_.Record(), R_.RecordSize());
	}

}