// IniEx.cpp: implementation of the CIniEx class.
//
//////////////////////////////////////////////////////////////////////


#include "IniEx.h"

 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//GrowSize for Dynmiz Section Allocation
CIniEx1::CIniEx1()
{
   m_ConfigFileName = "Utilization.ini";
}

CIniEx1::~CIniEx1()
{
}


/** No descriptions */
int CIniEx1::GetIntValue( QString p_Section, QString p_Name, int p_iDefValue )
{
  QFile file;
  QString strSection;
  
  if( m_ConfigFileName.isEmpty() )
  {
    return p_iDefValue;
  }

  file.setFileName( m_ConfigFileName );
  if( !file.exists() )
  {
     return p_iDefValue;
  }

  if( !file.open( QIODevice::ReadOnly) )
  {
    return p_iDefValue;
  }

  strSection = "[" + p_Section + "]";
  {
    int iFind;
    QString line;
    QTextStream stream(&file);
    while ( !stream.atEnd() )
    {
       line = stream.readLine(); // line of text excluding '\n'
       if( line == strSection )
       {
          while ( !stream.atEnd() )
          {
            line = stream.readLine(); // line of text excluding '\n'
            iFind = line.indexOf( "[" );
            if( iFind != -1 )
            {
              break;
            }
            iFind = line.indexOf( p_Name );
            if( iFind != -1 )
            {
              int iRtn;
              iRtn = line.mid( iFind + p_Name.length() + 1 ).toInt();
              file.close();
              return iRtn;
            }
          }
          break;
       }
    }

  }
  file.close();
  return p_iDefValue;    
}
/** No descriptions */
QString CIniEx1::GetStringValue( QString p_Section, QString p_Name, QString p_DefValue )
{
  QFile file;
  QString strSection;

  if( m_ConfigFileName.isEmpty() )
  {
    return p_DefValue;
  }

  file.setFileName( m_ConfigFileName );
  if( !file.exists() )
  {
     return p_DefValue;
  }

  if( !file.open( QIODevice::ReadOnly ) )
  {
    return p_DefValue;
  }

  strSection = "[" + p_Section + "]";
  {
    int iFind;
    QString line;
    QTextStream stream(&file);
    while ( !stream.atEnd() )
    {
       line = stream.readLine(); // line of text excluding '\n'
       if( line == strSection )
       {
          while ( !stream.atEnd() )
          {
            line = stream.readLine(); // line of text excluding '\n'
            iFind = line.indexOf( "[" );
            if( iFind != -1 )
            {
              break;
            }
            iFind = line.indexOf( p_Name );
            if( iFind != -1 )
            {
              QString strRtn;
              strRtn = Unicode2GBK(line.mid( iFind + p_Name.length() + 1 ));
              file.close();
              return strRtn;
            }
          }
          break;
       }
    }

  }
  file.close();
  return p_DefValue;
}
/** No descriptions */
QString CIniEx1::GetCStringValue( QString p_Section, QString p_Name, QString p_DefValue )
{
  QFile file;
  QString strSection;

  if( m_ConfigFileName.isEmpty() )
  {
    return p_DefValue;
  }

  file.setFileName( m_ConfigFileName );
  if( !file.exists() )
  {
     return p_DefValue;
  }

  if( !file.open( QIODevice::ReadOnly ) )
  {
    return p_DefValue;
  }

  strSection = "[" + p_Section + "]";
  {
    int iFind;
    QString line;
    QTextStream stream(&file);
    while ( !stream.atEnd() )
    {
       line = stream.readLine(); // line of text excluding '\n'
       if( line == strSection )
       {
          while ( !stream.atEnd() )
          {
            line = stream.readLine(); // line of text excluding '\n'
            iFind = line.indexOf( "[" );
            if( iFind != -1 )
            {
              break;
            }
            iFind = line.indexOf( p_Name );
            if( iFind != -1 )
            {
              QString strRtn;
              strRtn = line.mid( iFind + p_Name.length() + 1 );
              file.close();
              return strRtn;
            }
          }
          break;
       }
    }

  }
  file.close();
  return p_DefValue;
}
/** gbk code to unicode */
QString CIniEx1::GBK2Unicode( QString p_szStr )
{
#ifdef INPC
  QTextCodec * codec;
  codec = QTextCodec::codecForName( "GBK" );
  return codec->toUnicode( p_szStr );
#else
   return p_szStr;
#endif
}
/** No descriptions */
QString CIniEx1::Unicode2GBK( QString p_str )
{
 #ifdef INPC
  QTextCodec * codec;
  codec = QTextCodec::codecForName( "GBK" );
  return codec->fromUnicode( p_str );
#else
   return p_str;
#endif
}
