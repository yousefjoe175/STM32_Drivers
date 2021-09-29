#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

void HTFT_voidInitialize (void);
void HTFT_voidDisplayImage (const u16 *Ptr_u16Image);
void HTFT_voidFillColor(u16 copy_u16Color);
void HTFT_voidDrawRectangle (u8 x1, u8 x2, u8 y1, u8 y2, u16 color);
#endif
