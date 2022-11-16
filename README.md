# Easy-Audio-Recording-Playback-API
##### Easy Audio Recording Playback
##### Just ten lines of code   can achieve these functions (Network transmission is possible)
### ( By HalfPeopleStudio )

# Record  Function
```cpp
//Record Demo
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
}
```
##### CreateRecordClass
```cpp
HalfSound::HRecord R = HalfSound::HRecord();
```
##### write sound to file (init)
`void InitFile(const char* Path)`
```
R.InitFile("Export.HalfSound");
```
###### Write To File
`void WriteInFile(BYTE* Record)`
```
R.WriteInFile( /* SoundData  e.g.: R.Record()   */ );
```
###### Close The File
`int CloseFile()`
```
R.CloseFile();```
###### Record

`BYTE* Record(int RecordTime_ms , DWORD NewSize = 1024 * 1024)`
`BYTE* Record()`
```
// This function locks the thread (1 second by default)
R.Record();
```
###### Resize the max Record size ( Its not mandatory )
`void Resize(size_t NewSize)`
```
R.Resize( 1024*1024 )
```
###### GetRecord The Size ( Its not mandatory )
`size_t RecordSize()`
```
R.RecordSize();
```
###### Close The Class
```	
R.~HRecord();
```
# Play Function
```cpp
//Play Demo
#include "HalfPeopleSoundAPI(Windows).h"
using namespace HalfSound;

int main()
{
	HPlay P = HPlay();
	
	P.InitFile("Export.HalfSound");
	
	while (P.HaveLoop())
	{
		P.Play(P.ReadFile());
	
		P.ReadFileEnd();
	}
	P.CloseFile();
	P.~HPlay();
}
```
##### CreatePlayClass
```cpp
HalfSound::HPlay P = HalfSound::HPlay();
```
##### read sound file (init)
`void InitFile(const char* FileName, DWORD Size = 1024 * 1024 * 4)`
```
P.InitFile("Export.HalfSound");
```
###### get play sound file have loop
`bool HaveLoop()`
```
P.HaveLoop()
```
###### read file SoundData (form line)
`LPSTR ReadFile()`
```
P.ReadFile()
//e.g. P.Play(P.ReadFile());
```
###### get read file Sound Size (form line)
`size_t ReadFileSize()`
``` 
P.ReadFileSize()
```
###### read next line
`void ReadFileEnd()`
```
P.ReadFileEnd();
```
###### Close The File
`int CloseFile()`
```cpp
P.CloseFile();
```
###### Play

`void Play(LPSTR PlayData)`
`void Play(LPSTR PlayData , size_t PlaySize)`
```cpp
P.Play( ... );
//e.g. P.Play(P.ReadFile());
```
###### Close The Class
```
P.~HPlay();
```
# echo sample (non-full version  have BUG)
### Multithreading will solve
```cpp
#include "HalfPeopleSoundAPI(Windows).h"
using namespace HalfSound;

int main()
{
	HRecord R = HRecord();
	HPlay P = HPlay();

	while (true)
	{
		P.Play((LPSTR)R.Record(), R.RecordSize());
	}
}
```
