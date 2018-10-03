
enum SOUND_ID
{
	//�@BGM�̋Ȑ���p��
	BGM_01,
	BGM_02,
	BGM_03,
	BGM_04,
	BGM_05,

	//�@SE�̋Ȑ���p��
	SE_HNG,
	SE_TRIGGER,
	SE_GET,
	SE_BOM,
	SE_05,

	//�z��O�␳
	SOUND_MAX

};


//////////////////////////////////////////
//
//	���g�p�@
//	
//	//�A�v���J�n����Win_Main�Ōďo
//		InitXAudio2
//
//		//��ɃV�[�����������Ōďo
//			LoadSoundFile
//				->	OpenWaveFile	(�����Ōďo�E�E�E�K�v�ȃt�@�C�����������Ń��[�h)
//
//			//�T�E���h�̎g�p��������ʂŌďo
//			SoundPlay, SoundStop, SoundAllStop
//
//		//��ɃV�[���ڍs���Ōďo
//			ReleaseSoundFile, ReleaseAllSoundFile
//
//
//
//		//
//
//
//	//�A�v���I�����Ƀ����[�X�����Ōďo
//			ReleaseXAudio2
//
//////////////////////////////////////////



//XAudio�̏�����
HRESULT InitXAudio2(void);

//�Ǎ���.wav�t�@�C�����J���ĉ��
bool OpenWaveFile(LPSTR FileName, WAVEFORMATEX &waveFormatEx, BYTE **ppData, DWORD &dataSize);

//�����t�@�C���̓ǂݍ���	->	��͂ł�����g�p��������
void LoadSoundFile(LPSTR FileName, int IN_ID);

//�T�E���h�Đ�
void SoundPlay(int ID, bool LOOP);

//�T�E���h��~
void SoundStop(int ID);

//�T�E���h�S��~
void SoundAllStop(void);

//�t�@�C��->���
void ReleaseSoundFile(int ID);

//�t�@�C��->�S���
void ReleaseAllSoundFile(void);

//XAudio�̉��
HRESULT ReleaseXAudio2(void);











