/******************************************************************************
  文 件 名   : mthread.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "mthread.h"
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <QDir>
#include <QCryptographicHash>

#define FILE_TEST_DIR   "/oem/developer/testapp/filetest_dir/filetest/"
#define WN_TEST_DIR     "/oem/developer/testapp/filetest_dir/wntest/"

#define FILE_SIZE   10240

int small_file_wr_cnt = 0;

mThread::mThread(QWidget *parent)
{


    file_error_cnt = 0;
    g_file_test = 0;
    show_color_timeout_flag = 0;

    QDir testDir(FILE_TEST_DIR);

    if(testDir.exists() == false)
    {
        system("mkdir -p /oem/developer/testapp/filetest_dir/filetest");
    }
}

QString mThread::getFileMd5(QString filename)
{
    QFile theFile(filename);
    if(!theFile.open(QIODevice::ReadOnly))
    {
        return "failed";
    }
    QByteArray ba = QCryptographicHash::hash(theFile.readAll(),QCryptographicHash::Md5);
    theFile.close();
    return QString(ba.toHex());
}

int mThread::fileCompare(QString File1, QString File2)
{
    int ret = 0;
    QFile destFile(File1);
    QFile srcFile(File2);

    if(!destFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
    }

    if(!srcFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        destFile.close();
        return 0;
    }

    QByteArray destData = destFile.readAll();
    QByteArray srcData = srcFile.readAll();
    char *dData = destData.data();
    char *sData = srcData.data();
    int len = srcData.length();

    if(destData.length() != srcData.length())
    {
        srcFile.close();
        destFile.close();
        return -1;
    }

    for(int i = 0; i < len; i++)
    {
        if(dData[i] != sData[i])
        {
            ret = -1;
            break;
        }
    }

    srcFile.close();
    destFile.close();
    return ret;
}

void mThread::file_test(void)
{

    if(++small_file_wr_cnt >= 4)
    {
        QDir dir(WN_TEST_DIR);

        small_file_wr_cnt = 0;
        dir.setFilter(QDir::Files);

        foreach(QFileInfo testfile, dir.entryInfoList())
        {
            if(testfile.fileName() == "." || testfile.fileName() == "..")
            {
                continue;
            }

//            ret = fileCompare(QString("/developer/wnfiletest/") + testfile.fileName(), QString(WN_TEST_DIR) + testfile.fileName());
//            if(ret != 0)
           QString sourceMd5 =  getFileMd5(QString("/oem/developer/wnfiletest/") + testfile.fileName());
           QString destMd5 =  getFileMd5(QString(WN_TEST_DIR) + testfile.fileName());
           if(sourceMd5 != destMd5)
            {
                file_error_cnt++;
                emit setfile_error_cnt(file_error_cnt);
                //QFile::remove(QString(WN_TEST_DIR) + testfile1.fileName());

                QFile log_file("/oem/developer/testapp/filetest_dir/file_error_cnt.log");
                if(log_file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
                {
                    QByteArray tmp;
                    tmp = testfile.fileName().toLatin1();
                    log_file.write(tmp.constData(), tmp.length());
                    log_file.write(QByteArray("\n", 1));
                    log_file.close();
                }
            }

            QFile::remove(QString(WN_TEST_DIR) + testfile.fileName());
            system("sync");
            //sleep(1);
        }

        //system("cp /developer/filetest/* /developer/testapp/filetest_dir/filetest/");
        //QDir dir1("/developer/filetest");
        QDir dir1("/oem/developer/wnfiletest");
//        QDir testDir(FILE_TEST_DIR);

//        if(testDir.exists() == false)
//        {
//            system("mkdir -p /developer/testapp/filetest_dir/filetest");
//        }

        QDir testDir(WN_TEST_DIR);

        if(testDir.exists() == false)
        {
            system("mkdir -p /oem/developer/testapp/filetest_dir/wntest");
        }

        foreach(QFileInfo testfile1, dir1.entryInfoList())
        {
            if(testfile1.fileName() == "." || testfile1.fileName() == "..")
            {
                continue;
            }

            QByteArray sourcefile;
            bool ret;
            if(testfile1.isFile())
            {
                QFile a(QString("/oem/developer/wnfiletest/")+testfile1.fileName());
                if(a.open(QFile::ReadOnly))
                {
                    sourcefile = a.readAll();
                    a.close();

                    wntest_file = new QFile(QString(WN_TEST_DIR) + testfile1.fileName());
                    ret = wntest_file->open(QIODevice::WriteOnly | QIODevice::Truncate);

                    if(ret == false)
                    {
                        return;
                    }
                    else
                    {

                        //wntest_file->write((const char *)str);
                        wntest_file->write(sourcefile);
                        wntest_file->flush();
                        wntest_file->close();
                    }
                   // sleep(1);
                }
                else
                {
                    return;
                }
            }
        }

        system("sync");
    }
}

void mThread::set_file_test_enable(int en)
{
    g_file_test = en;
}

void mThread::file_del(void)
{
    QFile *update_log_file = new QFile("/oem/developer/testapp/writetest.txt");

    if(update_log_file->exists())
    {
        update_log_file->remove();
    }
}

void mThread::run()
{
    while(1)
    {
       if(g_file_test == 1)
       {
           file_test();
       }

       if(show_color_timeout_flag == 1)
       {
           show_color_timeout_flag = 0;
           //system("sh /developer/show_color_timeout.sh");
       }

       usleep(100000);
    }
}
