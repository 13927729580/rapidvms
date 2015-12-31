#ifndef __VSC_STOR_STREAM_H__
#define __VSC_STOR_STREAM_H__
#include "config/confdb.hpp"
#include "server/camera.hpp"
#include "vdb.hpp"
#include "vhdfsdb.hpp"
#include "vplay.hpp"
#include "config/sysdb.hpp"
#include "server/hdddevice.hpp"
#include <QThread>
#include <qdebug.h>
#include "Poco/Path.h"
#include "Poco/File.h"
#include "config/vidconf.pb.h"
#include "server/camera.hpp"

class StorStream: public QThread
{
	Q_OBJECT
public:
	StorStream(VidStor &stor, astring strId, unsigned int nStream);
	~StorStream();
	bool AttachWidget(HWND hWnd, int w, int h);
	bool UpdateWidget(HWND hWnd, int w, int h);
	bool DetachWidget(HWND hWnd);

	bool RegDataCallback(CameraDataCallbackFunctionPtr pCallback, void * pParam);
	bool UnRegDataCallback(void * pParam);

public:
	bool StartStorStream();
	bool StopStorStream();
public:
	void run();
	
private:
	XMutex m_cMutex;
	
private:
	bool m_Quit;
	VPlay m_play;
	astring m_strId;
	unsigned int m_nStream;
	VidStor m_stor;
	
	CameraDataCallbackFunctionPtr m_pCallback; 
	void * m_pParam;

	XRef<XSocket> m_pSocket;
};

typedef StorStream* LPStorStream;


#include "storstreamimpl.hpp"

#endif