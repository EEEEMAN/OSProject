db 0xeb
db 0x3b
db 0x90
times 445 - ($ - $$) db 0
bBootIndicator					db		0x80	;부탕 가능한 파티션이면 0x80 아니면 0x00
bStartingHeader					db 		0x20	;도스시절 필드
wStartingSectorAndCylinder		dw 		0x0021	;도스시절 필드
bSystemID						db 		0x0c	;시스템 타입. 0x0B 또는 0x0C
bEndingHeader					db 		0xfe	;도스시절 필드
wEndingSectorAndCylinder		dw 		0xccff	;도스시절 필드
dwRelativeSector				dd 		0x00000800	;파티션이 시작되는 섹터
dwTotalSector					dd 		0x00ee8400	;총 파티션의 크기
times 510 - ($ - $$) db 0
db 0x55
db 0xaa