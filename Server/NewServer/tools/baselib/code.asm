PUBLIC _ReplaceThreadProc
_text SEGMENT
.data
params	dd ?
		dd ?
		dq ?
		dq ?
.code
_ReplaceThreadProc proc
	ret
_ReplaceThreadProc endp
_text ENDS
end
