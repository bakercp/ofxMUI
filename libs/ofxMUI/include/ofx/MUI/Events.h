//// =============================================================================
////
//// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
////
//// The above copyright notice and this permission notice shall be included in
//// all copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//// THE SOFTWARE.
////
//// =============================================================================
//
//
//#pragma once
//	
//
//#include "ofx/DOM/Events.h"
//
//
//namespace ofx {
//namespace MUI {
//
//
////    class Button;
////
////
////    class ButtonEventArgs: public DOM::EventArgs
////    {
////    public:
////        /// \brief Create EventArgs with a type.
////        /// \param type The event type string (case-insensitive).
////        /// \param source The source of the event.
////        /// \param target The target element.
////        /// \param relatedTarget The relatedTarget element.
////        /// \param bubbles True iff the argument bubbles after AT_TARGET phase.
////        /// \param cancelable True iff the event can be cancelled by a listener.
////        /// \param timestamp The timestamp of the event.
////        ButtonEventArgs(const std::string& type,
////                        Button* source,
////                        Button* target,
////                        Widget* relatedTarget,
////                        bool bubbles,
////                        bool cancelable,
////                        uint64_t timestamp);
////
////
////
////        static const std::string BUTTON_DOWN;
////        static const std::string BUTTON_UP;
////        static const std::string BUTTON_PRESSED;
////        
////    private:
////        Button* _button;
////        Widget* _parent;
////        
////    };
//
//
//} } // ofx::MUI
