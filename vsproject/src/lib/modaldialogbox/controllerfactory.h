#if !defined controllerfactory_h
#define controllerfactory_h
/************************************************************************************************************ 
** controllerfactory
** ����� ����. ���������, ������� �� ������������ ������������ �� ������ ������ ��������
** ��� ��������� ���������� ����...
**                   __              __ __            ____            __                    
** .----.-----.-----|  |_.----.-----|  |  |-----.----|   _|-----.----|  |_.-----.----.--.--.
** |  __|  _  |     |   _|   _|  _  |  |  |  -__|   _|   _|  _  |  __|   _|  _  |   _|  |  |
** |____|_____|__|__|____|__| |_____|__|__|_____|__| |__| |___._|____|____|_____|__| |___  |
**                                                                                   |_____|
************************************************************************************************************/

#include <windows.h>

/***********************************************************************************************************/
/* basic controller class
/* subclass this and define your own class for in/out data */
class modaldialogboxcontroller
{
protected:
    modaldialogboxcontroller(void * d) : _data (d) {}

public:
    virtual        ~modaldialogboxcontroller() {}

    virtual void    initialization() = 0;
    
    virtual BOOL    paint() = 0;
    virtual BOOL    drawitem(LPDRAWITEMSTRUCT pis) = 0;
    virtual BOOL    themechanged() = 0;
    
    virtual LRESULT ctlcolorstatic(HDC, HWND) = 0;
    virtual LRESULT ctlcolorbutton(HDC, HWND) = 0;

    virtual bool    mousemove(int x, int y) = 0;
    virtual bool    lbuttondn(int x, int y) = 0;
    virtual bool    lbuttonup(int x, int y) = 0;

    virtual bool    oncommand(int ctrlid, int notifycode) = 0;
    virtual bool    onnotify(int ctrlid, NMHDR * hdr) = 0;

    void *          getarglist() { return _data; }

private:
    void *          _data;
};

/***********************************************************************************************************/
/* basic factory class  */
class ctrlfactory
{
public:
    // ��������� ��������� �� ������ ���������� ������
    ctrlfactory(void * d) : _data (d) {}

    // ������������ ���������� ��� ������ windowproc
    void *                             getarglist() { return _data; }
    virtual modaldialogboxcontroller * makectrl(HWND hwnddlg) = 0;

private:
    void *          _data;
};

/***********************************************************************************************************/
/* parametrized by class myctrl derived from dlgcontroller
** and myarglist that encapsulates in/out arguments to the dialog */
template<typename ctrl, typename data> class controllerfactory: public ctrlfactory
{
public:
    // ���������� ����� ������ ������ � �������� ���������
    controllerfactory(void * d) : ctrlfactory (d) { }
    
    // ����� ������� ���������� �� �������, �� ��������� ����� ���������� ������
    // �� ����, ����� ��������� ������������ �����(�����)) �����
    // � ������� �������� ������ ����� � �������� ���������. �������� optionscontroller->optionsdata
    modaldialogboxcontroller * makectrl(HWND boxhwnd) { return new ctrl(boxhwnd, (data*)getarglist()); }
};

/***********************************************************************************************************/
#endif