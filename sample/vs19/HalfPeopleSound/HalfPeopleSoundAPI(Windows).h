//#########################################################################################
//							This Code By HalfPeople Studio
//	   Github   : https://github.com/Half-People/Easy-Audio-Recording-Playback-API
//	   YouTube 1: https://www.youtube.com/channel/UCzxYUnoPAv5-9RAkwVYCuPA
//     YouTube 2: https://www.youtube.com/channel/UCKv63XONExN6JtUriTqP9Ew 
//     BiliBili : https://space.bilibili.com/443124242/video
// 
//#########################################################################################

#pragma once
#if _WIN32
#include <Windows.h>
#include <iostream>

#pragma comment (lib,"winmm.lib")
namespace HalfSound
{
	class HRecord
	{
	public:
		HRecord()
		{
			waveform.wFormatTag = WAVE_FORMAT_PCM;
			waveform.nSamplesPerSec = 8000;
			waveform.wBitsPerSample = 16;
			waveform.nChannels = 1;
			waveform.nAvgBytesPerSec = 16000;
			waveform.nBlockAlign = 2;
			waveform.cbSize = 0;

			wait = CreateEvent(NULL, 0, 0, NULL);

			waveInOpen(&hWaveIn, WAVE_MAPPER , &waveform , (DWORD_PTR)wait,0L, CALLBACK_EVENT);

		}
		~HRecord()
		{
			waveInClose(hWaveIn);
		}

		void Resize(size_t NewSize)
		{
			bufsize = NewSize;
		}

		//Record 1 sec ( This Function Have Sleep )
		BYTE* Record()
		{
			BYTE* pBuffer1 = new BYTE[bufsize];
			wHdr1.lpData = (LPSTR)pBuffer1;
			wHdr1.dwBufferLength = bufsize;
			wHdr1.dwBytesRecorded = 0;
			wHdr1.dwFlags = 0;
			wHdr1.dwLoops = 1;

			waveInPrepareHeader(hWaveIn, &wHdr1, sizeof(WAVEHDR));
			waveInAddBuffer(hWaveIn, &wHdr1, sizeof(WAVEHDR));

			waveInStart(hWaveIn);
			Sleep(1000);
			waveInReset(hWaveIn);

			return pBuffer1;
		}

		BYTE* Record(int RecordTime_ms , DWORD NewSize = 1024 * 1024)
		{
			BYTE* pBuffer1 = new BYTE[NewSize];
			wHdr1.lpData = (LPSTR)pBuffer1;
			wHdr1.dwBufferLength = NewSize;
			wHdr1.dwBytesRecorded = 0;
			wHdr1.dwFlags = 0;
			wHdr1.dwLoops = 1;

			waveInPrepareHeader(hWaveIn, &wHdr1, sizeof(WAVEHDR));
			waveInAddBuffer(hWaveIn, &wHdr1, sizeof(WAVEHDR));

			waveInStart(hWaveIn);
			Sleep(1000);
			waveInReset(hWaveIn);
			return pBuffer1;
		}

		size_t RecordSize()
		{
			return wHdr1.dwBytesRecorded;
		}

		void InitFile(const char* Path)
		{
			fopen_s(&file, Path, "wb");
		}

		void WriteInFile(BYTE* Record)
		{
			fwrite(Record, 1, wHdr1.dwBytesRecorded, file);
			delete Record;
		}

		int CloseFile()
		{
			waveInClose(hWaveIn);
			return fclose(file);
		}

	private:
		HWAVEIN hWaveIn;

		WAVEFORMATEX waveform;
		WAVEHDR wHdr1;

		//BYTE* pBuffer1;
		HANDLE	wait;

		DWORD bufsize = 1024 * 1024;
		FILE* file;
	};

	class HPlay
	{
	public:
		HPlay()
		{
			waveform.wFormatTag = WAVE_FORMAT_PCM;
			waveform.nSamplesPerSec = 8000;
			waveform.wBitsPerSample = 16;
			waveform.nChannels = 1;
			waveform.nAvgBytesPerSec = 16000;
			waveform.nBlockAlign = 2;
			waveform.cbSize = 0;

			wait = CreateEvent(NULL, 0, 0, NULL);

			waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveform, (DWORD_PTR)wait, 0L, CALLBACK_EVENT);
		}
		~HPlay()
		{
			waveOutClose(hWaveOut);
		}



		// Play Sound Have Loop (form File)
		bool HaveLoop()
		{
			return cnt;
		}

		void InitFile(const char* FileName, DWORD Size = 1024 * 1024 * 4)
		{
			fopen_s(&file, FileName, "rb");
			buf = new char[Size];
			dolenght = new int(0);
			playsize = new int(1024);
			cnt = fread(buf, sizeof(char), Size, file);
		}

		int CloseFile()
		{
			delete buf;
			delete playsize;
			delete dolenght;
			waveOutClose(hWaveOut);
			return fclose(file);
		}


		LPSTR ReadFile()
		{
			return buf + *dolenght;
		}
		size_t ReadFileSize()
		{
			return *playsize;
		}
	
		void Play(LPSTR PlayData)
		{
			wHdr1.lpData = PlayData;
			wHdr1.dwBufferLength = *playsize;
			wHdr1.dwFlags = 0;
			wHdr1.dwLoops = 1L;

			waveOutPrepareHeader(hWaveOut, &wHdr1, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &wHdr1, sizeof(WAVEHDR));
			WaitForSingleObject(wait, INFINITE);
		}

		void Play(LPSTR PlayData , size_t PlaySize)
		{
			wHdr1.lpData = PlayData;
			wHdr1.dwBufferLength = PlaySize;
			wHdr1.dwFlags = 0;
			wHdr1.dwLoops = 1L;

			waveOutPrepareHeader(hWaveOut, &wHdr1, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &wHdr1, sizeof(WAVEHDR));
			WaitForSingleObject(wait, INFINITE);

		}

		// In Not Play Sound Go To Next Loop
		void ReadFileEnd()
		{
			*dolenght = *dolenght + *playsize;
			cnt = cnt - *playsize;
		}
	private:
		HWAVEOUT hWaveOut;

		WAVEFORMATEX waveform;
		WAVEHDR wHdr1;

		//BYTE* pBuffer1;
		HANDLE	wait;


		FILE* file;

		char* buf;
		int cnt;
		int *dolenght;
		int *playsize;
	};


#if _DEBUG
	void HRecordDemo()
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

	void HPlayDemo()
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
#endif // 0
}
#endif // 0
