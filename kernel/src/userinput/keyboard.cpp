#include "keyboard.h"

    bool isLeftShiftPressed;
    bool isRightShiftPressed;

void HandleKeyboard(uint8_t scancode){

    switch (scancode){
        case LeftShift:
            isLeftShiftPressed = true;
            return;
        case LeftShift + 0x80:
            isLeftShiftPressed = false;
            return;
        case RightShift:
            isRightShiftPressed = true;
            return;
        case RightShift + 0x80:
            isRightShiftPressed = false;
            return;
        case Enter:
            //if(GlobalRenderer!=NULL)
               // GlobalRenderer->defaultCanvases->textCanvas->Next();
            return;
        case Spacebar:
           // if(GlobalRenderer!=NULL)
                //GlobalRenderer->defaultCanvases->textCanvas->PutChar(' ');
            return;
        case BackSpace:
            //if(GlobalRenderer!=NULL)
                //GlobalRenderer->defaultCanvases->textCanvas->ClearChar();
           return;
    }

    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed);

    if (ascii != 0 && GlobalRenderer != NULL){
       // GlobalRenderer->defaultCanvases->textCanvas->PutChar(ascii);
    }

}