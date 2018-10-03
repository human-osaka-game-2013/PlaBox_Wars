#include "main.h"
#include "Audio.h"


//�f�o�C�X�̏���
IXAudio2*					pXAudio2;
IXAudio2MasteringVoice*	pMasteringVo;
IXAudio2SourceVoice*		pSourceVo[SOUND_MAX]	= {0};
XAUDIO2_BUFFER			buffer[SOUND_MAX]		= {0};

//�@X�I�[�f�B�I�̏�����
HRESULT InitXAudio2(void)
{
	HRESULT			hr = NULL;
	unsigned int flag = 0;

	//CO_M��������
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	pXAudio2 = NULL;
	hr = XAudio2Create(&pXAudio2,flag,XAUDIO2_DEFAULT_PROCESSOR);

	if(SUCCEEDED(hr))
	{
		hr = pXAudio2->CreateMasteringVoice(&pMasteringVo,0,0,0,0,0);
		if(FAILED(hr))
		{
			//�G���[���ɂ̓��b�Z�[�W�{�b�N�X�ŕ\��
			ShowCursor(true);
			MessageBox(NULL,TEXT("�I�[�f�B�I�̍쐬�Ɏ��s"),TEXT("���������s"),S_OK);
			ShowCursor(false);
		}
	}

	else
	{
		//�G���[���ɂ̓��b�Z�[�W�{�b�N�X�ŕ\��
			ShowCursor(true);
			MessageBox(NULL,TEXT("�I�[�f�B�I�̍Đ��Ɏ��s���܂����B"),TEXT("XAudio2��NULL"),S_OK);
			ShowCursor(false);
	}

	return hr;

}



//.wav�t�@�C�����J���ĉ��
bool OpenWaveFile(LPSTR FileName,WAVEFORMATEX &waveFormatEx, BYTE **ppData, DWORD &dataSize)
{
	if(FileName == 0)
	{
		return false;
	}

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	//Wave�t�@�C���I�[�v��
	memset( &mmioInfo,0,sizeof(MMIOINFO) );
	hMmio = mmioOpen(FileName, &mmioInfo, MMIO_READ);

	if(!hMmio)
	{
		return false;		//�t�@�C���I�[�v���Ɏ��s
	}

	// RIFF�`�����N����
	MMRESULT		mmRes;
	MMCKINFO		riffChunk;

	riffChunk.fccType = mmioFOURCC('W','A','V','E');	//WAVE�t�@�C�������m�F�H�H
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);

	if(mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	//�t�H�[�}�b�g�`�����N����
	MMCKINFO	formatChunk;
	formatChunk.ckid = mmioFOURCC('f','m','t',' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);

	if(mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	DWORD fmsize	= formatChunk.cksize;
	DWORD size	= mmioRead(hMmio, (HPSTR)&waveFormatEx, fmsize);

	if(size != fmsize)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &formatChunk, 0);

	//�f�[�^�`�����N����
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d','a','t','a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);

	if(mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	*ppData = new BYTE[ dataChunk.cksize];
	size = mmioRead(hMmio, (HPSTR)*ppData, dataChunk.cksize);

	if(size != dataChunk.cksize)
	{
		delete[] *ppData;
		return false;
	}
	dataSize = size;

	//�n���h���N���[�Y
	mmioClose(hMmio, 0);

	return true;
}


//.wav�t�@�C���̓ǂݍ���
void LoadSoundFile (LPSTR FileName, int IN_ID)
{
	//////////////////////////////////
	//	�T�E���h�f�[�^(.wav�t�@�C��)�̓ǂݍ���
	//	�t�@�C������ID���w��
	//	(Audio.h�Ɉ�����n��)
	//////////////////////////////////

	//����ID�ւ̏㏑�����N�������ہA�ȑO�̂��̂��������(���������[�N�h�~)
	if(buffer[IN_ID].pAudioData != NULL)
	{
		ReleaseSoundFile(IN_ID);
	}

	HRESULT		hr;
	WAVEFORMATEX	wFmt;
	BYTE*		pWaveData	= 0;
	DWORD		waveSize	= 0;

	if(pXAudio2 != NULL)
	{
		if(!OpenWaveFile (FileName, wFmt, &pWaveData, waveSize) )
		{
			//���s�������������b�Z�[�W�{�b�N�X�ŕ\��
			ShowCursor(true);
			MessageBox(NULL,FileName, TEXT("�Ǎ����s"), S_OK);
			ShowCursor(false);
			return;
		}

		if(FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVo[IN_ID],&wFmt, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, NULL, NULL) ) )
		{
			//���s�������������b�Z�[�W�{�b�N�X�ŕ\��
			ShowCursor(true);
			MessageBox(NULL, TEXT("SourceVoice�̃N���G�C�g�Ɏ��s"), TEXT("�G���["), S_OK);
			ShowCursor(false);
			return;
		}

		//�o�b�t�@�[�֒l���Z�b�g
		buffer[IN_ID].AudioBytes	= waveSize;
		buffer[IN_ID].pAudioData	= pWaveData;
		buffer[IN_ID].Flags		= XAUDIO2_END_OF_STREAM;

	}

	return;
}


