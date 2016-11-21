// IniEx.h: interface for the CIniEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIEX_H__36888C4C_12D3_4F65_A78B_2F3C3576B5B8__INCLUDED_)
#define AFX_INIEX_H__36888C4C_12D3_4F65_A78B_2F3C3576B5B8__INCLUDED_

#define MAX_SECTION_COUNT	256
#include <QString>
#include <QFile>
#include <QTextStream>
class CIniEx1
{
public:

  CIniEx1();
  ~CIniEx1();

public:
  /** No descriptions */
  int GetIntValue( QString p_Section, QString p_Name, int p_iDefValue = 0 );
  /** No descriptions */
  QString GetStringValue( QString p_Section, QString p_Name, QString p_DefValue = "" );
  /** No descriptions */
  QString GetCStringValue( QString p_Section, QString p_Name, QString p_DefValue = "" );
  static QString GBK2Unicode( QString p_szStr );
  static QString Unicode2GBK( QString p_szStr );

public:
  /** No descriptions */
  QString m_ConfigFileName;

};

#endif // !defined(AFX_INIEX_H__36888C4C_12D3_4F65_A78B_2F3C3576B5B8__INCLUDED_)
