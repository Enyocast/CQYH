/********************************************************************
	Created:	2013/05/20
	Filename: 	DlgInterpEditorAutoShakeCamera
	file ext:	h
	Author:		hemu@snda
	Purpose:	Matinee自动添加震屏动画
*********************************************************************/

#ifndef __DLGINTERPEDITORAutoShakeCamera_H_
#define __DLGINTERPEDITORAutoShakeCamera_H_

class WxInterpEditorAutoShakeCamera : public wxDialog
{
public:
	WxInterpEditorAutoShakeCamera(wxWindow* InParent, FLOAT IntervalMinimum, FLOAT IntervalMaximum);
	~WxInterpEditorAutoShakeCamera();

	FLOAT Tolerance;
	UBOOL FullInterval;
	FLOAT IntervalStart;
	FLOAT IntervalEnd;
    FLOAT SWING;

private:

    //起始方向
    wxStaticText* StartDirLabel;
    wxRadioBox*   StartDirRadioBox;
	//震动频率
	wxStaticText* FrequencyLabel;
    wxTextCtrl*   FrequencyText;
    //振幅
	wxStaticText* SwingLabel;
    wxTextCtrl*   SwingText;
    wxSpinCtrl*   SwingSpin;
    //次数
    wxStaticText* CountLabel;
    wxTextCtrl*   CountText;
    //相位 
	wxStaticText* IntervalLabel;
	wxTextCtrl*   IntervalText;
	//按钮
	wxButton*     OkayButton;
	wxButton*     CancelButton;
	void OnOkay(wxCommandEvent& In);
	void OnCancel(wxCommandEvent& In);

	DECLARE_EVENT_TABLE()
};

#endif // __DLGINTERPEDITORAutoShakeCamera_H_