//-------------------------------------------------------
//	�����܂ł����y�t�@�C���̏���
//-------------------------------------------------------



//�����t�@�C���̍Đ�
void SoundPlay (int ID, bool LOOP)
{

	//--------------------------------------------------------------------
	//	�����̍Đ�
	//	����
	//	ID	->	�Đ��������f�[�^��ID���w��iDxAudioX2.h�ɂė񋓂��Ă���j
	//	LOOP	->	���[�v���邩�ǂ����H���w�肷��
	//---------------------------------------------------------------------


	//�Đ����̃t�@�C�����������ꍇ�ɔ����āA�O�̂��߂̒�~����
	SoundStop(ID);

	if(buffer[ID].pAudioData != NULL)
	{
		buffer[ID].LoopBegin	= 0;
		buffer[ID].LoopLength	= 0;
		buffer[ID].PlayBegin	= 0;
		buffer[ID].PlayLength	= 0;

		if(LOOP)
		{
			//���[�v�̎w�肪�������ꍇ���[�v�̐ݒ�
			buffer[ID].LoopCount	= XAUDIO2_LOOP_INFINITE;
		}
		
		pSourceVo[ID]->SubmitSourceBuffer(&buffer[ID]);
		pSourceVo[ID]->Start(0);
		
	}
}

//�����t�@�C���̒�~
void SoundStop (int ID)
{
	//--------------------------------------------
	//	�����̒�~
	//	����
	//	ID	->	��~�������f�[�^��ID���w��iDxAudioX2.h�ɂė񋓂��Ă���j
	//--------------------------------------------

	if(buffer[ID].pAudioData != NULL)
	{
		if(buffer[ID].LoopCount == XAUDIO2_LOOP_INFINITE)
		{
			buffer[ID].LoopCount = 0;
		}

		pSourceVo[ID]->Stop(0);

		pSourceVo[ID]->FlushSourceBuffers();
	}
}


//�S�Ẳ����t�@�C�����~����
void SoundAllStop (void)
{
	//--------------------------------------------
	//	���ׂẲ����̒�~
	//	���������őS��~
	//--------------------------------------------

	//�T�E���h�f�[�^�̍ő吔����~���������s
	for(int LOOP = 0; LOOP < SOUND_MAX; LOOP++)
	{
		//�Đ��f�[�^������
		if(buffer[LOOP].pAudioData != NULL)
		{
			SoundStop(LOOP);
		}
	}
}



//�����t�@�C���̉��
void ReleaseSoundFile(int ID)
{
	//�O���ߍĐ���~
	pSourceVo[ID] -> Stop( 0 );

	NULL_ARRAY_DELETE( buffer[ID].pAudioData );

	pSourceVo[ID] -> DestroyVoice( );
	pSourceVo[ID] = NULL;
	
	return;

}

//�S�Ẳ����t�@�C���̉��
void ReleaseAllSoundFile(void)
{
	//�T�E���h�f�[�^�̍ő吔����~���������s
	for(int LOOP = 0; LOOP < SOUND_MAX; LOOP++)
	{
		//�Đ��f�[�^������
		if(buffer[LOOP].pAudioData != NULL)
		{
			ReleaseSoundFile(LOOP);
		}
	}
}


//	X�I�[�f�B�I�̉�����s��
HRESULT ReleaseXAudio2(void)
{
	//�Đ����̃t�@�C�����������ꍇ�ɔ����āA�O�̂��߂̒�~����
	SoundAllStop();
	ReleaseAllSoundFile();


	if(pMasteringVo)
	{
		//�ǂݍ���Ń������ɕۑ�����Ă��鉹���t�@�C�������
		pMasteringVo->DestroyVoice();
		pMasteringVo = NULL;
	}

	if(pXAudio2)
	{
		// XAudio���̂����
		SAFE_RELEASE(pXAudio2);
		pXAudio2 = NULL;
	}



	//	PG�T�c�̊��ł̓R�����g�A�E�g���Ȃ��ƃG���[���o��͗l
	//	12/12

	// CO_M�̏�����
	CoUninitialize();

	return S_OK;

}