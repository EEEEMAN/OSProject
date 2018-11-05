bBootIndicator					db		0	;부탕 가능한 파티션이면 0x80 아니면 0x00
bStartingHeader					db 		0	;도스시절 필드
wStartingSectorAndCylinder		dw 		0	;도스시절 필드
bSystemID						db 		0	;시스템 타입. 0x0B 또는 0x0C
bEndingHeader					db 		0	;도스시절 필드
wEndingSectorAndCylinder		dw 		0	;도스시절 필드
dwRelativeSector				dd 		0	;파티션이 시작되는 섹터
dwTotalSector					dd 		0	;총 파티션의 크기