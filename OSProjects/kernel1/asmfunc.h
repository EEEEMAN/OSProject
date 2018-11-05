#ifndef __IOFUNC_H__
#define __IOFUNC_H__

void jumpToMainKernel();
void setCR3Register(DWORD pageAddress);
void activePaging();
void activeA20Gate();

#endif /*__IOFUNC_H__*/
