#if !defined(AFX_MARKUP_H__20050505_6983_3DDF_F867_0080AD509054__INCLUDED_)
#define AFX_MARKUP_H__20050505_6983_3DDF_F867_0080AD509054__INCLUDED_

#pragma once

class CMarkup;
class CMarkupNode;


class UILIB_API CMarkup
{
friend CMarkupNode;
public:
   CMarkup(LPCTSTR pstrXML = NULL);
   ~CMarkup();

   bool Load(LPCTSTR pstrXML);
   bool LoadFromFile(LPCTSTR pstrFilename);
   void Release();
   bool IsValid() const;

   void SetPreserveWhitespace(bool bPreserve = true);
   void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
   void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;

   CMarkupNode GetRoot();

private:
   typedef struct tagXMLELEMENT
   {
      ULONG iStart;
      ULONG iChild;
      ULONG iNext;
      ULONG iParent;
      ULONG iData;
   } XMLELEMENT;
   
   LPTSTR m_pstrXML;
   XMLELEMENT* m_pElements;
   ULONG m_nElements;
   ULONG m_nReservedElements;
   TCHAR m_szErrorMsg[100];
   TCHAR m_szErrorXML[50];
   bool m_bPreserveWhitespace;

private:
   bool _Parse();
   bool _Parse(LPTSTR& pstrText, ULONG iParent);
   XMLELEMENT* _ReserveElement();
   inline void _SkipWhitespace(LPTSTR& pstr) const;
   inline void _SkipWhitespace(LPCTSTR& pstr) const;
   inline void _SkipIdentifier(LPTSTR& pstr) const;
   inline void _SkipIdentifier(LPCTSTR& pstr) const;
   bool _ParseData(LPTSTR& pstrText, LPTSTR& pstrData, TCHAR cEnd);
   void _ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest);
   bool _ParseAttributes(LPTSTR& pstrText);
   bool _Failed(LPCTSTR pstrError, LPCTSTR pstrLocation = NULL);
};


class UILIB_API CMarkupNode
{
friend CMarkup;
private:
   CMarkupNode();
   CMarkupNode(CMarkup* pOwner, int iPos);

public:
   bool IsValid() const;

   CMarkupNode GetParent();
   CMarkupNode GetSibling();
   CMarkupNode GetChild();
   CMarkupNode GetChild(LPCTSTR pstrName);

   bool HasSiblings() const;
   bool HasChildren() const;
   LPCTSTR GetName() const;
   LPCTSTR GetValue() const;

   bool HasAttributes();
   bool HasAttribute(LPCTSTR pstrName);
   int GetAttributeCount();
   LPCTSTR GetAttributeName(int iIndex);
   LPCTSTR GetAttributeValue(int iIndex);
   LPCTSTR GetAttributeValue(LPCTSTR pstrName);
   bool GetAttributeValue(int iIndex, LPTSTR pstrValue, SIZE_T cchMax);
   bool GetAttributeValue(LPCTSTR pstrName, LPTSTR pstrValue, SIZE_T cchMax);

private:
   void _MapAttributes();

   enum { MAX_XML_ATTRIBUTES = 20 };

   typedef struct
   {
      ULONG iName;
      ULONG iValue;
   } XMLATTRIBUTE;

   int m_iPos;
   int m_nAttributes;
   XMLATTRIBUTE m_aAttributes[MAX_XML_ATTRIBUTES];
   CMarkup* m_pOwner;
};


#endif // !defined(AFX_MARKUP_H__20050505_6983_3DDF_F867_0080AD509054__INCLUDED_)

